
/*
 *  tar.h
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
 * $Id: tar.h,v 1.4 2003/01/27 20:24:13 fredlie Exp $
 */

#ifndef __TAR_H__
#define __TAR_H__

#define TMAGIC    "ustar"
#define TMAGLEN   6
#define TVERSION  "00"
#define TVERSLEN  2

enum TypeFlag
{
   REGTYPE  = '0',      /* Regular file */
   AREGTYPE = '\0',     /* Regular file */
   LNKTYPE  = '1',      /* Link */
   SYMLINK  = '2',      /* Symbolic Link */
   CHRTYPE  = '3',      /* Character special */
   BLKTYPE  = '4',      /* Block special */
   DIRTYPE  = '5',      /* Directory */
   FIFOTYPE = '6',      /* FIFO special */
   CONTTYPE = '7',      /* Reserved */
};

#define TSUID   04000   /* Set UID on execution */
#define TSGID   02000   /* Set GID on execution */
#define TSVTX   01000   /* On directories, restricted deletion flag */
#define TUREAD  00400   /* Read by owner */
#define TUWRITE 00200   /* Write by owner */
#define TUEXEC  00100   /* Execute/search by owner */
#define TGREAD  00040   /* Read by group */
#define TGWRITE 00020   /* Write by group */
#define TGEXEC  00010   /* Execute/search by group */
#define TOREAD  00004   /* Read by other */
#define TOWRITE 00002   /* Write by other */
#define TOEXEC  00001   /* Execute/search by other */

#endif /* __TAR_H__ */
