
/*
 *  key.c
 *  Copyright (c) 2001-2002 Brad Proctor
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
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: key.c,v 1.6 2002/12/02 04:16:28 fredlie Exp $
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <system.h>
#include <io.h>
#include <sys/interrupt.h>
#include <stdio.h>
#include <device.h>

Device kbd;

void int_keyboard (void);

#define LED_SCOLL_LOCK     1
#define LED_NUM_LOCK       2
#define LED_CAPS_LOCK      4

#define SCROLL_LOCK        0x00000001
#define NUM_LOCK           0x00000002
#define CAPS_LOCK          0x00000004
#define CTRL_LEFT_DOWN     0x00000008
#define CTRL_RIGHT_DOWN    0x00000010
#define SHIFT_LEFT_DOWN    0x00000020
#define SHIFT_RIGHT_DOWN   0x00000040
#define ALT_LEFT_DOWN      0x00000080
#define ALT_RIGHT_DOWN     0x00000100
#define NUM_PAD            0x00000200

uchar led_status;


/* The first value is the key code, the second is the shift code */

static const uchar keymap[128][2] = 
{
   {0x00, 0x00},  /*          */
   {0x1B, 0x00},  /* esc      */
   {0x31, 0x21},  /* '1'  '!' */
   {0x32, 0x40},  /* '2'  '@' */
   {0x33, 0x23},  /* '3'  '#' */
   {0x34, 0x24},  /* '4'  '$' */
   {0x35, 0x25},  /* '5'  '%' */
   {0x36, 0x5E},  /* '6'  '^' */
   {0x37, 0x26},  /* '7'  '&' */
   {0x38, 0x2A},  /* '8'  '*' */
   {0x39, 0x28},  /* '9'  '(' */
   {0x30, 0x29},  /* '0'  ')' */
   {0x2D, 0x5F},  /* '-'  '_' */
   {0x3D, 0x2B},  /* '='  '+' */
   {0x08, 0x08},  /* bs       */
   {0x09, 0x09},  /* tab      */
   {0x71, 0x51},  /* 'q'  'Q' */
   {0x77, 0x57},  /* 'w'  'W' */
   {0x65, 0x45},  /* 'e'  'E' */
   {0x72, 0x52},  /* 'r'  'R' */
   {0x74, 0x54},  /* 't'  'T' */
   {0x79, 0x59},  /* 'y'  'Y' */
   {0x75, 0x55},  /* 'u'  'U' */
   {0x69, 0x49},  /* 'i'  'I' */
   {0x6F, 0x4F},  /* 'o'  'O' */
   {0x70, 0x50},  /* 'p'  'P' */
   {0x5B, 0x7B},  /* '['  '{' */
   {0x5D, 0x7D},  /* ']'  '}' */
   {0x0D, 0x00},  /* cr       */
   {0x00, 0x00},  /* lctrl    */
   {0x61, 0x41},  /* 'a'  'A' */
   {0x73, 0x53},  /* 's'  'S' */
   {0x64, 0x44},  /* 'd'  'D' */
   {0x66, 0x46},  /* 'f'  'F' */
   {0x67, 0x47},  /* 'g'  'G' */
   {0x68, 0x48},  /* 'h'  'H' */
   {0x6A, 0x4A},  /* 'j'  'J' */
   {0x6B, 0x4B},  /* 'k'  'K' */
   {0x6C, 0x4C},  /* 'l'  'L' */
   {0x3B, 0x3A},  /* ';'  ':' */
   {0x27, 0x22},  /* '\'' '\"' */
   {0x60, 0x7E},  /* '`'  '~' */
   {0x00, 0x00},  /* lshift   */
   {0x5C, 0x7C},  /* '\'  '|' */
   {0x7A, 0x5A},  /* 'z'  'Z' */
   {0x78, 0x58},  /* 'x'  'X' */
   {0x63, 0x43},  /* 'c'  'C' */
   {0x76, 0x56},  /* 'v'  'V' */
   {0x62, 0x42},  /* 'b'  'B' */
   {0x6E, 0x4E},  /* 'n'  'N' */
   {0x6D, 0x4D},  /* 'm'  'M' */
   {0x2C, 0x3C},  /* ','  '<' */
   {0x2E, 0x3E},  /* '.'  '>' */
   {0x2F, 0x3F},  /* '/'  '?' */
   {0x00, 0x00},  /* rshift   */
   {0x2A, 0x2A},  /* num '*'  */
   {0x00, 0x00},  /* lalt     */
   {0x20, 0x20},  /* space    */
   {0x0F, 0x0F},  /* F1       */
   {0x10, 0x10},  /* F2       */
   {0x11, 0x11},  /* F3       */
   {0x12, 0x12},  /* F4       */
   {0x13, 0x13},  /* F5       */
   {0x14, 0x14},  /* F6       */
   {0x15, 0x15},  /* F7       */
   {0x16, 0x16},  /* F8       */
   {0x17, 0x17},  /* F9       */
   {0x18, 0x18},  /* F10      */
   {0x00, 0x00},  /* num lock */
   {0x00, 0x00},  /* scroll lock */
   {0x86, 0x37},  /* num '7'     num 'home' */
   {0x81, 0x38},  /* num '8'     num 'up'   */
   {0x85, 0x39},  /* num '9'     num 'pgup' */
   {0xAD, 0xAD},  /* num '-'                */
   {0x83, 0x34},  /* num '4'     num 'left' */
   {0x9F, 0x35},  /* num '5'     num pad    */
   {0x84, 0x36},  /* num '6'     num 'right' */
   {0xAB, 0xAB},  /* num '+'                */
   {0x8B, 0x31},  /* num '1'     num 'end'  */
   {0x82, 0x32},  /* num '2'     num 'down' */
   {0x8C, 0x33},  /* num '3'     num 'pgdn' */
   {0x8E, 0x30},  /* num '0'     num 'ins'  */
   {0xFF, 0x2E},  /* num '.'     num 'del'  */
   {0x1C, 0x1C},  /* prscr       sysreq     */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x19, 0x19},  /* F11      */
   {0x1A, 0x1A},  /* F12      */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x0E, 0x0E},  /* ins      */
   {0x0B, 0x0B},  /* end      */
   {0x02, 0x02},  /* down     */
   {0x0C, 0x0C},  /* pgdn     */
   {0x03, 0x03},  /* left     */
   {0x00, 0x00},  /*          */
   {0x04, 0x04},  /* right    */
   {0x06, 0x06},  /* home     */
   {0x01, 0x01},  /* up       */
   {0x05, 0x05},  /* pgup     */
   {0x7F, 0x7F},  /* del      */
   {0xAF, 0xAF},  /* num '/'  */
   {0x8D, 0x8D},  /* num 'enter' */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
   {0x00, 0x00},  /*          */
};


static void set_leds (uchar led_mask)
{
   outb (0x60, 0xED);
   while (inb (0x64) & 2);
   outb (0x60, led_mask);
   while (inb (0x64) & 2);
}

static ulong kbd_stat (ulong s)
{
   return (0);
}

static ulong kbd_op (ulong com)
{
   return (0);
}

static ulong kbd_init (void)
{
   return (0);
}

void __init__ init_keyboard (void)
{
   puts ("Initializing keyboard... ");
   InterruptAttach (1, int_keyboard, "Keyboard");
   led_status = 0;
   set_leds (0);
   kbd.init = kbd_init;
   kbd.op = kbd_op;
   kbd.stat = kbd_stat;
   puts ("done.\n");
}

asm (
"  .text                   \n"
"  .align   16             \n"
"  .globl   int_keyboard   \n"
"int_keyboard:             \n"
"     pushal               \n"
"     movb     $0x20,%al   \n"
"     outb     %al,$0x20   \n"
"     popal                \n"
"     iret                 \n");
