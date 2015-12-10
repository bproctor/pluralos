
/*
 *  getnum_ll.c
 *  Copyright (c) 2003 Brad Proctor
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
 * $Id: getnum_ll.c,v 1.3 2003/02/16 18:46:40 fredlie Exp $
 */

#include <ctype.h>
#include "utils.h"

long long (getnum_ll)(const char *s)
{
   char sign = '+';
   long long i = 0;

   if (*s == '-' || *s == '+')
      sign = *s++;

   if (!isdigit (*s))
      terror ("malformed number `%s'", s);

   if (*s == '0')
   {
      if (*++s == 'x' || *s == 'X')
      {
         while (1)
         {
            if (isdigit (*++s))
               i = (i << 4) + *s - '0';
            else if (*s >= 'a' && *s <= 'f')
               i = (i << 4) + *s - 'a' + 10;
            else if (*s >= 'A' && *s <= 'F')
               i = (i << 4) + *s - 'A' + 10;
            else
               break;
         }
      }
      else
      {
         while (*s >= '0' && *s <= '7')
            i = (i << 3) + *s - '0';
      }
   }
   else
   {
      while (isdigit (*s))
         i = (i * 10) + *s++ - '0';
   }
   
   switch (*s)
   {
      case '\0':
         break;
      case 'k':
      case 'K':
         if (*++s == 'b')
            i *= 1000;
         else if (*s == 'B' || *s == '\0')
            i <<= 10;
         else
            terror ("malformed number `%s'", s);
         break;
      case 'm':
      case 'M':
         if (*++s == 'b')
            i *= 1000000;
         else if (*s == 'B' || *s == '\0')
            i <<= 20;
         else
            terror ("malformed number `%s'", s);
         break;
      case 'g':
      case 'G':
         if (*++s == 'b')
            i *= 1000000000;
         else if (*s == 'B' || *s == '\0')
            i <<= 30;
         else
            terror ("malformed number `%s'", s);
      default:
         terror ("malformed number `%s'", s);
   }

   if (sign == '-')
      i = -i;
      
   return (i);
}
