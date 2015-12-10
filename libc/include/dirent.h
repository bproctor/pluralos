
/*
 *  dirent.h -- format of directory entries
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
 * $Id: dirent.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __DIRENT_H__
#define __DIRENT_H__

#ifndef __INO_T
#define __INO_T
typedef int ino_t;
#endif

typedef int DIR;

struct dirent
{
   ino_t d_ino;      /* file serial number */
   char  d_name[];   /* name of entry */
};

int            closedir (DIR *);
DIR           *opendir (const char *);
struct dirent *readdir (DIR *);
int            readdir_r (DIR *, struct dirent *, struct dirent **);
void           rewinddir (DIR *);
void           seekdir (DIR *, long);
long           telldir (DIR *);

#endif /* __DIRENT_H__ */
