/*
 *  lxdialog - Display simple dialog boxes from shell scripts
 *
 *  ORIGINAL AUTHOR: Savio Lam (lam836@cs.cuhk.hk)
 *  MODIFIED FOR LINUX KERNEL CONFIG BY: William Roadcap (roadcap@cfw.com)
 *
 *  Modified again for Plural by Brad Proctor
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: lxdialog.c,v 1.2 2001/10/26 20:42:28 fredlie Exp $
 */

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include CURSES_LOC

/*
 * Colors in ncurses 1.9.9e do not work properly since foreground and
 * background colors are OR'd rather than separately masked.  This version
 * of dialog was hacked to work with ncurses 1.9.9e, making it incompatible
 * with standard curses.  The simplest fix (to make this work with standard
 * curses) uses the wbkgdset() function, not used in the original hack.
 * Turn it off if we're building with 1.9.9e, since it just confuses things.
 */
#if defined(NCURSES_VERSION) && defined(_NEED_WRAP) && !defined(GCC_PRINTFLIKE)
#define OLD_NCURSES 1
#undef  wbkgdset
#define wbkgdset(w,p) /*nothing*/
#else
#define OLD_NCURSES 0
#endif

#define TR(params) _tracef params

#define ESC 27
#define TAB 9
#define MAX_LEN 2048
#define BUF_SIZE (10*1024)
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)


#ifndef ACS_ULCORNER
#define ACS_ULCORNER '+'
#endif
#ifndef ACS_LLCORNER
#define ACS_LLCORNER '+'
#endif
#ifndef ACS_URCORNER
#define ACS_URCORNER '+'
#endif
#ifndef ACS_LRCORNER
#define ACS_LRCORNER '+'
#endif
#ifndef ACS_HLINE
#define ACS_HLINE '-'
#endif
#ifndef ACS_VLINE
#define ACS_VLINE '|'
#endif
#ifndef ACS_LTEE
#define ACS_LTEE '+'
#endif
#ifndef ACS_RTEE
#define ACS_RTEE '+'
#endif
#ifndef ACS_UARROW
#define ACS_UARROW '^'
#endif
#ifndef ACS_DARROW
#define ACS_DARROW 'v'
#endif

/* 
 * Attribute names
 */
#define screen_attr                   attributes[0]
#define shadow_attr                   attributes[1]
#define dialog_attr                   attributes[2]
#define title_attr                    attributes[3]
#define border_attr                   attributes[4]
#define button_active_attr            attributes[5]
#define button_inactive_attr          attributes[6]
#define button_key_active_attr        attributes[7]
#define button_key_inactive_attr      attributes[8]
#define button_label_active_attr      attributes[9]
#define button_label_inactive_attr    attributes[10]
#define inputbox_attr                 attributes[11]
#define inputbox_border_attr          attributes[12]
#define searchbox_attr                attributes[13]
#define searchbox_title_attr          attributes[14]
#define searchbox_border_attr         attributes[15]
#define position_indicator_attr       attributes[16]
#define menubox_attr                  attributes[17]
#define menubox_border_attr           attributes[18]
#define item_attr                     attributes[19]
#define item_selected_attr            attributes[20]
#define tag_attr                      attributes[21]
#define tag_selected_attr             attributes[22]
#define tag_key_attr                  attributes[23]
#define tag_key_selected_attr         attributes[24]
#define check_attr                    attributes[25]
#define check_selected_attr           attributes[26]
#define uarrow_attr                   attributes[27]
#define darrow_attr                   attributes[28]

/* number of attributes */
#define ATTRIBUTE_COUNT               29

/*
 * Global variables
 */
extern bool use_colors;
extern bool use_shadow;

extern chtype attributes[];

extern const char *backtitle;

/*
 * Function prototypes
 */
extern void create_rc (const char *filename);
extern int parse_rc (void);


void init_dialog (void);
void end_dialog (void);
void attr_clear (WINDOW * win, int height, int width, chtype attr);
void dialog_clear (void);
void color_setup (void);
void print_autowrap (WINDOW * win, const char *prompt, int width, int y, int x);
void print_button (WINDOW * win, const char *label, int y, int x, int selected);
void draw_box (WINDOW * win, int y, int x, int height, int width, chtype box,
		chtype border);
void draw_shadow (WINDOW * win, int y, int x, int height, int width);

int first_alpha (const char *string, const char *exempt);
int dialog_yesno (const char *title, const char *prompt, int height, int width);
int dialog_msgbox (const char *title, const char *prompt, int height,
		int width, int pause);
int dialog_textbox (const char *title, const char *file, int height, int width);
int dialog_menu (const char *title, const char *prompt, int height, int width,
		int menu_height, const char *choice, int item_no, 
		const char * const * items);
int dialog_checklist (const char *title, const char *prompt, int height,
		int width, int list_height, int item_no,
		const char * const * items, int flag);
extern unsigned char dialog_input_result[];
int dialog_inputbox (const char *title, const char *prompt, int height,
		int width, const char *init);

/*
 * This is the base for fictitious keys, which activate
 * the buttons.
 *
 * Mouse-generated keys are the following:
 *   -- the first 32 are used as numbers, in addition to '0'-'9'
 *   -- the lowercase are used to signal mouse-enter events (M_EVENT + 'o')
 *   -- uppercase chars are used to invoke the button (M_EVENT + 'O')
 */
#define M_EVENT (KEY_MAX+1)


/*
 * The `flag' parameter in checklist is used to select between
 * radiolist and checklist
 */
#define FLAG_CHECK 1
#define FLAG_RADIO 0

/*
 *   Default color definitions
 *
 *   *_FG = foreground
 *   *_BG = background
 *   *_HL = highlight?
 */
#define SCREEN_FG                    COLOR_CYAN
#define SCREEN_BG                    COLOR_BLUE
#define SCREEN_HL                    TRUE

#define SHADOW_FG                    COLOR_BLACK
#define SHADOW_BG                    COLOR_BLACK
#define SHADOW_HL                    TRUE

#define DIALOG_FG                    COLOR_BLACK
#define DIALOG_BG                    COLOR_WHITE
#define DIALOG_HL                    FALSE

#define TITLE_FG                     COLOR_YELLOW
#define TITLE_BG                     COLOR_WHITE
#define TITLE_HL                     TRUE

#define BORDER_FG                    COLOR_WHITE
#define BORDER_BG                    COLOR_WHITE
#define BORDER_HL                    TRUE

#define BUTTON_ACTIVE_FG             COLOR_WHITE
#define BUTTON_ACTIVE_BG             COLOR_BLUE
#define BUTTON_ACTIVE_HL             TRUE

#define BUTTON_INACTIVE_FG           COLOR_BLACK
#define BUTTON_INACTIVE_BG           COLOR_WHITE
#define BUTTON_INACTIVE_HL           FALSE

#define BUTTON_KEY_ACTIVE_FG         COLOR_WHITE
#define BUTTON_KEY_ACTIVE_BG         COLOR_BLUE
#define BUTTON_KEY_ACTIVE_HL         TRUE

#define BUTTON_KEY_INACTIVE_FG       COLOR_RED
#define BUTTON_KEY_INACTIVE_BG       COLOR_WHITE
#define BUTTON_KEY_INACTIVE_HL       FALSE

#define BUTTON_LABEL_ACTIVE_FG       COLOR_YELLOW
#define BUTTON_LABEL_ACTIVE_BG       COLOR_BLUE
#define BUTTON_LABEL_ACTIVE_HL       TRUE

#define BUTTON_LABEL_INACTIVE_FG     COLOR_BLACK
#define BUTTON_LABEL_INACTIVE_BG     COLOR_WHITE
#define BUTTON_LABEL_INACTIVE_HL     TRUE

#define INPUTBOX_FG                  COLOR_BLACK
#define INPUTBOX_BG                  COLOR_WHITE
#define INPUTBOX_HL                  FALSE

#define INPUTBOX_BORDER_FG           COLOR_BLACK
#define INPUTBOX_BORDER_BG           COLOR_WHITE
#define INPUTBOX_BORDER_HL           FALSE

#define SEARCHBOX_FG                 COLOR_BLACK
#define SEARCHBOX_BG                 COLOR_WHITE
#define SEARCHBOX_HL                 FALSE

#define SEARCHBOX_TITLE_FG           COLOR_YELLOW
#define SEARCHBOX_TITLE_BG           COLOR_WHITE
#define SEARCHBOX_TITLE_HL           TRUE

#define SEARCHBOX_BORDER_FG          COLOR_WHITE
#define SEARCHBOX_BORDER_BG          COLOR_WHITE
#define SEARCHBOX_BORDER_HL          TRUE

#define POSITION_INDICATOR_FG        COLOR_YELLOW
#define POSITION_INDICATOR_BG        COLOR_WHITE
#define POSITION_INDICATOR_HL        TRUE

#define MENUBOX_FG                   COLOR_BLACK
#define MENUBOX_BG                   COLOR_WHITE
#define MENUBOX_HL                   FALSE

#define MENUBOX_BORDER_FG            COLOR_WHITE
#define MENUBOX_BORDER_BG            COLOR_WHITE
#define MENUBOX_BORDER_HL            TRUE

#define ITEM_FG                      COLOR_BLACK
#define ITEM_BG                      COLOR_WHITE
#define ITEM_HL                      FALSE

#define ITEM_SELECTED_FG             COLOR_WHITE
#define ITEM_SELECTED_BG             COLOR_BLUE
#define ITEM_SELECTED_HL             TRUE

#define TAG_FG                       COLOR_YELLOW
#define TAG_BG                       COLOR_WHITE
#define TAG_HL                       TRUE

#define TAG_SELECTED_FG              COLOR_YELLOW
#define TAG_SELECTED_BG              COLOR_BLUE
#define TAG_SELECTED_HL              TRUE

#define TAG_KEY_FG                   COLOR_YELLOW
#define TAG_KEY_BG                   COLOR_WHITE
#define TAG_KEY_HL                   TRUE

#define TAG_KEY_SELECTED_FG          COLOR_YELLOW
#define TAG_KEY_SELECTED_BG          COLOR_BLUE
#define TAG_KEY_SELECTED_HL          TRUE

#define CHECK_FG                     COLOR_BLACK
#define CHECK_BG                     COLOR_WHITE
#define CHECK_HL                     FALSE

#define CHECK_SELECTED_FG            COLOR_WHITE
#define CHECK_SELECTED_BG            COLOR_BLUE
#define CHECK_SELECTED_HL            TRUE

#define UARROW_FG                    COLOR_GREEN
#define UARROW_BG                    COLOR_WHITE
#define UARROW_HL                    TRUE

#define DARROW_FG                    COLOR_GREEN
#define DARROW_BG                    COLOR_WHITE
#define DARROW_HL                    TRUE

/* End of default color definitions */

#define C_ATTR(x,y)                  ((x ? A_BOLD : 0) | COLOR_PAIR((y)))
#define COLOR_NAME_LEN               10
#define COLOR_COUNT                  8

/*
 * Global variables
 */

typedef struct {
    char name[COLOR_NAME_LEN];
    int value;
} color_names_st;

extern color_names_st color_names[];
extern int color_table[][3];

static void Usage (const char *name);

typedef int (jumperFn) (const char *title, int argc, const char * const * argv);

struct Mode {
    char *name;
    int argmin, argmax, argmod;
    jumperFn *jumper;
};

jumperFn j_menu, j_checklist, j_radiolist, j_yesno, j_textbox, j_inputbox;
jumperFn j_msgbox, j_infobox;

static struct Mode modes[] =
{
    {"--menu", 9, 0, 3, j_menu},
    {"--checklist", 9, 0, 3, j_checklist},
    {"--radiolist", 9, 0, 3, j_radiolist},
    {"--yesno",    5,5,1, j_yesno},
    {"--textbox",  5,5,1, j_textbox},
    {"--inputbox", 5, 6, 1, j_inputbox},
    {"--msgbox", 5, 5, 1, j_msgbox},
    {"--infobox", 5, 5, 1, j_infobox},
    {NULL, 0, 0, 0, NULL}
};

static struct Mode *modePtr;

#ifdef LOCALE
#include <locale.h>
#endif

int
main (int argc, const char * const * argv)
{
    int offset = 0, clear_screen = 0, end_common_opts = 0, retval;
    const char *title = NULL;

#ifdef LOCALE
    (void) setlocale (LC_ALL, "");
#endif

#ifdef TRACE
    trace(TRACE_CALLS|TRACE_UPDATE);
#endif
    if (argc < 2) {
	Usage (argv[0]);
	exit (-1);
    }

    while (offset < argc - 1 && !end_common_opts) {	/* Common options */
	if (!strcmp (argv[offset + 1], "--title")) {
	    if (argc - offset < 3 || title != NULL) {
		Usage (argv[0]);
		exit (-1);
	    } else {
		title = argv[offset + 2];
		offset += 2;
	    }
        } else if (!strcmp (argv[offset + 1], "--backtitle")) {
            if (backtitle != NULL) {
                Usage (argv[0]);
                exit (-1);
            } else {
                backtitle = argv[offset + 2];
                offset += 2;
            }
	} else if (!strcmp (argv[offset + 1], "--clear")) {
	    if (clear_screen) {	/* Hey, "--clear" can't appear twice! */
		Usage (argv[0]);
		exit (-1);
	    } else if (argc == 2) {	/* we only want to clear the screen */
		init_dialog ();
		refresh ();	/* init_dialog() will clear the screen for us */
		end_dialog ();
		return 0;
	    } else {
		clear_screen = 1;
		offset++;
	    }
	} else			/* no more common options */
	    end_common_opts = 1;
    }

    if (argc - 1 == offset) {	/* no more options */
	Usage (argv[0]);
	exit (-1);
    }
    /* use a table to look for the requested mode, to avoid code duplication */

    for (modePtr = modes; modePtr->name; modePtr++)	/* look for the mode */
	if (!strcmp (argv[offset + 1], modePtr->name))
	    break;

    if (!modePtr->name)
	Usage (argv[0]);
    if (argc - offset < modePtr->argmin)
	Usage (argv[0]);
    if (modePtr->argmax && argc - offset > modePtr->argmax)
	Usage (argv[0]);



    init_dialog ();
    retval = (*(modePtr->jumper)) (title, argc - offset, argv + offset);

    if (clear_screen) {		/* clear screen before exit */
	attr_clear (stdscr, LINES, COLS, screen_attr);
	refresh ();
    }
    end_dialog();

    exit (retval);
}

/*
 * Print program usage
 */
static void
Usage (const char *name)
{
    fprintf (stderr, "\
\ndialog, by Savio Lam (lam836@cs.cuhk.hk).\
\n  patched by Stuart Herbert (S.Herbert@shef.ac.uk)\
\n  modified/gutted for use as a Linux kernel config tool by \
\n  William Roadcap (roadcapw@cfw.com)\
\n\
\n* Display dialog boxes from shell scripts *\
\n\
\nUsage: %s --clear\
\n       %s [--title <title>] [--backtitle <backtitle>] --clear <Box options>\
\n\
\nBox options:\
\n\
\n  --menu      <text> <height> <width> <menu height> <tag1> <item1>...\
\n  --checklist <text> <height> <width> <list height> <tag1> <item1> <status1>...\
\n  --radiolist <text> <height> <width> <list height> <tag1> <item1> <status1>...\
\n  --textbox   <file> <height> <width>\
\n  --inputbox  <text> <height> <width> [<init>]\
\n  --yesno     <text> <height> <width>\
\n", name, name);
    exit (-1);
}

/*
 * These are the program jumpers
 */

int
j_menu (const char *t, int ac, const char * const * av)
{
    return dialog_menu (t, av[2], atoi (av[3]), atoi (av[4]),
			atoi (av[5]), av[6], (ac - 6) / 2, av + 7);
}

int
j_checklist (const char *t, int ac, const char * const * av)
{
    return dialog_checklist (t, av[2], atoi (av[3]), atoi (av[4]),
	atoi (av[5]), (ac - 6) / 3, av + 6, FLAG_CHECK);
}

int
j_radiolist (const char *t, int ac, const char * const * av)
{
    return dialog_checklist (t, av[2], atoi (av[3]), atoi (av[4]),
	atoi (av[5]), (ac - 6) / 3, av + 6, FLAG_RADIO);
}

int
j_textbox (const char *t, int ac, const char * const * av)
{
    return dialog_textbox (t, av[2], atoi (av[3]), atoi (av[4]));
}

int
j_yesno (const char *t, int ac, const char * const * av)
{
    return dialog_yesno (t, av[2], atoi (av[3]), atoi (av[4]));
}

int
j_inputbox (const char *t, int ac, const char * const * av)
{
    int ret = dialog_inputbox (t, av[2], atoi (av[3]), atoi (av[4]),
                            ac == 6 ? av[5] : (char *) NULL);
    if (ret == 0)
        fprintf(stderr, dialog_input_result);
    return ret;
}

int
j_msgbox (const char *t, int ac, const char * const * av)
{
    return dialog_msgbox (t, av[2], atoi (av[3]), atoi (av[4]), 1);
}

int
j_infobox (const char *t, int ac, const char * const * av)
{
    return dialog_msgbox (t, av[2], atoi (av[3]), atoi (av[4]), 0);
}

static int list_width, check_x, item_x, checkflag;

/*
 * Print list item
 */
static void
checklist_print_item (WINDOW * win, const char *item, int status,
	    int choice, int selected)
{
    int i;

    /* Clear 'residue' of last item */
    wattrset (win, menubox_attr);
    wmove (win, choice, 0);
    for (i = 0; i < list_width; i++)
	waddch (win, ' ');

    wmove (win, choice, check_x);
    wattrset (win, selected ? check_selected_attr : check_attr);
    if (checkflag == FLAG_CHECK)
	wprintw (win, "[%c]", status ? 'X' : ' ');
    else
	wprintw (win, "(%c)", status ? 'X' : ' ');

    wattrset (win, selected ? tag_selected_attr : tag_attr);
    mvwaddch(win, choice, item_x, item[0]);
    wattrset (win, selected ? item_selected_attr : item_attr);
    waddstr (win, (char *)item+1);
    if (selected) {
    	wmove (win, choice, check_x+1);
    	wrefresh (win);
    }
}

/*
 * Print the scroll indicators.
 */
static void
checklist_print_arrows (WINDOW * win, int choice, int item_no, int scroll,
		int y, int x, int height)
{
    wmove(win, y, x);

    if (scroll > 0) {
	wattrset (win, uarrow_attr);
	waddch (win, ACS_UARROW);
	waddstr (win, "(-)");
    }
    else {
	wattrset (win, menubox_attr);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
    }

   y = y + height + 1;
   wmove(win, y, x);

   if ((height < item_no) && (scroll + choice < item_no - 1)) {
	wattrset (win, darrow_attr);
	waddch (win, ACS_DARROW);
	waddstr (win, "(+)");
    }
    else {
	wattrset (win, menubox_border_attr);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
   }
}

/*
 *  Display the termination buttons
 */
static void
checklist_print_buttons( WINDOW *dialog, int height, int width, int selected)
{
    int x = width / 2 - 11;
    int y = height - 2;

    print_button (dialog, "Select", y, x, selected == 0);
    print_button (dialog, " Help ", y, x + 14, selected == 1);

    wmove(dialog, y, x+1 + 14*selected);
    wrefresh (dialog);
}

/*
 * Display a dialog box with a list of options that can be turned on or off
 * The `flag' parameter is used to select between radiolist and checklist.
 */
int
dialog_checklist (const char *title, const char *prompt, int height, int width,
	int list_height, int item_no, const char * const * items, int flag)
	
{
    int i, x, y, box_x, box_y;
    int key = 0, button = 0, choice = 0, scroll = 0, max_choice, *status;
    WINDOW *dialog, *list;

    checkflag = flag;

    /* Allocate space for storing item on/off status */
    if ((status = malloc (sizeof (int) * item_no)) == NULL) {
	endwin ();
	fprintf (stderr,
		 "\nCan't allocate memory in dialog_checklist().\n");
	exit (-1);
    }

    /* Initializes status */
    for (i = 0; i < item_no; i++) {
	status[i] = !strcasecmp (items[i * 3 + 2], "on");
	if (!choice && status[i])
            choice = i;
    }

    max_choice = MIN (list_height, item_no);

    /* center dialog box on screen */
    x = (COLS - width) / 2;
    y = (LINES - height) / 2;

    draw_shadow (stdscr, y, x, height, width);

    dialog = newwin (height, width, y, x);
    keypad (dialog, TRUE);

    draw_box (dialog, 0, 0, height, width, dialog_attr, border_attr);
    wattrset (dialog, border_attr);
    mvwaddch (dialog, height-3, 0, ACS_LTEE);
    for (i = 0; i < width - 2; i++)
	waddch (dialog, ACS_HLINE);
    wattrset (dialog, dialog_attr);
    waddch (dialog, ACS_RTEE);

    if (title != NULL && strlen(title) >= width-2 ) {
	/* truncate long title -- mec */
	char * title2 = malloc(width-2+1);
	memcpy( title2, title, width-2 );
	title2[width-2] = '\0';
	title = title2;
    }

    if (title != NULL) {
	wattrset (dialog, title_attr);
	mvwaddch (dialog, 0, (width - strlen(title))/2 - 1, ' ');
	waddstr (dialog, (char *)title);
	waddch (dialog, ' ');
    }

    wattrset (dialog, dialog_attr);
    print_autowrap (dialog, prompt, width - 2, 1, 3);

    list_width = width - 6;
    box_y = height - list_height - 5;
    box_x = (width - list_width) / 2 - 1;

    /* create new window for the list */
    list = subwin (dialog, list_height, list_width, y+box_y+1, x+box_x+1);

    keypad (list, TRUE);

    /* draw a box around the list items */
    draw_box (dialog, box_y, box_x, list_height + 2, list_width + 2,
	      menubox_border_attr, menubox_attr);

    /* Find length of longest item in order to center checklist */
    check_x = 0;
    for (i = 0; i < item_no; i++) 
	check_x = MAX (check_x, + strlen (items[i * 3 + 1]) + 4);

    check_x = (list_width - check_x) / 2;
    item_x = check_x + 4;

    if (choice >= list_height) {
	scroll = choice - list_height + 1;
	choice -= scroll;
    }

    /* Print the list */
    for (i = 0; i < max_choice; i++) {
	checklist_print_item (list, items[(scroll+i) * 3 + 1],
		    status[i+scroll], i, i == choice);
    }

    checklist_print_arrows(dialog, choice, item_no, scroll,
			box_y, box_x + check_x + 5, list_height);

    checklist_print_buttons(dialog, height, width, 0);

    wnoutrefresh (list);
    wnoutrefresh (dialog);
    doupdate ();

    while (key != ESC) {
	key = wgetch (dialog);

    	for (i = 0; i < max_choice; i++)
            if (toupper(key) == toupper(items[(scroll+i)*3+1][0]))
                break;


	if ( i < max_choice || key == KEY_UP || key == KEY_DOWN || 
	    key == '+' || key == '-' ) {
	    if (key == KEY_UP || key == '-') {
		if (!choice) {
		    if (!scroll)
			continue;
		    /* Scroll list down */
		    if (list_height > 1) {
			/* De-highlight current first item */
			checklist_print_item (list, items[scroll * 3 + 1],
					status[scroll], 0, FALSE);
			scrollok (list, TRUE);
			wscrl (list, -1);
			scrollok (list, FALSE);
		    }
		    scroll--;
		    checklist_print_item (list, items[scroll * 3 + 1],
				status[scroll], 0, TRUE);
		    wnoutrefresh (list);

    		    checklist_print_arrows(dialog, choice, item_no, scroll,
				box_y, box_x + check_x + 5, list_height);

		    wrefresh (dialog);

		    continue;	/* wait for another key press */
		} else
		    i = choice - 1;
	    } else if (key == KEY_DOWN || key == '+') {
		if (choice == max_choice - 1) {
		    if (scroll + choice >= item_no - 1)
			continue;
		    /* Scroll list up */
		    if (list_height > 1) {
			/* De-highlight current last item before scrolling up */
			checklist_print_item (list, items[(scroll + max_choice - 1) * 3 + 1],
				    status[scroll + max_choice - 1],
				    max_choice - 1, FALSE);
			scrollok (list, TRUE);
			scroll (list);
			scrollok (list, FALSE);
		    }
		    scroll++;
		    checklist_print_item (list, items[(scroll + max_choice - 1) * 3 + 1],
				status[scroll + max_choice - 1],
				max_choice - 1, TRUE);
		    wnoutrefresh (list);

    		    checklist_print_arrows(dialog, choice, item_no, scroll,
				box_y, box_x + check_x + 5, list_height);

		    wrefresh (dialog);

		    continue;	/* wait for another key press */
		} else
		    i = choice + 1;
	    }
	    if (i != choice) {
		/* De-highlight current item */
		checklist_print_item (list, items[(scroll + choice) * 3 + 1],
			    status[scroll + choice], choice, FALSE);
		/* Highlight new item */
		choice = i;
		checklist_print_item (list, items[(scroll + choice) * 3 + 1],
			    status[scroll + choice], choice, TRUE);
		wnoutrefresh (list);
		wrefresh (dialog);
	    }
	    continue;		/* wait for another key press */
	}
	switch (key) {
	case 'H':
	case 'h':
	case '?':
	    delwin (dialog);
	    free (status);
	    return 1;
	case TAB:
	case KEY_LEFT:
	case KEY_RIGHT:
	    button = ((key == KEY_LEFT ? --button : ++button) < 0)
			? 1 : (button > 1 ? 0 : button);

	    checklist_print_buttons(dialog, height, width, button);
	    wrefresh (dialog);
	    break;
	case 'S':
	case 's':
	case ' ':
	case '\n':
	    if (!button) {
		if (flag == FLAG_CHECK) {
		    status[scroll + choice] = !status[scroll + choice];
		    wmove (list, choice, check_x);
		    wattrset (list, check_selected_attr);
		    wprintw (list, "[%c]", status[scroll + choice] ? 'X' : ' ');
		} else {
		    if (!status[scroll + choice]) {
			for (i = 0; i < item_no; i++)
			    status[i] = 0;
			status[scroll + choice] = 1;
			for (i = 0; i < max_choice; i++)
			    checklist_print_item (list, items[(scroll + i) * 3 + 1],
					status[scroll + i], i, i == choice);
		    }
		}
		wnoutrefresh (list);
		wrefresh (dialog);
            
		for (i = 0; i < item_no; i++) {
		    if (status[i]) {
			if (flag == FLAG_CHECK) {
			    fprintf (stderr, "\"%s\" ", items[i * 3]);
			} else {
			    fprintf (stderr, "%s", items[i * 3]);
			}

		    }
		}
            }
	    delwin (dialog);
	    free (status);
	    return button;
	case 'X':
	case 'x':
	    key = ESC;
	case ESC:
	    break;
	}

	/* Now, update everything... */
	doupdate ();
    }
    

    delwin (dialog);
    free (status);
    return -1;			/* ESC pressed */
}

unsigned char dialog_input_result[MAX_LEN + 1];

/*
 *  Print the termination buttons
 */
static void
inputbox_print_buttons(WINDOW *dialog, int height, int width, int selected)
{
    int x = width / 2 - 11;
    int y = height - 2;

    print_button (dialog, "  Ok  ", y, x, selected==0);
    print_button (dialog, " Help ", y, x + 14, selected==1);

    wmove(dialog, y, x+1+14*selected);
    wrefresh(dialog);
}

/*
 * Display a dialog box for inputing a string
 */
int
dialog_inputbox (const char *title, const char *prompt, int height, int width,
		 const char *init)
{
    int i, x, y, box_y, box_x, box_width;
    int input_x = 0, scroll = 0, key = 0, button = -1;
    unsigned char *instr = dialog_input_result;
    WINDOW *dialog;

    /* center dialog box on screen */
    x = (COLS - width) / 2;
    y = (LINES - height) / 2;


    draw_shadow (stdscr, y, x, height, width);

    dialog = newwin (height, width, y, x);
    keypad (dialog, TRUE);

    draw_box (dialog, 0, 0, height, width, dialog_attr, border_attr);
    wattrset (dialog, border_attr);
    mvwaddch (dialog, height-3, 0, ACS_LTEE);
    for (i = 0; i < width - 2; i++)
	waddch (dialog, ACS_HLINE);
    wattrset (dialog, dialog_attr);
    waddch (dialog, ACS_RTEE);

    if (title != NULL && strlen(title) >= width-2 ) {
	/* truncate long title -- mec */
	char * title2 = malloc(width-2+1);
	memcpy( title2, title, width-2 );
	title2[width-2] = '\0';
	title = title2;
    }

    if (title != NULL) {
	wattrset (dialog, title_attr);
	mvwaddch (dialog, 0, (width - strlen(title))/2 - 1, ' ');
	waddstr (dialog, (char *)title);
	waddch (dialog, ' ');
    }

    wattrset (dialog, dialog_attr);
    print_autowrap (dialog, prompt, width - 2, 1, 3);

    /* Draw the input field box */
    box_width = width - 6;
    getyx (dialog, y, x);
    box_y = y + 2;
    box_x = (width - box_width) / 2;
    draw_box (dialog, y + 1, box_x - 1, 3, box_width + 2,
	      border_attr, dialog_attr);

    inputbox_print_buttons(dialog, height, width, 0);

    /* Set up the initial value */
    wmove (dialog, box_y, box_x);
    wattrset (dialog, inputbox_attr);

    if (!init)
	instr[0] = '\0';
    else
	strcpy (instr, init);

    input_x = strlen (instr);

    if (input_x >= box_width) {
	scroll = input_x - box_width + 1;
	input_x = box_width - 1;
	for (i = 0; i < box_width - 1; i++)
	    waddch (dialog, instr[scroll + i]);
    } else
	waddstr (dialog, instr);

    wmove (dialog, box_y, box_x + input_x);

    wrefresh (dialog);

    while (key != ESC) {
	key = wgetch (dialog);

	if (button == -1) {	/* Input box selected */
	    switch (key) {
	    case TAB:
	    case KEY_UP:
	    case KEY_DOWN:
		break;
	    case KEY_LEFT:
		continue;
	    case KEY_RIGHT:
		continue;
	    case KEY_BACKSPACE:
	    case 127:
		if (input_x || scroll) {
		    wattrset (dialog, inputbox_attr);
		    if (!input_x) {
			scroll = scroll < box_width - 1 ?
			    0 : scroll - (box_width - 1);
			wmove (dialog, box_y, box_x);
			for (i = 0; i < box_width; i++)
			    waddch (dialog, instr[scroll + input_x + i] ?
				    instr[scroll + input_x + i] : ' ');
			input_x = strlen (instr) - scroll;
		    } else
			input_x--;
		    instr[scroll + input_x] = '\0';
		    mvwaddch (dialog, box_y, input_x + box_x, ' ');
		    wmove (dialog, box_y, input_x + box_x);
		    wrefresh (dialog);
		}
		continue;
	    default:
		if (key < 0x100 && isprint (key)) {
		    if (scroll + input_x < MAX_LEN) {
			wattrset (dialog, inputbox_attr);
			instr[scroll + input_x] = key;
			instr[scroll + input_x + 1] = '\0';
			if (input_x == box_width - 1) {
			    scroll++;
			    wmove (dialog, box_y, box_x);
			    for (i = 0; i < box_width - 1; i++)
				waddch (dialog, instr[scroll + i]);
			} else {
			    wmove (dialog, box_y, input_x++ + box_x);
			    waddch (dialog, key);
			}
			wrefresh (dialog);
		    } else
			flash ();	/* Alarm user about overflow */
		    continue;
		}
	    }
	}
	switch (key) {
	case 'O':
	case 'o':
	    delwin (dialog);
	    return 0;
	case 'H':
	case 'h':
	    delwin (dialog);
	    return 1;
	case KEY_UP:
	case KEY_LEFT:
	    switch (button) {
	    case -1:
		button = 1;	/* Indicates "Cancel" button is selected */
		inputbox_print_buttons(dialog, height, width, 1);
		break;
	    case 0:
		button = -1;	/* Indicates input box is selected */
		inputbox_print_buttons(dialog, height, width, 0);
		wmove (dialog, box_y, box_x + input_x);
		wrefresh (dialog);
		break;
	    case 1:
		button = 0;	/* Indicates "OK" button is selected */
		inputbox_print_buttons(dialog, height, width, 0);
		break;
	    }
	    break;
	case TAB:
	case KEY_DOWN:
	case KEY_RIGHT:
	    switch (button) {
	    case -1:
		button = 0;	/* Indicates "OK" button is selected */
		inputbox_print_buttons(dialog, height, width, 0);
		break;
	    case 0:
		button = 1;	/* Indicates "Cancel" button is selected */
		inputbox_print_buttons(dialog, height, width, 1);
		break;
	    case 1:
		button = -1;	/* Indicates input box is selected */
		inputbox_print_buttons(dialog, height, width, 0);
		wmove (dialog, box_y, box_x + input_x);
		wrefresh (dialog);
		break;
	    }
	    break;
	case ' ':
	case '\n':
	    delwin (dialog);
	    return (button == -1 ? 0 : button);
	case 'X':
	case 'x':
	    key = ESC;
	case ESC:
	    break;
	}
    }

    delwin (dialog);
    return -1;			/* ESC pressed */
}

static int menu_width, item_x;

/*
 * Print menu item
 */
static void
menu_print_item (WINDOW * win, const char *item, int choice, int selected, int hotkey)
{
    int j;
    char menu_item[menu_width+1];

    strncpy(menu_item, item, menu_width);
    menu_item[menu_width] = 0;
    j = first_alpha(menu_item, "YyNnMm");

    /* Clear 'residue' of last item */
    wattrset (win, menubox_attr);
    wmove (win, choice, 0);
#if OLD_NCURSES
    {
        int i;
        for (i = 0; i < menu_width; i++)
	    waddch (win, ' ');
    }
#else
    wclrtoeol(win);
#endif
    wattrset (win, selected ? item_selected_attr : item_attr);
    mvwaddstr (win, choice, item_x, menu_item);
    if (hotkey) {
    	wattrset (win, selected ? tag_key_selected_attr : tag_key_attr);
    	mvwaddch(win, choice, item_x+j, menu_item[j]);
    }
    if (selected) {
	wmove (win, choice, item_x+1);
	wrefresh (win);
    }
}

/*
 * Print the scroll indicators.
 */
static void
menu_print_arrows (WINDOW * win, int item_no, int scroll,
		int y, int x, int height)
{
    int cur_y, cur_x;

    getyx(win, cur_y, cur_x);

    wmove(win, y, x);

    if (scroll > 0) {
	wattrset (win, uarrow_attr);
	waddch (win, ACS_UARROW);
	waddstr (win, "(-)");
    }
    else {
	wattrset (win, menubox_attr);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
    }

   y = y + height + 1;
   wmove(win, y, x);

   if ((height < item_no) && (scroll + height < item_no)) {
	wattrset (win, darrow_attr);
	waddch (win, ACS_DARROW);
	waddstr (win, "(+)");
    }
    else {
	wattrset (win, menubox_border_attr);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
	waddch (win, ACS_HLINE);
   }

   wmove(win, cur_y, cur_x);
}

/*
 * Display the termination buttons.
 */
static void
menu_print_buttons (WINDOW *win, int height, int width, int selected)
{
    int x = width / 2 - 16;
    int y = height - 2;

    print_button (win, "Select", y, x, selected == 0);
    print_button (win, " Exit ", y, x + 12, selected == 1);
    print_button (win, " Help ", y, x + 24, selected == 2);

    wmove(win, y, x+1+12*selected);
    wrefresh (win);
}

/*
 * Display a menu for choosing among a number of options
 */
int
dialog_menu (const char *title, const char *prompt, int height, int width,
		int menu_height, const char *current, int item_no,
		const char * const * items)

{
    int i, j, x, y, box_x, box_y;
    int key = 0, button = 0, scroll = 0, choice = 0, first_item = 0, max_choice;
    WINDOW *dialog, *menu;
    FILE *f;

    max_choice = MIN (menu_height, item_no);

    /* center dialog box on screen */
    x = (COLS - width) / 2;
    y = (LINES - height) / 2;

    draw_shadow (stdscr, y, x, height, width);

    dialog = newwin (height, width, y, x);
    keypad (dialog, TRUE);

    draw_box (dialog, 0, 0, height, width, dialog_attr, border_attr);
    wattrset (dialog, border_attr);
    mvwaddch (dialog, height - 3, 0, ACS_LTEE);
    for (i = 0; i < width - 2; i++)
	waddch (dialog, ACS_HLINE);
    wattrset (dialog, dialog_attr);
    wbkgdset (dialog, dialog_attr & A_COLOR);
    waddch (dialog, ACS_RTEE);

    if (title != NULL && strlen(title) >= width-2 ) {
	/* truncate long title -- mec */
	char * title2 = malloc(width-2+1);
	memcpy( title2, title, width-2 );
	title2[width-2] = '\0';
	title = title2;
    }

    if (title != NULL) {
	wattrset (dialog, title_attr);
	mvwaddch (dialog, 0, (width - strlen(title))/2 - 1, ' ');
	waddstr (dialog, (char *)title);
	waddch (dialog, ' ');
    }

    wattrset (dialog, dialog_attr);
    print_autowrap (dialog, prompt, width - 2, 1, 3);

    menu_width = width - 6;
    box_y = height - menu_height - 5;
    box_x = (width - menu_width) / 2 - 1;

    /* create new window for the menu */
    menu = subwin (dialog, menu_height, menu_width,
		y + box_y + 1, x + box_x + 1);
    keypad (menu, TRUE);

    /* draw a box around the menu items */
    draw_box (dialog, box_y, box_x, menu_height + 2, menu_width + 2,
	      menubox_border_attr, menubox_attr);

    /*
     * Find length of longest item in order to center menu.
     * Set 'choice' to default item. 
     */
    item_x = 0;
    for (i = 0; i < item_no; i++) {
	item_x = MAX (item_x, MIN(menu_width, strlen (items[i * 2 + 1]) + 2));
	if (strcmp(current, items[i*2]) == 0) choice = i;
    }

    item_x = (menu_width - item_x) / 2;

    /* get the scroll info from the temp file */
    if ( (f=fopen("lxdialog.scrltmp","r")) != NULL ) {
	if ( (fscanf(f,"%d\n",&scroll) == 1) && (scroll <= choice) &&
	     (scroll+max_choice > choice) && (scroll >= 0) &&
	     (scroll+max_choice <= item_no) ) {
	    first_item = scroll;
	    choice = choice - scroll;
	    fclose(f);
	} else {
	    scroll=0;
	    remove("lxdialog.scrltmp");
	    fclose(f);
	    f=NULL;
	}
    }
    if ( (choice >= max_choice) || (f==NULL && choice >= max_choice/2) ) {
	if (choice >= item_no-max_choice/2)
	    scroll = first_item = item_no-max_choice;
	else
	    scroll = first_item = choice - max_choice/2;
	choice = choice - scroll;
    }

    /* Print the menu */
    for (i=0; i < max_choice; i++) {
	menu_print_item (menu, items[(first_item + i) * 2 + 1], i, i == choice,
                    (items[(first_item + i)*2][0] != ':'));
    }

    wnoutrefresh (menu);

    menu_print_arrows(dialog, item_no, scroll,
		 box_y, box_x+item_x+1, menu_height);

    menu_print_buttons (dialog, height, width, 0);
    wmove (menu, choice, item_x+1);
    wrefresh (menu);

    while (key != ESC) {
	key = wgetch(menu);

	if (key < 256 && isalpha(key)) key = tolower(key);

	if (strchr("ynm", key))
		i = max_choice;
	else {
        for (i = choice+1; i < max_choice; i++) {
		j = first_alpha(items[(scroll+i)*2+1], "YyNnMm");
		if (key == tolower(items[(scroll+i)*2+1][j]))
                	break;
	}
	if (i == max_choice)
       		for (i = 0; i < max_choice; i++) {
			j = first_alpha(items[(scroll+i)*2+1], "YyNnMm");
			if (key == tolower(items[(scroll+i)*2+1][j]))
                		break;
		}
	}

	if (i < max_choice || 
            key == KEY_UP || key == KEY_DOWN ||
            key == '-' || key == '+' ||
            key == KEY_PPAGE || key == KEY_NPAGE) {

            menu_print_item (menu, items[(scroll+choice)*2+1], choice, FALSE,
                       (items[(scroll+choice)*2][0] != ':'));

	    if (key == KEY_UP || key == '-') {
                if (choice < 2 && scroll) {
	            /* Scroll menu down */
                    scrollok (menu, TRUE);
                    wscrl (menu, -1);
                    scrollok (menu, FALSE);

                    scroll--;

                    menu_print_item (menu, items[scroll * 2 + 1], 0, FALSE,
                               (items[scroll*2][0] != ':'));
		} else
		    choice = MAX(choice - 1, 0);

	    } else if (key == KEY_DOWN || key == '+')  {

		menu_print_item (menu, items[(scroll+choice)*2+1], choice, FALSE,
                                (items[(scroll+choice)*2][0] != ':'));

                if ((choice > max_choice-3) &&
                    (scroll + max_choice < item_no)
                   ) {
		    /* Scroll menu up */
		    scrollok (menu, TRUE);
                    scroll (menu);
                    scrollok (menu, FALSE);

                    scroll++;

                    menu_print_item (menu, items[(scroll+max_choice-1)*2+1],
                               max_choice-1, FALSE,
                               (items[(scroll+max_choice-1)*2][0] != ':'));
                } else
                    choice = MIN(choice+1, max_choice-1);

	    } else if (key == KEY_PPAGE) {
	        scrollok (menu, TRUE);
                for (i=0; (i < max_choice); i++) {
                    if (scroll > 0) {
                	wscrl (menu, -1);
                	scroll--;
                	menu_print_item (menu, items[scroll * 2 + 1], 0, FALSE,
                	(items[scroll*2][0] != ':'));
                    } else {
                        if (choice > 0)
                            choice--;
                    }
                }
                scrollok (menu, FALSE);

            } else if (key == KEY_NPAGE) {
                for (i=0; (i < max_choice); i++) {
                    if (scroll+max_choice < item_no) {
			scrollok (menu, TRUE);
			scroll(menu);
			scrollok (menu, FALSE);
                	scroll++;
                	menu_print_item (menu, items[(scroll+max_choice-1)*2+1],
			            max_choice-1, FALSE,
			            (items[(scroll+max_choice-1)*2][0] != ':'));
		    } else {
			if (choice+1 < max_choice)
			    choice++;
		    }
                }

            } else
                choice = i;

            menu_print_item (menu, items[(scroll+choice)*2+1], choice, TRUE,
                       (items[(scroll+choice)*2][0] != ':'));

            menu_print_arrows(dialog, item_no, scroll,
                         box_y, box_x+item_x+1, menu_height);

            wnoutrefresh (dialog);
            wrefresh (menu);

	    continue;		/* wait for another key press */
        }

	switch (key) {
	case KEY_LEFT:
	case TAB:
	case KEY_RIGHT:
	    button = ((key == KEY_LEFT ? --button : ++button) < 0)
			? 2 : (button > 2 ? 0 : button);

	    menu_print_buttons(dialog, height, width, button);
	    wrefresh (menu);
	    break;
	case ' ':
	case 's':
	case 'y':
	case 'n':
	case 'm':
	    /* save scroll info */
	    if ( (f=fopen("lxdialog.scrltmp","w")) != NULL ) {
		fprintf(f,"%d\n",scroll);
		fclose(f);
	    }
	    delwin (dialog);
            fprintf(stderr, "%s\n", items[(scroll + choice) * 2]);
            switch (key) {
            case 's': return 3;
            case 'y': return 3;
            case 'n': return 4;
            case 'm': return 5;
            case ' ': return 6;
            }
	    return 0;
	case 'h':
	case '?':
	    button = 2;
	case '\n':
	    delwin (dialog);
	    if (button == 2) 
            	fprintf(stderr, "%s \"%s\"\n", 
			items[(scroll + choice) * 2],
			items[(scroll + choice) * 2 + 1] +
			first_alpha(items[(scroll + choice) * 2 + 1],""));
	    else
            	fprintf(stderr, "%s\n", items[(scroll + choice) * 2]);

	    remove("lxdialog.scrltmp");
	    return button;
	case 'e':
	case 'x':
	    key = ESC;
	case ESC:
	    break;
	}
    }

    delwin (dialog);
    remove("lxdialog.scrltmp");
    return -1;			/* ESC pressed */
}

/*
 * Display a message box. Program will pause and display an "OK" button
 * if the parameter 'pause' is non-zero.
 */
int
dialog_msgbox (const char *title, const char *prompt, int height, int width,
		int pause)
{
    int i, x, y, key = 0;
    WINDOW *dialog;

    /* center dialog box on screen */
    x = (COLS - width) / 2;
    y = (LINES - height) / 2;

    draw_shadow (stdscr, y, x, height, width);

    dialog = newwin (height, width, y, x);
    keypad (dialog, TRUE);

    draw_box (dialog, 0, 0, height, width, dialog_attr, border_attr);

    if (title != NULL && strlen(title) >= width-2 ) {
	/* truncate long title -- mec */
	char * title2 = malloc(width-2+1);
	memcpy( title2, title, width-2 );
	title2[width-2] = '\0';
	title = title2;
    }

    if (title != NULL) {
	wattrset (dialog, title_attr);
	mvwaddch (dialog, 0, (width - strlen(title))/2 - 1, ' ');
	waddstr (dialog, (char *)title);
	waddch (dialog, ' ');
    }
    wattrset (dialog, dialog_attr);
    print_autowrap (dialog, prompt, width - 2, 1, 2);

    if (pause) {
	wattrset (dialog, border_attr);
	mvwaddch (dialog, height - 3, 0, ACS_LTEE);
	for (i = 0; i < width - 2; i++)
	    waddch (dialog, ACS_HLINE);
	wattrset (dialog, dialog_attr);
	waddch (dialog, ACS_RTEE);

	print_button (dialog, "  Ok  ",
		      height - 2, width / 2 - 4, TRUE);

	wrefresh (dialog);
	while (key != ESC && key != '\n' && key != ' ' &&
               key != 'O' && key != 'o' && key != 'X' && key != 'x')
	    key = wgetch (dialog);
    } else {
	key = '\n';
	wrefresh (dialog);
    }

    delwin (dialog);
    return key == ESC ? -1 : 0;
}

static void back_lines (int n);
static void print_page (WINDOW * win, int height, int width);
static void print_line (WINDOW * win, int row, int width);
static char *get_line (void);
static void print_position (WINDOW * win, int height, int width);

static int hscroll = 0, fd, file_size, bytes_read;
static int begin_reached = 1, end_reached = 0, page_length;
static char *buf, *page;

/*
 * Display text from a file in a dialog box.
 */
int
dialog_textbox (const char *title, const char *file, int height, int width)
{
    int i, x, y, cur_x, cur_y, fpos, key = 0;
    int passed_end;
    char search_term[MAX_LEN + 1];
    WINDOW *dialog, *text;

    search_term[0] = '\0';	/* no search term entered yet */

    /* Open input file for reading */
    if ((fd = open (file, O_RDONLY)) == -1) {
	endwin ();
	fprintf (stderr,
		 "\nCan't open input file in dialog_textbox().\n");
	exit (-1);
    }
    /* Get file size. Actually, 'file_size' is the real file size - 1,
       since it's only the last byte offset from the beginning */
    if ((file_size = lseek (fd, 0, SEEK_END)) == -1) {
	endwin ();
	fprintf (stderr, "\nError getting file size in dialog_textbox().\n");
	exit (-1);
    }
    /* Restore file pointer to beginning of file after getting file size */
    if (lseek (fd, 0, SEEK_SET) == -1) {
	endwin ();
	fprintf (stderr, "\nError moving file pointer in dialog_textbox().\n");
	exit (-1);
    }
    /* Allocate space for read buffer */
    if ((buf = malloc (BUF_SIZE + 1)) == NULL) {
	endwin ();
	fprintf (stderr, "\nCan't allocate memory in dialog_textbox().\n");
	exit (-1);
    }
    if ((bytes_read = read (fd, buf, BUF_SIZE)) == -1) {
	endwin ();
	fprintf (stderr, "\nError reading file in dialog_textbox().\n");
	exit (-1);
    }
    buf[bytes_read] = '\0';	/* mark end of valid data */
    page = buf;			/* page is pointer to start of page to be displayed */

    /* center dialog box on screen */
    x = (COLS - width) / 2;
    y = (LINES - height) / 2;


    draw_shadow (stdscr, y, x, height, width);

    dialog = newwin (height, width, y, x);
    keypad (dialog, TRUE);

    /* Create window for text region, used for scrolling text */
    text = subwin (dialog, height - 4, width - 2, y + 1, x + 1);
    wattrset (text, dialog_attr);
    wbkgdset (text, dialog_attr & A_COLOR);

    keypad (text, TRUE);

    /* register the new window, along with its borders */
    draw_box (dialog, 0, 0, height, width, dialog_attr, border_attr);

    wattrset (dialog, border_attr);
    mvwaddch (dialog, height-3, 0, ACS_LTEE);
    for (i = 0; i < width - 2; i++)
	waddch (dialog, ACS_HLINE);
    wattrset (dialog, dialog_attr);
    wbkgdset (dialog, dialog_attr & A_COLOR);
    waddch (dialog, ACS_RTEE);

    if (title != NULL && strlen(title) >= width-2 ) {
	/* truncate long title -- mec */
	char * title2 = malloc(width-2+1);
	memcpy( title2, title, width-2 );
	title2[width-2] = '\0';
	title = title2;
    }

    if (title != NULL) {
	wattrset (dialog, title_attr);
	mvwaddch (dialog, 0, (width - strlen(title))/2 - 1, ' ');
	waddstr (dialog, (char *)title);
	waddch (dialog, ' ');
    }
    print_button (dialog, " Exit ", height - 2, width / 2 - 4, TRUE);
    wnoutrefresh (dialog);
    getyx (dialog, cur_y, cur_x);	/* Save cursor position */

    /* Print first page of text */
    attr_clear (text, height - 4, width - 2, dialog_attr);
    print_page (text, height - 4, width - 2);
    print_position (dialog, height, width);
    wmove (dialog, cur_y, cur_x);	/* Restore cursor position */
    wrefresh (dialog);

    while ((key != ESC) && (key != '\n')) {
	key = wgetch (dialog);
	switch (key) {
	case 'E':		/* Exit */
	case 'e':
	case 'X':
	case 'x':
	    delwin (dialog);
	    free (buf);
	    close (fd);
	    return 0;
	case 'g':		/* First page */
	case KEY_HOME:
	    if (!begin_reached) {
		begin_reached = 1;
		/* First page not in buffer? */
		if ((fpos = lseek (fd, 0, SEEK_CUR)) == -1) {
		    endwin ();
		    fprintf (stderr,
		      "\nError moving file pointer in dialog_textbox().\n");
		    exit (-1);
		}
		if (fpos > bytes_read) {	/* Yes, we have to read it in */
		    if (lseek (fd, 0, SEEK_SET) == -1) {
			endwin ();
			fprintf (stderr, "\nError moving file pointer in "
				 "dialog_textbox().\n");
			exit (-1);
		    }
		    if ((bytes_read = read (fd, buf, BUF_SIZE)) == -1) {
			endwin ();
			fprintf (stderr,
			     "\nError reading file in dialog_textbox().\n");
			exit (-1);
		    }
		    buf[bytes_read] = '\0';
		}
		page = buf;
		print_page (text, height - 4, width - 2);
		print_position (dialog, height, width);
		wmove (dialog, cur_y, cur_x);	/* Restore cursor position */
		wrefresh (dialog);
	    }
	    break;
	case 'G':		/* Last page */
	case KEY_END:

	    end_reached = 1;
	    /* Last page not in buffer? */
	    if ((fpos = lseek (fd, 0, SEEK_CUR)) == -1) {
		endwin ();
		fprintf (stderr,
		      "\nError moving file pointer in dialog_textbox().\n");
		exit (-1);
	    }
	    if (fpos < file_size) {	/* Yes, we have to read it in */
		if (lseek (fd, -BUF_SIZE, SEEK_END) == -1) {
		    endwin ();
		    fprintf (stderr,
		      "\nError moving file pointer in dialog_textbox().\n");
		    exit (-1);
		}
		if ((bytes_read = read (fd, buf, BUF_SIZE)) == -1) {
		    endwin ();
		    fprintf (stderr,
			     "\nError reading file in dialog_textbox().\n");
		    exit (-1);
		}
		buf[bytes_read] = '\0';
	    }
	    page = buf + bytes_read;
	    back_lines (height - 4);
	    print_page (text, height - 4, width - 2);
	    print_position (dialog, height, width);
	    wmove (dialog, cur_y, cur_x);	/* Restore cursor position */
	    wrefresh (dialog);
	    break;
	case 'K':		/* Previous line */
	case 'k':
	case KEY_UP:
	    if (!begin_reached) {
		back_lines (page_length + 1);

		/* We don't call print_page() here but use scrolling to ensure
		   faster screen update. However, 'end_reached' and
		   'page_length' should still be updated, and 'page' should
		   point to start of next page. This is done by calling
		   get_line() in the following 'for' loop. */
		scrollok (text, TRUE);
		wscrl (text, -1);	/* Scroll text region down one line */
		scrollok (text, FALSE);
		page_length = 0;
		passed_end = 0;
		for (i = 0; i < height - 4; i++) {
		    if (!i) {
			/* print first line of page */
			print_line (text, 0, width - 2);
			wnoutrefresh (text);
		    } else
			/* Called to update 'end_reached' and 'page' */
			get_line ();
		    if (!passed_end)
			page_length++;
		    if (end_reached && !passed_end)
			passed_end = 1;
		}

		print_position (dialog, height, width);
		wmove (dialog, cur_y, cur_x);	/* Restore cursor position */
		wrefresh (dialog);
	    }
	    break;
	case 'B':		/* Previous page */
	case 'b':
	case KEY_PPAGE:
	    if (begin_reached)
		break;
	    back_lines (page_length + height - 4);
	    print_page (text, height - 4, width - 2);
	    print_position (dialog, height, width);
	    wmove (dialog, cur_y, cur_x);
	    wrefresh (dialog);
	    break;
	case 'J':		/* Next line */
	case 'j':
	case KEY_DOWN:
	    if (!end_reached) {
		begin_reached = 0;
		scrollok (text, TRUE);
		scroll (text);	/* Scroll text region up one line */
		scrollok (text, FALSE);
		print_line (text, height - 5, width - 2);
		wnoutrefresh (text);
		print_position (dialog, height, width);
		wmove (dialog, cur_y, cur_x);	/* Restore cursor position */
		wrefresh (dialog);
	    }
	    break;
	case KEY_NPAGE:		/* Next page */
	case ' ':
	    if (end_reached)
		break;

	    begin_reached = 0;
	    print_page (text, height - 4, width - 2);
	    print_position (dialog, height, width);
	    wmove (dialog, cur_y, cur_x);
	    wrefresh (dialog);
	    break;
	case '0':		/* Beginning of line */
	case 'H':		/* Scroll left */
	case 'h':
	case KEY_LEFT:
	    if (hscroll <= 0)
		break;

	    if (key == '0')
		hscroll = 0;
	    else
		hscroll--;
	    /* Reprint current page to scroll horizontally */
	    back_lines (page_length);
	    print_page (text, height - 4, width - 2);
	    wmove (dialog, cur_y, cur_x);
	    wrefresh (dialog);
	    break;
	case 'L':		/* Scroll right */
	case 'l':
	case KEY_RIGHT:
	    if (hscroll >= MAX_LEN)
		break;
	    hscroll++;
	    /* Reprint current page to scroll horizontally */
	    back_lines (page_length);
	    print_page (text, height - 4, width - 2);
	    wmove (dialog, cur_y, cur_x);
	    wrefresh (dialog);
	    break;
	case ESC:
	    break;
	}
    }

    delwin (dialog);
    free (buf);
    close (fd);
    return -1;			/* ESC pressed */
}

/*
 * Go back 'n' lines in text file. Called by dialog_textbox().
 * 'page' will be updated to point to the desired line in 'buf'.
 */
static void
back_lines (int n)
{
    int i, fpos;

    begin_reached = 0;
    /* We have to distinguish between end_reached and !end_reached
       since at end of file, the line is not ended by a '\n'.
       The code inside 'if' basically does a '--page' to move one
       character backward so as to skip '\n' of the previous line */
    if (!end_reached) {
	/* Either beginning of buffer or beginning of file reached? */
	if (page == buf) {
	    if ((fpos = lseek (fd, 0, SEEK_CUR)) == -1) {
		endwin ();
		fprintf (stderr, "\nError moving file pointer in "
			 "back_lines().\n");
		exit (-1);
	    }
	    if (fpos > bytes_read) {	/* Not beginning of file yet */
		/* We've reached beginning of buffer, but not beginning of
		   file yet, so read previous part of file into buffer.
		   Note that we only move backward for BUF_SIZE/2 bytes,
		   but not BUF_SIZE bytes to avoid re-reading again in
		   print_page() later */
		/* Really possible to move backward BUF_SIZE/2 bytes? */
		if (fpos < BUF_SIZE / 2 + bytes_read) {
		    /* No, move less then */
		    if (lseek (fd, 0, SEEK_SET) == -1) {
			endwin ();
			fprintf (stderr, "\nError moving file pointer in "
				 "back_lines().\n");
			exit (-1);
		    }
		    page = buf + fpos - bytes_read;
		} else {	/* Move backward BUF_SIZE/2 bytes */
		    if (lseek (fd, -(BUF_SIZE / 2 + bytes_read), SEEK_CUR)
			== -1) {
			endwin ();
			fprintf (stderr, "\nError moving file pointer "
				 "in back_lines().\n");
			exit (-1);
		    }
		    page = buf + BUF_SIZE / 2;
		}
		if ((bytes_read = read (fd, buf, BUF_SIZE)) == -1) {
		    endwin ();
		    fprintf (stderr, "\nError reading file in back_lines().\n");
		    exit (-1);
		}
		buf[bytes_read] = '\0';
	    } else {		/* Beginning of file reached */
		begin_reached = 1;
		return;
	    }
	}
	if (*(--page) != '\n') {	/* '--page' here */
	    /* Something's wrong... */
	    endwin ();
	    fprintf (stderr, "\nInternal error in back_lines().\n");
	    exit (-1);
	}
    }
    /* Go back 'n' lines */
    for (i = 0; i < n; i++)
	do {
	    if (page == buf) {
		if ((fpos = lseek (fd, 0, SEEK_CUR)) == -1) {
		    endwin ();
		    fprintf (stderr,
			  "\nError moving file pointer in back_lines().\n");
		    exit (-1);
		}
		if (fpos > bytes_read) {
		    /* Really possible to move backward BUF_SIZE/2 bytes? */
		    if (fpos < BUF_SIZE / 2 + bytes_read) {
			/* No, move less then */
			if (lseek (fd, 0, SEEK_SET) == -1) {
			    endwin ();
			    fprintf (stderr, "\nError moving file pointer "
				     "in back_lines().\n");
			    exit (-1);
			}
			page = buf + fpos - bytes_read;
		    } else {	/* Move backward BUF_SIZE/2 bytes */
			if (lseek (fd, -(BUF_SIZE / 2 + bytes_read),
				   SEEK_CUR) == -1) {
			    endwin ();
			    fprintf (stderr, "\nError moving file pointer"
				     " in back_lines().\n");
			    exit (-1);
			}
			page = buf + BUF_SIZE / 2;
		    }
		    if ((bytes_read = read (fd, buf, BUF_SIZE)) == -1) {
			endwin ();
			fprintf (stderr, "\nError reading file in "
				 "back_lines().\n");
			exit (-1);
		    }
		    buf[bytes_read] = '\0';
		} else {	/* Beginning of file reached */
		    begin_reached = 1;
		    return;
		}
	    }
	} while (*(--page) != '\n');
    page++;
}

/*
 * Print a new page of text. Called by dialog_textbox().
 */
static void
print_page (WINDOW * win, int height, int width)
{
    int i, passed_end = 0;

    page_length = 0;
    for (i = 0; i < height; i++) {
	print_line (win, i, width);
	if (!passed_end)
	    page_length++;
	if (end_reached && !passed_end)
	    passed_end = 1;
    }
    wnoutrefresh (win);
}

/*
 * Print a new line of text. Called by dialog_textbox() and print_page().
 */
static void
print_line (WINDOW * win, int row, int width)
{
    int y, x;
    char *line;

    line = get_line ();
    line += MIN (strlen (line), hscroll);	/* Scroll horizontally */
    wmove (win, row, 0);	/* move cursor to correct line */
    waddch (win, ' ');
    waddnstr (win, line, MIN (strlen (line), width - 2));

    getyx (win, y, x);
    /* Clear 'residue' of previous line */
#if OLD_NCURSES
    {
        int i;
        for (i = 0; i < width - x; i++)
	    waddch (win, ' ');
    }
#else
    wclrtoeol(win);
#endif
}

/*
 * Return current line of text. Called by dialog_textbox() and print_line().
 * 'page' should point to start of current line before calling, and will be
 * updated to point to start of next line.
 */
static char *
get_line (void)
{
    int i = 0, fpos;
    static char line[MAX_LEN + 1];

    end_reached = 0;
    while (*page != '\n') {
	if (*page == '\0') {
	    /* Either end of file or end of buffer reached */
	    if ((fpos = lseek (fd, 0, SEEK_CUR)) == -1) {
		endwin ();
		fprintf (stderr, "\nError moving file pointer in "
			 "get_line().\n");
		exit (-1);
	    }
	    if (fpos < file_size) {	/* Not end of file yet */
		/* We've reached end of buffer, but not end of file yet,
		   so read next part of file into buffer */
		if ((bytes_read = read (fd, buf, BUF_SIZE)) == -1) {
		    endwin ();
		    fprintf (stderr, "\nError reading file in get_line().\n");
		    exit (-1);
		}
		buf[bytes_read] = '\0';
		page = buf;
	    } else {
		if (!end_reached)
		    end_reached = 1;
		break;
	    }
	} else if (i < MAX_LEN)
	    line[i++] = *(page++);
	else {
	    /* Truncate lines longer than MAX_LEN characters */
	    if (i == MAX_LEN)
		line[i++] = '\0';
	    page++;
	}
    }
    if (i <= MAX_LEN)
	line[i] = '\0';
    if (!end_reached)
	page++;			/* move pass '\n' */

    return line;
}

/*
 * Print current position
 */
static void
print_position (WINDOW * win, int height, int width)
{
    int fpos, percent;

    if ((fpos = lseek (fd, 0, SEEK_CUR)) == -1) {
	endwin ();
	fprintf (stderr, "\nError moving file pointer in print_position().\n");
	exit (-1);
    }
    wattrset (win, position_indicator_attr);
    wbkgdset (win, position_indicator_attr & A_COLOR);
    percent = !file_size ?
	100 : ((fpos - bytes_read + page - buf) * 100) / file_size;
    wmove (win, height - 3, width - 9);
    wprintw (win, "(%3d%%)", percent);
}

/* use colors by default? */
bool use_colors = 1;

const char *backtitle = NULL;

const char *dialog_result;

/* 
 * Attribute values, default is for mono display
 */
chtype attributes[] =
{
    A_NORMAL,			/* screen_attr */
    A_NORMAL,			/* shadow_attr */
    A_NORMAL,			/* dialog_attr */
    A_BOLD,			/* title_attr */
    A_NORMAL,			/* border_attr */
    A_REVERSE,			/* button_active_attr */
    A_DIM,			/* button_inactive_attr */
    A_REVERSE,			/* button_key_active_attr */
    A_BOLD,			/* button_key_inactive_attr */
    A_REVERSE,			/* button_label_active_attr */
    A_NORMAL,			/* button_label_inactive_attr */
    A_NORMAL,			/* inputbox_attr */
    A_NORMAL,			/* inputbox_border_attr */
    A_NORMAL,			/* searchbox_attr */
    A_BOLD,			/* searchbox_title_attr */
    A_NORMAL,			/* searchbox_border_attr */
    A_BOLD,			/* position_indicator_attr */
    A_NORMAL,			/* menubox_attr */
    A_NORMAL,			/* menubox_border_attr */
    A_NORMAL,			/* item_attr */
    A_REVERSE,			/* item_selected_attr */
    A_BOLD,			/* tag_attr */
    A_REVERSE,			/* tag_selected_attr */
    A_BOLD,			/* tag_key_attr */
    A_REVERSE,			/* tag_key_selected_attr */
    A_BOLD,			/* check_attr */
    A_REVERSE,			/* check_selected_attr */
    A_BOLD,			/* uarrow_attr */
    A_BOLD			/* darrow_attr */
};

/*
 * Table of color values
 */
int color_table[][3] =
{
    {SCREEN_FG, SCREEN_BG, SCREEN_HL},
    {SHADOW_FG, SHADOW_BG, SHADOW_HL},
    {DIALOG_FG, DIALOG_BG, DIALOG_HL},
    {TITLE_FG, TITLE_BG, TITLE_HL},
    {BORDER_FG, BORDER_BG, BORDER_HL},
    {BUTTON_ACTIVE_FG, BUTTON_ACTIVE_BG, BUTTON_ACTIVE_HL},
    {BUTTON_INACTIVE_FG, BUTTON_INACTIVE_BG, BUTTON_INACTIVE_HL},
    {BUTTON_KEY_ACTIVE_FG, BUTTON_KEY_ACTIVE_BG, BUTTON_KEY_ACTIVE_HL},
    {BUTTON_KEY_INACTIVE_FG, BUTTON_KEY_INACTIVE_BG, BUTTON_KEY_INACTIVE_HL},
    {BUTTON_LABEL_ACTIVE_FG, BUTTON_LABEL_ACTIVE_BG, BUTTON_LABEL_ACTIVE_HL},
    {BUTTON_LABEL_INACTIVE_FG, BUTTON_LABEL_INACTIVE_BG,
     BUTTON_LABEL_INACTIVE_HL},
    {INPUTBOX_FG, INPUTBOX_BG, INPUTBOX_HL},
    {INPUTBOX_BORDER_FG, INPUTBOX_BORDER_BG, INPUTBOX_BORDER_HL},
    {SEARCHBOX_FG, SEARCHBOX_BG, SEARCHBOX_HL},
    {SEARCHBOX_TITLE_FG, SEARCHBOX_TITLE_BG, SEARCHBOX_TITLE_HL},
    {SEARCHBOX_BORDER_FG, SEARCHBOX_BORDER_BG, SEARCHBOX_BORDER_HL},
    {POSITION_INDICATOR_FG, POSITION_INDICATOR_BG, POSITION_INDICATOR_HL},
    {MENUBOX_FG, MENUBOX_BG, MENUBOX_HL},
    {MENUBOX_BORDER_FG, MENUBOX_BORDER_BG, MENUBOX_BORDER_HL},
    {ITEM_FG, ITEM_BG, ITEM_HL},
    {ITEM_SELECTED_FG, ITEM_SELECTED_BG, ITEM_SELECTED_HL},
    {TAG_FG, TAG_BG, TAG_HL},
    {TAG_SELECTED_FG, TAG_SELECTED_BG, TAG_SELECTED_HL},
    {TAG_KEY_FG, TAG_KEY_BG, TAG_KEY_HL},
    {TAG_KEY_SELECTED_FG, TAG_KEY_SELECTED_BG, TAG_KEY_SELECTED_HL},
    {CHECK_FG, CHECK_BG, CHECK_HL},
    {CHECK_SELECTED_FG, CHECK_SELECTED_BG, CHECK_SELECTED_HL},
    {UARROW_FG, UARROW_BG, UARROW_HL},
    {DARROW_FG, DARROW_BG, DARROW_HL},
};				/* color_table */

/*
 * Set window to attribute 'attr'
 */
void
attr_clear (WINDOW * win, int height, int width, chtype attr)
{
    int i, j;

    wattrset (win, attr);
    for (i = 0; i < height; i++) {
	wmove (win, i, 0);
	for (j = 0; j < width; j++)
	    waddch (win, ' ');
    }
    touchwin (win);
}

void dialog_clear (void)
{
    attr_clear (stdscr, LINES, COLS, screen_attr);
    /* Display background title if it exists ... - SLH */
    if (backtitle != NULL) {
        int i;

        wattrset (stdscr, screen_attr);
        mvwaddstr (stdscr, 0, 1, (char *)backtitle);
        wmove (stdscr, 1, 1);
        for (i = 1; i < COLS - 1; i++)
            waddch (stdscr, ACS_HLINE);
    }
    wnoutrefresh (stdscr);
}

/*
 * Do some initialization for dialog
 */
void
init_dialog (void)
{
    initscr ();			/* Init curses */
    keypad (stdscr, TRUE);
    cbreak ();
    noecho ();


    if (use_colors)	/* Set up colors */
	color_setup ();


    dialog_clear ();
}

/*
 * Setup for color display
 */
void
color_setup (void)
{
    int i;

    if (has_colors ()) {	/* Terminal supports color? */
	start_color ();

	/* Initialize color pairs */
	for (i = 0; i < ATTRIBUTE_COUNT; i++)
	    init_pair (i + 1, color_table[i][0], color_table[i][1]);

	/* Setup color attributes */
	for (i = 0; i < ATTRIBUTE_COUNT; i++)
	    attributes[i] = C_ATTR (color_table[i][2], i + 1);
    }
}

/*
 * End using dialog functions.
 */
void
end_dialog (void)
{
    endwin ();
}


/*
 * Print a string of text in a window, automatically wrap around to the
 * next line if the string is too long to fit on one line. Newline
 * characters '\n' are replaced by spaces.  We start on a new line
 * if there is no room for at least 4 nonblanks following a double-space.
 */
void
print_autowrap (WINDOW * win, const char *prompt, int width, int y, int x)
{
    int newl, cur_x, cur_y;
    int i, prompt_len, room, wlen;
    char tempstr[MAX_LEN + 1], *word, *sp, *sp2;

    strcpy (tempstr, prompt);

    prompt_len = strlen(tempstr);
	
    /*
     * Remove newlines
     */
    for(i=0; i<prompt_len; i++) {
	if(tempstr[i] == '\n') tempstr[i] = ' ';
    }

    if (prompt_len <= width - x * 2) {	/* If prompt is short */
	wmove (win, y, (width - prompt_len) / 2);
	waddstr (win, tempstr);
    } else {
	cur_x = x;
	cur_y = y;
	newl = 1;
	word = tempstr;
	while (word && *word) {
	    sp = index(word, ' ');
	    if (sp)
	        *sp++ = 0;

	    /* Wrap to next line if either the word does not fit,
	       or it is the first word of a new sentence, and it is
	       short, and the next word does not fit. */
	    room = width - cur_x;
	    wlen = strlen(word);
	    if (wlen > room ||
	       (newl && wlen < 4 && sp && wlen+1+strlen(sp) > room
		     && (!(sp2 = index(sp, ' ')) || wlen+1+(sp2-sp) > room))) {
		cur_y++;
		cur_x = x;
	    }
	    wmove (win, cur_y, cur_x);
	    waddstr (win, word);
	    getyx (win, cur_y, cur_x);
	    cur_x++;
	    if (sp && *sp == ' ') {
	        cur_x++;	/* double space */
		while (*++sp == ' ');
		newl = 1;
	    } else
	        newl = 0;
	    word = sp;
	}
    }
}

/*
 * Print a button
 */
void
print_button (WINDOW * win, const char *label, int y, int x, int selected)
{
    int i, temp;

    wmove (win, y, x);
    wattrset (win, selected ? button_active_attr : button_inactive_attr);
    waddstr (win, "<");
    temp = strspn (label, " ");
    label += temp;
    wattrset (win, selected ? button_label_active_attr
	      : button_label_inactive_attr);
    for (i = 0; i < temp; i++)
	waddch (win, ' ');
    wattrset (win, selected ? button_key_active_attr
	      : button_key_inactive_attr);
    waddch (win, label[0]);
    wattrset (win, selected ? button_label_active_attr
	      : button_label_inactive_attr);
    waddstr (win, (char *)label + 1);
    wattrset (win, selected ? button_active_attr : button_inactive_attr);
    waddstr (win, ">");
    wmove (win, y, x + temp + 1);
}

/*
 * Draw a rectangular box with line drawing characters
 */
void
draw_box (WINDOW * win, int y, int x, int height, int width,
	  chtype box, chtype border)
{
    int i, j;

    wattrset (win, 0);
    for (i = 0; i < height; i++) {
	wmove (win, y + i, x);
	for (j = 0; j < width; j++)
	    if (!i && !j)
		waddch (win, border | ACS_ULCORNER);
	    else if (i == height - 1 && !j)
		waddch (win, border | ACS_LLCORNER);
	    else if (!i && j == width - 1)
		waddch (win, box | ACS_URCORNER);
	    else if (i == height - 1 && j == width - 1)
		waddch (win, box | ACS_LRCORNER);
	    else if (!i)
		waddch (win, border | ACS_HLINE);
	    else if (i == height - 1)
		waddch (win, box | ACS_HLINE);
	    else if (!j)
		waddch (win, border | ACS_VLINE);
	    else if (j == width - 1)
		waddch (win, box | ACS_VLINE);
	    else
		waddch (win, box | ' ');
    }
}

/*
 * Draw shadows along the right and bottom edge to give a more 3D look
 * to the boxes
 */
void
draw_shadow (WINDOW * win, int y, int x, int height, int width)
{
    int i;

    if (has_colors ()) {	/* Whether terminal supports color? */
	wattrset (win, shadow_attr);
	wmove (win, y + height, x + 2);
	for (i = 0; i < width; i++)
	    waddch (win, winch (win) & A_CHARTEXT);
	for (i = y + 1; i < y + height + 1; i++) {
	    wmove (win, i, x + width);
	    waddch (win, winch (win) & A_CHARTEXT);
	    waddch (win, winch (win) & A_CHARTEXT);
	}
	wnoutrefresh (win);
    }
}

/*
 *  Return the position of the first alphabetic character in a string.
 */
int
first_alpha(const char *string, const char *exempt)
{
	int i, in_paren=0, c;

	for (i = 0; i < strlen(string); i++) {
		c = tolower(string[i]);

		if (strchr("<[(", c)) ++in_paren;
		if (strchr(">])", c)) --in_paren;

		if ((! in_paren) && isalpha(c) && 
		     strchr(exempt, c) == 0)
			return i;
	}

	return 0;
}

/*
 * Display termination buttons
 */
static void
yesno_print_buttons(WINDOW *dialog, int height, int width, int selected)
{
    int x = width / 2 - 10;
    int y = height - 2;

    print_button (dialog, " Yes ", y, x, selected == 0);
    print_button (dialog, "  No  ", y, x + 13, selected == 1);

    wmove(dialog, y, x+1 + 13*selected );
    wrefresh (dialog);
}

/*
 * Display a dialog box with two buttons - Yes and No
 */
int
dialog_yesno (const char *title, const char *prompt, int height, int width)
{
    int i, x, y, key = 0, button = 0;
    WINDOW *dialog;

    /* center dialog box on screen */
    x = (COLS - width) / 2;
    y = (LINES - height) / 2;

    draw_shadow (stdscr, y, x, height, width);

    dialog = newwin (height, width, y, x);
    keypad (dialog, TRUE);

    draw_box (dialog, 0, 0, height, width, dialog_attr, border_attr);
    wattrset (dialog, border_attr);
    mvwaddch (dialog, height-3, 0, ACS_LTEE);
    for (i = 0; i < width - 2; i++)
	waddch (dialog, ACS_HLINE);
    wattrset (dialog, dialog_attr);
    waddch (dialog, ACS_RTEE);

    if (title != NULL && strlen(title) >= width-2 ) {
	/* truncate long title -- mec */
	char * title2 = malloc(width-2+1);
	memcpy( title2, title, width-2 );
	title2[width-2] = '\0';
	title = title2;
    }

    if (title != NULL) {
	wattrset (dialog, title_attr);
	mvwaddch (dialog, 0, (width - strlen(title))/2 - 1, ' ');
	waddstr (dialog, (char *)title);
	waddch (dialog, ' ');
    }

    wattrset (dialog, dialog_attr);
    print_autowrap (dialog, prompt, width - 2, 1, 3);

    yesno_print_buttons(dialog, height, width, 0);

    while (key != ESC) {
	key = wgetch (dialog);
	switch (key) {
	case 'Y':
	case 'y':
	    delwin (dialog);
	    return 0;
	case 'N':
	case 'n':
	    delwin (dialog);
	    return 1;

	case TAB:
	case KEY_LEFT:
	case KEY_RIGHT:
	    button = ((key == KEY_LEFT ? --button : ++button) < 0)
			? 1 : (button > 1 ? 0 : button);

	    yesno_print_buttons(dialog, height, width, button);
	    wrefresh (dialog);
	    break;
	case ' ':
	case '\n':
	    delwin (dialog);
	    return button;
	case ESC:
	    break;
	}
    }

    delwin (dialog);
    return -1;			/* ESC pressed */
}
