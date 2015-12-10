
/*
 *  unistd.h -- standard symbolic constants and types
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
 * $Id: unistd.h,v 1.5 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __UNISTD_H__
#define __UNISTD_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

#define _POSIX_VERSION        200112L
#define _POSIX2_VERSION
#define _POSIX_C_VERSION
#define _XOPEN_VERSION        500
#define _XOPEN_XCU_VERSION    4

#define _POSIX2_C_BIND
#define _POSIX2_C_VERSION
#define _POSIX2_CHAR_TERM
#define _POSIX2_LOCALEDEF
#define _POSIX2_UPE

#define _XOPEN_XPG2
#define _XOPEN_XPG3
#define _XOPEN_XPG4
#define _XOPEN_UNIX

#define _POSIX_CHOWN_RESTRICTED
#define _POSIX_NO_TRUNC
#define _POSIX_VDISABLE
#define _POSIX_SAVED_IDS
#define _POSIX_JOB_CONTROL

#define _POSIX_THREADS
#define _POSIX_THREAD_ATTR_STACKADDR
#define _POSIX_THREAD_ATTR_STACKSIZE
#define _POSIX_THREAD_PROCESS_SHARED
#define _POSIX_THREAD_SAFE_FUNCTION

#define _POSIX2_C_BIND
#define _POSIX2_C_DEV
#define _POSIX2_CHAR_TERM
#define _POSIX2_FORT_DEV
#define _POSIX2_FORT_RUN
#define _POSIX2_LOCALEDEF
#define _POSIX2_SW_DEV
#define _POSIX2_UPE
#define _XOPEN_CRYPT
#define _XOPEN_ENH_I18N
#define _XOPEN_LEGACY                     1
#define _XOPEN_REALTIME
#define _XOPEN_REALTIME_THREADS
#define _XOPEN_SHM
#define _XBS5_ILP32_OFF32                 1
#define _XBS5_ILP32_OFFBIG                (-1)
#define _XBS5_LP64_OFF64                  (-1)
#define _XBS5_LPIG_OFFBIG                 (-1)

#define _POSIX_ASYCHRONOUS_IO
#define _POSIX_MEMLOCK
#define _POSIX_MEMLOCK_RANGE
#define _POSIX_MESSAGE_PASSING
#define _POSIX_PRIORITY_SCHEDULING
#define _POSIX_REALTIME_SIGNALS
#define _POSIX_SEMAPHORES
#define _POSIX_SHARED_MEMORY_OBJECTS
#define _POSIX_SYCHRONIZED_IO
#define _POSIX_TIMERS

#define _POSIX_FSYNC
#define _POSIX_MAPPED_FILES
#define _POSIX_MEMORY_PROTECTION
#define _POSIX_PRIORITIZED_IO

#ifdef _XOPEN_REALTIME_THREADS
#define _POSIX_THREAD_PRIORITY_SCHEDULING
#define _POSIX_THREAD_PRIO_INHERIT
#define _POSIX_THREAD_PRIO_PROTECT
#endif

#define _POSIX_ASYNC_IO
#define _POSIX_PRIO_IO
#define _POSIX_SYNC_IO

#ifndef NULL
#define NULL      ((void *)0)
#endif

#define R_OK      0x0001
#define W_OK      0x0002
#define X_OK      0x0004
#define F_OK      0x0008

#define _CS_PATH
#define _CS_XBS5_ILP32_OFF32_CFLAGS
#define _CS_XBS5_ILP32_OFF32_LDFLAGS
#define _CS_XBS5_ILP32_OFF32_LIBS
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS
#define _CS_XBS5_ILP32_OFFBIG_LIBS
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS
#define _CS_XBS5_LP64_OFF64_CFLAGS
#define _CS_XBS5_LP64_OFF64_LDFLAGS
#define _CS_XBS5_LP64_OFF64_LIBS
#define _CS_XBS5_LP64_OFF64_LINTFLAGS
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS
#define _CS_XBS5_LPBIG_OFFBIG_LIBS
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS

#ifndef __STDIO_H__
#define SEEK_SET     0
#define SEEK_CUR     1
#define SEEK_END     2
#endif

#define _SC_2_C_BIND                      1
#define _SC_2_C_DEV                       2
#define _SC_2_C_VERSION                   3
#define _SC_2_FORT_DEV                    4
#define _SC_2_FORT_RUN                    5
#define _SC_2_LOCALEDEF                   6
#define _SC_2_SW_DEV                      7
#define _SC_2_UPE                         8
#define _SC_2_VERSION                     9
#define _SC_ARG_MAX                       10
#define _SC_AIO_LISTIO_MAX                11
#define _SC_AIO_MAX                       12
#define _SC_AIO_PRIO_DELTA_MAX            13
#define _SC_ASYNCRONOUS_IO                14
#define _SC_ATEXIT_MAX                    15
#define _SC_BC_BASE_MAX                   16
#define _SC_BC_DIM_MAX                    17
#define _SC_BC_SCALE_MAX                  18
#define _SC_BC_STRING_MAX                 19
#define _SC_CHILD_MAX                     20
#define _SC_CLK_TCK                       21
#define _SC_COLL_WEIGHTS_MAX              22
#define _SC_DELAYTIMER_MAX                23
#define _SC_EXPR_NEST_MAX                 24
#define _SC_FSYNC                         25
#define _SC_GETGR_R_SIZE_MAX              26
#define _SC_GETPW_R_SIZE_MAX              27
#define _SC_IOV_MAX                       28
#define _SC_JOB_CONTROL                   29
#define _SC_LINE_MAX                      30
#define _SC_LOGIN_NAME_MAX                31
#define _SC_MAPPED_FILES                  32
#define _SC_MEMLOCK                       33
#define _SC_MEMLOCK_RANGE                 34
#define _SC_MEMORY_PROTECTION             35
#define _SC_MESSAGE_PASSING               36
#define _SC_MQ_OPEN_MAX                   37
#define _SC_MQ_PRIO_MAX                   38
#define _SC_NGROUPS_MAX                   39
#define _SC_OPEN_MAX                      40
#define _SC_PAGESIZE                      41
#define _SC_PAGE_SIZE                     42
#define _SC_PASS_MAX                      43
#define _SC_PRIORITIZED_IO                44
#define _SC_PRIORITIZED_SCHEDULING        45
#define _SC_RE_DUP_MAX                    46
#define _SC_REALTIME_SIGNALS              47
#define _SC_RTSIG_MAX                     48
#define _SC_SAVED_IDS                     49
#define _SC_SEMAPHORES                    50
#define _SC_SEM_NSEMS_MAX                 51
#define _SC_SEM_VALUE_MAX                 52
#define _SC_SHARED_MEMORY_OBJECTS         53
#define _SC_SIGQUEUE_MAX                  54
#define _SC_STREAM_MAX                    55
#define _SC_SYNCHRONIZED_IO               56
#define _SC_THREADS                       57
#define _SC_THREAD_ATTR_STACKADDR         58
#define _SC_THREAD_ATTR_STACKSIZE         59
#define _SC_THREAD_DESTRUCTOR_ITERATIONS  60
#define _SC_THREAD_KEYS_MAX               61
#define _SC_THREAD_PRIORITY_SCHEDULING    62
#define _SC_THREAD_PRIO_INHERIT           63
#define _SC_THREAD_PRIO_PROTECT           64
#define _SC_THREAD_PROCESS_SHARED         65
#define _SC_THREAD_SAFE_FUNCTIONS         66
#define _SC_THREAD_STACK_MIN              67
#define _SC_THREAD_THREADS_MAX            68
#define _SC_TIMERS                        69
#define _SC_TIMER_MAX                     70
#define _SC_TTY_NAME_MAX                  71
#define _SC_TZNAME_MAX                    72
#define _SC_VERSION                       73
#define _SC_XOPEN_VERSION                 74
#define _SC_XOPEN_CRYPT                   75
#define _SC_XOPEN_ENH_I18N                76
#define _SC_XOPEN_SHM                     77
#define _SC_XOPEN_XCU_VERSION             78
#define _SC_XOPEN_LEGACY                  79
#define _SC_XOPEN_REALTIME                80
#define _SC_XOPEN_REALTIME_THREADS        81
#define _SC_XOPEN_ILP32_OFF32             82
#define _SC_XOPEN_ILP32_OFFBIG            83
#define _SC_XOPEN_LP64_OFF64              84
#define _SC_XOPEN_LPBIG_OFFBIG            85

#define F_LOCK       1
#define F_ULOCK      2
#define F_TEST       3
#define F_TLOCK      4

#define _PC_ASYNC_IO
#define _PC_CHOWN_RESTRICTED
#define _PC_FILESIZEBITS
#define _PC_LINK_MAX
#define _PC_MAX_CANON
#define _PC_MAX_INPUT
#define _PC_NAME_MAX
#define _PC_NO_TRUNC
#define _PC_PATH_MAX
#define _PC_PIPE_BUF
#define _PC_PRIO_IO
#define _PC_SYNC_IO
#define _PC_VDISABLE

#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

#ifndef __SSIZET
#define __SSIZET
typedef unsigned int ssize_t;
#endif

#ifndef __UIDT
#define __UIDT
typedef unsigned int uid_t;
#endif

#ifndef __GIDT
#define __GIDT
typedef unsigned int gid_t;
#endif

#ifndef __OFFT
#define __OFFT
typedef unsigned int off_t;
#endif

#ifndef __PIDT
#define __PIDT
typedef unsigned int pid_t;
#endif

#ifndef __USECONDST
#define __USECONDST
typedef unsigned int useconds_t;
#endif

#ifndef __INTPTRT
#define __INTPTRT
typedef unsigned int intptr_t;
#endif

int          access (const char *, int);
unsigned int alarm (unsigned int);
int          brk (void *);
int          chdir (const char *);
int          chroot (const char *);
int          chown (const char *, uid_t, gid_t);
int          close (int);
size_t       confstr (int, char *, size_t);
char        *crypt (const char *, const char *);
char        *ctermid (char *);
char        *cuserid (char *);




#endif /* __UNISTD_H__ */
