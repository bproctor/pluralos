
/*
 *  getnum_d.c
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
 * $Id: getnum_d.c,v 1.1 2003/02/15 17:16:34 fredlie Exp $
 */

#include <ctype.h>
#include "utils.h"

double (getnum_d)(const char *s)
{
   char sign = '+';
   char found_decimal = 0;
   char found_exponent = 0;
   char exponent_sign = '+';

   int digits = 0;
   double num = 0, num1 = 0, num2 = 0, exp = 0;

   if (*s == '-' || *s == '+')
      sign = *s++;

   while (*s)
   {
      switch (*s)
      {
         case '\0':
            break;
         case '.':
            if (found_decimal)
               terror ("malformed floating-point number `%s'", s);
            found_decimal = 1;
            break;
         case '0': case '1': case '2':
         case '3': case '4': case '5':
         case '6': case '7': case '8':
         case '9':
            if (found_decimal)
               num2 = num2 * 10 + *s - '0', digits++;
            else if (found_exponent)
               exp = exp * 10 + *s - '0';
            else
               num1 = num1 * 10 + *s - '0';
            break;
         case 'e':
         case 'E':
            if (*++s == '-')
               exponent_sign = '-';
            else if (*s == '+')
               exponent_sign = '+';
            found_exponent = 1;
            break;
         default:
            break;
      }
      ++s;
   }      

   while (digits--)
      num2 /= 10;

   num = num1 + num2;

   if (exponent_sign == '-')
      while (exp--)
         num /= 10;
   else
      while (exp--)
         num *= 10;

   if (sign == '-')
      num = -num;

   return (num);
}
