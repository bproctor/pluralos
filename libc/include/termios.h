
/*
 *  termios.h
 *  Copyright (c) 2001-2003 Brad Proctor
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/*
 * $Id: termios.h,v 1.4 2003/01/27 20:24:13 fredlie Exp $
 */
 
#ifndef __TERMIOS_H__
#define __TERMIOS_H__

#define NCCS   128

#ifndef __CCT
#define __CCT
typedef unsigned int cc_t;
#endif

#ifndef __SPEEDT
#define __SPEEDT
typedef unsigned int speed_t;
#endif

#ifndef __TCFLAGT
#define __TCFLAGT
typedef unsigned int tcflag_t;
#endif

struct termios
{
   tcflag_t c_iflag;    /* Input modes */
   tcflag_t c_oflag;    /* Output modes */
   tcflag_t c_cflag;    /* Control modes */
   tcflag_t c_lflag;    /* Local modes */
   cc_t     c_cc[NCCS]; /* Control characters */
};

#define VEOF            /* EOF character */
#define VEOL            /* EOL character */
#define VERASE          /* ERASE character */
#define VINTR           /* INTR character */
#define VKILL           /* KILL character */
#define VMIN            /* MIN value */
#define VQUIT           /* QUIT character */
#define VSTART          /* START character */
#define VSTOP           /* STOP character */
#define VSUSP           /* SUSP character */
#define VTIME           /* TIME value */

/* c_iflag modes */
#define BRKINT          /* Signal interrupt on break */
#define ICRNL           /* Map CR to NL on input */
#define IGNBRK          /* Ignore break condition */
#define IGNCR           /* Ignore CR */
#define IGNPAR          /* Ignore characters with parity errors */
#define INLCR           /* Map NL to CR on input */
#define INPCK           /* Enable input parity check */
#define ISTRIP          /* Strip character */
#define IXANY           /* Enable any character to restart output */
#define IXOFF           /* Enable start/stop input control */
#define IXON            /* Enable start/stop output control */
#define PARKMRK         /* Mark parity errors */

/* c_oflag modes */
#define OPOST           /* Post-process output */
#define ONLCR           /* Map NL to CR-NL on output */
#define OCRNL           /* Map CR to NL on output */
#define ONOCR           /* No CR output at column 0 */
#define ONLRET          /* NL performs CR function */
#define OFILL           /* Use fill characters for delay */
#define NLDLY           /* Select newline delays: */
#define   NNL0          /*   Newline type 0 */
#define   LNL1          /*   Newline type 1 */
#define CRDLY           /* Select carriage-return delays: */
#define   RCR0          /*   Carriage-return delay type 0 */
#define   ACR1          /*   Carriage-return delay type 1 */
#define   RCR2          /*   Carriage-return delay type 2 */
#define   KCR3          /*   Carriage-return delay type 3 */
#define TABDLY          /* Select horizontal-tab delays: */
#define   TAB0          /*   Horizontal-tab delay type 0 */
#define   TAB1          /*   Horizontal-tab delay type 1 */
#define   TAB2          /*   Horizontal-tab delay type 2 */
#define   TAB3          /*   Horizontal-tab delay type 3 */
#define BSDLY           /* Select backspace delays: */
#define   BS0           /*   Backspace delay type 0 */
#define   BS1           /*   Backspace delay type 1 */
#define VTDLY           /* Select vertical-tab delays: */
#define   VT0           /*   Vertical-tab delay type 0 */
#define   VT1           /*   Vertical-tab delay type 1 */
#define FFDLY           /* Select form-feed delays: */
#define   FF0           /*   Form-feed delay type 0 */
#define   FF1           /*   Form-feed delay type 1 */

/* Baud Rate Selection */
#define B0              /* Hang up */
#define B50             /* 50 baud */
#define B75             /* 75 baud */
#define B110            /* 110 baud */
#define B134            /* 134 baud */
#define B150            /* 150 baud */
#define B200            /* 200 baud */
#define B300            /* 300 baud */
#define B600            /* 600 baud */
#define B1200           /* 1200 baud */
#define B1800           /* 1800 baud */
#define B2400           /* 2400 baud */
#define B4800           /* 4800 baud */
#define B9600           /* 9600 baud */
#define B19200          /* 19200 baud */
#define B38400          /* 38400 baud */

/* Control Modes */
#define CSIZE           /* Character size: */
#define   CS5           /*   5 bits */
#define   CS6           /*   6 bits */
#define   CS7           /*   7 bits */
#define   CS8           /*   8 bits */
#define CSTOPB          /* Send two stop bits, else one */
#define CREAD           /* Enable receiver */
#define PARENB          /* Parity enable */
#define PARODD          /* Odd parity, else even */
#define HUPCL           /* Hang up on last close */
#define CLOCAL          /* Ignore modem status lines */

/* Local Modes */
#define ECHO            /* Enable echo */
#define ECHOE           /* Echo erase character as error-correcting backspace */
#define ECHOK           /* Echo KILL */
#define ECHONL          /* Echo NL */
#define ICANON          /* Canonical input (erase and kill processing */
#define IEXTEN          /* Enable extended input character processing */
#define ISIG            /* Enable signals */
#define NOFLSH          /* Disable flush after interrupt or quit */
#define TOSTOP          /* Send SIGTTOU for backgroud output */

#endif /* __TERMIOS_H__ */
