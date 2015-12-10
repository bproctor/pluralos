
/*
 *  utmpx.h -- user accounting database definitions
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
 * $Id: utmpx.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __UTMPX_H__
#define __UTMPX_H__

#ifndef __SYS_TIME_H__
#include <time.h>
#endif

#ifndef __PIDT
#define __PIDT
typedef unsigned int pid_t;
#endif

struct utmpx
{
   char           ut_user[];
   char           ut_id[];
   char           ut_line[];
   pid_t          ut_pid;
   short          ut_type;
   struct timeval ut_tv;
};

#define EMPTY           0     /* No valid user accounting information */
#define BOOT_TIME       1     /* Identifies time of system boot */
#define OLD_TIME        2     /* Identifies time when system clock change */
#define NEW_TIME        3     /* Identifies time after system clock change */
#define USER_PROCESS    4     /* Identifies a process */
#define INIT_PROCESS    5     /* Identifies a process spawned by an init process */
#define LOGIN_PROCESS   6     /* Identifies a session leader of a logged-in user */
#define DEAD_PROCESS    7     /* Identifies a session leader who has exited */

void           endutxent (void);
struct utmpx  *getutxent (void);
struct utmpx  *getutxid (const struct utmpx *);
struct utmpx  *getutxline (const struct utmpx *);
struct utmpx  *pututxline (const struct utmpx *);
void           setutxent (void);

#endif /* __UTMPX_H__ */
