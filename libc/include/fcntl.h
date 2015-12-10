
/*
 *  fcntl.h -- file control options
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
 * $Id: fcntl.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __FCNTL_H__
#define __FCNTL_H__

#ifndef __SYS_STAT_H__
#include <sys/stat.h>
#endif

#ifndef __UNISTD_H__
#include <unistd.h>
#endif

#define F_DUPFD      1
#define F_GETFD      2
#define F_SETFD      3
#define F_GETFL      4
#define F_SETFL      5
#define F_GETLK      6
#define F_SETLK      7
#define F_SETLKW     8
#define FD_CLOEXEC   9

#define F_RDLCK      1
#define F_UNLCK      2
#define F_WRLCK      3

#define O_CREAT      0x0000
#define O_EXCL       0x0001
#define O_NOCTTY     0x0002
#define O_TRUNC      0x0004
#define O_APPEND     0x0008
#define O_DSYNC      0x0010
#define O_NONBLOCK   0x0020
#define O_RSYNC      0x0040
#define O_SYNC       0x0080
#define O_ACCMODE    0x0100
#define O_RDONLY     0x0200
#define O_RDWR       0x0400
#define O_WRONLY     0x0800

struct flock
{
   short l_type;
   short l_whence;
   off_t l_start;
   off_t l_len;
   pid_t l_pid;
};

int creat (const char *, mode_t);
int fcntl (int, int, ...);
int open (const char *, int, ...);

#endif /* __FCNTL_H__ */
