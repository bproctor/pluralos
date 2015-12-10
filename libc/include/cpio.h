
/*
 *  cpio.h -- cpio archive values
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
 * $Id: cpio.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __CPIO_H__
#define __CPIO_H__

#define C_IRUSR      0000400  /* Read by owner */
#define C_IWUSR      0000200  /* Write by owner */
#define C_IXUSR      0000100  /* Execute by owner */
#define C_IRGRP      0000040  /* Read by group */
#define C_IWGRP      0000020  /* Write by group */
#define C_IXGRP      0000010  /* Execute by group */
#define C_IROTH      0000004  /* Read by other */
#define C_IWOTH      0000002  /* Write by other */
#define C_IXOTH      0000001  /* Execute by other */
#define C_ISUID      0004000  /* Set user ID */
#define C_ISGID      0002000  /* Set group ID */
#define C_ISVTX      0001000  /* On directories, restricted deletion flag */
#define C_ISDIR      0040000  /* Directory */
#define C_ISFIFO     0010000  /* Fifo */
#define C_ISREG      0100000  /* Regular file */
#define C_ISBLK      0060000  /* Block special */
#define C_ISCHR      0020000  /* Character special */
#define C_ISCTG      0110000  /* Reserved */
#define C_ISLNK      0120000  /* Symbolic link */
#define C_ISSOCK     0140000  /* Socket */

#define MAGIC        "070707"

#endif /* __CPIO_H__ */
