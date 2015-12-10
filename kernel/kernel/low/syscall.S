
/*
 *  syscall.S
 *  Copyright (c) 2001-2002 Brad Proctor
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
 * $Id: syscall.S,v 1.10 2002/12/02 09:06:24 fredlie Exp $
 */

#include <asm.h>

#define NUM_SYSCALLS            (end_syscall_table - syscall_table)/4

ENTRY (int_syscall):
        pushal
        cmpl    $NUM_SYSCALLS,%eax
        jl      1f
        xorl    %eax,%eax
1:      call    *syscall_table(,%eax,4)
        movb    $0x20,%al
        outb    %al,$0x20
        popal
        iret

LOCAL (syscall_null):
        movl    $53,%eax                /* ENOSYS */
        ret

/*
 * This system call list is subject to change until the kernel is actually up 
 * and running.  Don't rely on the numbers in this table to be the same from 
 * kernel version to kernel version.  Until at least kernel version 0.2 when
 * the system starts to stablize.
 */

LOCAL (syscall_table):
        .long   syscall_null                    /* 0 */
        .long   AlarmCreate
        .long   AlarmDestroy
        .long   AlarmResume
        .long   AlarmSuspend
	.long	ChannelCreate                   /* 5 */
	.long	ChannelDestroy
	.long	ChannelGetLimit
	.long   ChannelGetOwner
	.long	ChannelPurge
	.long	ChannelSetLimit                 /* 10 */
	.long   ChannelSetOwner
        .long   ClockGetDate
        .long   ClockGetTime
        .long   ClockSetDate
        .long   ClockSetTime                    /* 15 */
	.long   CondvarBroadcast
	.long   CondvarCreate
	.long   CondvarDestroy
	.long   CondvarSignal
	.long   CondvarWait                     /* 20 */
	.long   DeviceCreate
	.long   DeviceDestroy
	.long   DeviceInit
	.long   DeviceOp
	.long   DeviceStat                      /* 25 */
	.long   InterruptAttach
	.long   InterruptDetach
	.long   InterruptDisable
	.long   InterruptEnable
	.long   InterruptLock                   /* 30 */
	.long   InterruptMask
	.long   InterruptUnlock
	.long   InterruptUnmask
	.long   InterruptWait
	.long   MemoryAlloc                     /* 35 */
	.long   MemoryFree
	.long   MemoryMap
        .long   MemoryProtect
	.long   MemoryUnmap
        .long   MessageBroadcast                /* 40 */
	.long   MessageCheck
	.long   MessageCreate
	.long   MessageDestroy
	.long   MessagePost
	.long   MessageRecieve                  /* 45 */
	.long   MessageSend
	.long	MutexCreate
	.long	MutexDestroy
	.long	MutexLock
	.long	MutexTryLock                    /* 50 */
	.long	MutexUnlock
        .long   ProcessCreate
        .long   ProcessDestroy
        .long   ProcessGetPolicy
        .long   ProcessGetPriority              /* 55 */
        .long   ProcessSetPolicy
        .long   ProcessSetPriority
        .long   ProcessThreads
        .long   SemCreate
        .long   SemDestroy                      /* 60 */
        .long   ServiceCreate
        .long   ServiceDestroy
        .long   ServiceResume
        .long   ServiceSuspend
        .long   SignalAction                    /* 65 */
        .long   SignalKill
        .long   SignalProcMask
        .long   SignalReturn
        .long   SignalSuspend
        .long   SignalWaitInfo                  /* 70 */
	.long   ThreadCancel
	.long   ThreadContext
	.long   ThreadCreate
	.long   ThreadDestroy
	.long   ThreadDetach                    /* 75 */
	.long   ThreadGetChannel
	.long   ThreadGetPolicy
	.long   ThreadGetPriority
	.long   ThreadGetStack
	.long   ThreadSelf                      /* 80 */
	.long   ThreadSetChannel
	.long   ThreadSetPolicy
	.long   ThreadSetStack
	.long   ThreadSetPriority
	.long   ThreadYield                     /* 85 */
	.long   TimerCreate
	.long   TimerDestroy
	.long   TimerRead
	.long   TimerReset
	.long   TimerSet                        /* 90 */
	.long   TimerStart
	.long   TimerStop
LOCAL (end_syscall_table):

