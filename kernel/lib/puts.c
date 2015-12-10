
/*
 *  puts.c
 *  Modified for Plural by Brad Proctor.
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
 * $Id: puts.c,v 1.5 2002/12/02 04:06:57 fredlie Exp $
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <io.h>
#include <config.h>
#include <sys/types.h>

static unsigned short *video = (unsigned short *)0xB8000;
static int orig_x = 0, orig_y = 0;

static inline void __con_set_xy (void)
{
   ulong pos = (orig_y * CONFIG_ROWS + orig_x) * 2;
   outb (0x3D4, 14);
   outb (0x3D5, (unsigned char)(pos >> 9));
   outb (0x3D4, 15);
   outb (0x3D5, (unsigned char)(pos >> 1));
}

void con_set_xy (int x, int y)
{
   ulong pos = (y * CONFIG_ROWS + x) * 2;
   outb (0x3D4, 14);
   outb (0x3D5, (unsigned char)(pos >> 9));
   outb (0x3D4, 15);
   outb (0x3D5, (unsigned char)(pos >> 1));
}

void con_get_xy (int *x, int *y)
{
   *x = orig_x;
   *y = orig_y;
}

void con_clear_screen (void)
{
   ulong i;
   for (i = 0; i < CONFIG_LINES * CONFIG_ROWS; ++i)
      video[i] = (7 << 8)|' ';
   orig_x = 0, orig_y = 0;
   __con_set_xy ();
}

void con_putc (int x, int y, int attr, char c)
{
   video[y * CONFIG_ROWS + x] = (attr << 8)|c;
}

void con_puts (int x, int y, int attr, const char *s)
{
   orig_x = x;
   orig_y = y;
   cputs (attr, s);
}

static char buf[1024];

int con_printf (int x, int y, int attr, const char *fmt, ...)
{
   int i;
   orig_x = x;
   orig_y = y;
   va_list ap;
   va_start (ap, fmt);
   i = vsprintf (buf, fmt, ap);
   cputs (attr, buf);
   va_end (ap);
   return (i);
}

static inline void scroll (void)
{
   int i;
   memcpy (video, video + CONFIG_ROWS * 2, (CONFIG_LINES - 1) * CONFIG_ROWS * 2);
   for (i = (CONFIG_LINES - 1) * CONFIG_ROWS; i < CONFIG_LINES * CONFIG_ROWS; i++)
      video[i] = (7 << 8)|' ';
}

void cputs (int attr, const char *s)
{
   ulong x, y;
   char c;

   x = orig_x;
   y = orig_y;
   
   while ((c = *s++) != '\0')
   {
      if (c == '\n')
      {  
         x = 0;
         if (++y >= CONFIG_LINES)
         {
            scroll ();
            --y;
         }
      }
      else
      {
         video[y * CONFIG_ROWS + x] = (attr << 8) | c;
         if (++x >= CONFIG_ROWS)
         {
            x = 0;
            if (++y >= CONFIG_LINES)
            {
               scroll ();
               --y;
            }
         }
      }
   }

   orig_x = x;
   orig_y = y;
   __con_set_xy ();
}
