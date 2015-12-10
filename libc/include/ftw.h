
/*
 *  ftw.h
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
 * $Id: ftw.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __FTW_H__
#define __FTW_H__

struct FTW
{
   int base;
   int level;
};

#define FTW_F
#define FTW_D
#define FTW_DNR
#define FTW_DP
#define FTW_NS
#define FTW_SL
#define FTW_SLN

#define FTW_PHYS
#define FTW_MOUNT
#define FTW_DEPTH
#define FTW_CHDIR

int ftw (const char *, int (*)(const char *,
   const struct stat *, int), int);

int nftw (const char *, int (*)(const char *,
   const struct stat *, int, struct FTW *), int, int);

#endif /* __FTW_H__ */
