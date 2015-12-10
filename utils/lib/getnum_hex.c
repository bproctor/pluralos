
/*
 *  getnum_hex.c
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
 * $Id: getnum_hex.c,v 1.1 2003/02/16 15:27:15 fredlie Exp $
 */

#include <ctype.h>
#include "utils.h"

long long (getnum_hex)(const char *s)
{
   char sign = '+';
   long long i = 0;

   if (*s == '-' || *s == '+')
      sign = *s++;

   if (!isdigit (*s))
      terror ("malformed number `%s'", s);
   
   while (isxdigit (*s))
      i = (i << 4) + *s++ - '0';
   
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
