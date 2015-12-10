
/*
 *  signal.h -- signals
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
 * $Id: signal.h,v 1.6 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

#define SIG_DFL
#define SIG_ERR
#define SIG_HOLD
#define SIG_IGN

typedef int sig_atomic_t;

#ifndef __SIGSETT
#define __SIGSETT
typedef int sigset_t;
#endif

#ifndef __PIDT
#define __PIDT
typedef unsigned int pid_t;
#endif

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

#ifndef __UIDT
#define __UIDT
typedef unsigned int uid_t;
#endif

union sigval
{
   int sival_int;
   void *sival_ptr;
};

struct sigevent
{
   int sigev_notify;
   int sigev_signo;
   union sigval sigev_value;
   void (*sigev_notify_function)(union sigval);
/*   pthread_attr_t *sigev_notify_attributes; */
};

struct sigstack
{
   int   ss_onstack;          /* Non-zero when signal stack is in use */
   void *ss_sp;               /* Signal stack pointer */
};

#ifndef __STACKT
#define __STACKT
typedef struct
{
   void  *ss_sp;              /* Stack base or pointer */
   size_t ss_size;            /* Stack size */
   int    ss_flags;           /* Flags */
} stack_t;
#endif

typedef struct
{
   int          si_signo;     /* Signal number */
   int          si_errno;     /* If non-zero, an 'errno' value associated
                                 with this signal */
   int          si_code;      /* Signal code */
   pid_t        si_pid;       /* Sending process ID */
   uid_t        si_uid;       /* Real user ID of sending process */
   void        *si_addr;      /* Address of faulting instruction */
   int          si_status;    /* Exit value of signal */
   long         si_band;      /* Band event for SIGPOLL */
   union sigval si_value;     /* Signal value */
} siginfo_t;

#define SIGEV_NONE
#define SIGEV_SIGNAL
#define SIGEV_THREAD

#define SIGRTMIN
#define SIGRTMAX

#define SIGABRT      1
#define SIGALRM      2
#define SIGFPE       3
#define SIGHUP       4
#define SIGILL       5
#define SIGINT       6
#define SIGKILL      7
#define SIGPIPE      8
#define SIGQUIT      9
#define SIGSEGV      10
#define SIGTERM      11
#define SIGUSR1      12
#define SIGUSR2      13
#define SIGCHLD      14
#define SIGCONT      15
#define SIGSTOP      16
#define SIGTSTP      17
#define SIGTTIN      18
#define SIGTTOU      19
#define SIGBUS       20
#define SIGPOLL      21
#define SIGPROF      22
#define SIGSYS       23
#define SIGTRAP      24
#define SIGURG       25
#define SIGVTALRM    26
#define SIGXCPU      27
#define SIGXFSZ      28

void (*bsd_signal(int, void (*)(int)))(int);
int kill (pid_t, int);
int killpg (pid_t, int);
int pthread_kill (pthread_t, int);
int pthread_sigmask (int, const sigset_t *, sigset_t *);
int raise (int);
int sigaction (int, const struct sigaction *,  struct sigaction *);

#endif /* __SIGNAL_H__ */
