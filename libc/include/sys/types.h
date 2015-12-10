
/*
 *  types.h -- data types
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
 * $Id: types.h,v 1.5 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __SYS_TYPES_H__
#define __SYS_TYPES_H__

#ifndef __BLKCNTT
#define __BLKCNTT
typedef int          blkcnt_t;
#endif

#ifndef __BLKSIZET
#define __BLKSIZET
typedef int          blksize_t;
#endif

#ifndef __CLOCKT
#define __CLOCKT
typedef unsigned int clock_t;
#endif

#ifndef __CLOCKIDT
#define __CLOCKIDT
typedef unsigned int clockid_t;
#endif

#ifndef __DEVT
#define __DEVT
typedef unsigned int dev_t;
#endif

#ifndef __FSBLKCNTT
#define __FSBLKCNTT
typedef unsigned int fsblkcnt_t;
#endif

#ifndef __FSFILCNTT
#define __FSFILCNTT
typedef unsigned int fsfilcnt_t;
#endif

#ifndef __GIDT
#define __GIDT
typedef unsigned int gid_t;
#endif

#ifndef __IDT
#define __IDT
typedef unsigned int id_t;
#endif

#ifndef __INOT
#define __INOT
typedef unsigned int ino_t;
#endif

#ifndef __KEYT
#define __KEYT
typedef unsigned int key_t;
#endif

#ifndef __MODET
#define __MODET
typedef unsigned int mode_t;
#endif

#ifndef __NLINKT
#define __NLINKT
typedef unsigned int nlink_t;
#endif

#ifndef __OFFT
#define __OFFT
typedef int          off_t;
#endif

#ifndef __PIDT
#define __PIDT
typedef int          pid_t;
#endif

typedef unsigned int pthread_attr_t;
typedef unsigned int pthread_barrier_t;
typedef unsigned int pthread_barrierattr_t;
typedef unsigned int pthread_cond_t;
typedef unsigned int pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef unsigned int pthread_mutex_t;
typedef unsigned int pthread_mutexattr_t;
typedef unsigned int pthread_once_t;
typedef unsigned int pthread_rwlock_t;
typedef unsigned int pthread_rwlockattr_t;
typedef unsigned int pthread_spinlock_t;

#ifndef __PTHREADT
#define __PTHREADT
typedef unsigned int pthread_t;
#endif

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

#ifndef __SSIZET
#define __SSIZET
typedef int          ssize_t;
#endif

#ifndef __SUSECONDST
#define __SUSECONDST
typedef unsigned int suseconds_t;
#endif

#ifndef __TIMET
#define __TIMET
typedef unsigned int time_t;
#endif

#ifndef __TIMERT
#define __TIMERT
typedef unsigned int timer_t;
#endif

#ifndef __TRACEATTRT
#define __TRACEATTRT
typedef unsigned int trace_attr_t;
#endif

#ifndef __TRACEEVENTIDT
#define __TRACEEVENTIDT
typedef unsigned int trace_event_id_t;
#endif

#ifndef __TRACEEVENTSETT
#define __TRACEEVENTSETT
typedef unsigned int trace_event_set_t;
#endif

#ifndef __TRACEIDT
#define __TRACEIDT
typedef unsigned int trace_id_t;
#endif

#ifndef __UIDT
#define __UIDT
typedef unsigned int uid_t;
#endif

#ifndef __USECONDST
#define __USECONDST
typedef unsigned int useconds_t;
#endif

#endif /* __SYS_TYPES_H__ */
