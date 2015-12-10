
/*
 *  locale.h -- category macros
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: locale.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __LOCALE_H__
#define __LOCALE_H__

#ifndef NULL
#define NULL   ((void *)0)
#endif

#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MESSAGES     3
#define LC_MONETARY     4
#define LC_NUMERIC      5
#define LC_TIME         6

struct lconv
{
   char *currency_symbol;
   char *decimal_point;
   char *grouping;
   char *int_curr_symbol;
   char *mon_decimal_point;
   char *mon_grouping;
   char *mon_thousands_sep;
   char *negative_sign;
   char *positive_sign;
   char *thousands_sep;
   char  frac_digits;
   char  int_frac_digits;
   char  n_cs_precedes;
   char  n_sep_by_space;
   char  n_sign_posn;
   char  p_cs_precedes;
   char  p_sep_by_space;
   char  p_sign_posn;
};

struct lconv *localeconv (void);
char setlocale (int, const char *);

#endif /* __LOCALE_H__ */
