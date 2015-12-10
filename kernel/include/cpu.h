
/*
 *  cpu.h
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
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: cpu.h,v 1.4 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __CPU_H__
#define __CPU_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

#define FEATURE_FPU     0x00000001  /* Builtin FPU */
#define FEATURE_VME     0x00000002  /* Virtual mode extentions */
#define FEATURE_DE      0x00000004  /* Debugging extentions */
#define FEATURE_PSE     0x00000008  /* Pages size extentions */
#define FEATURE_TSC     0x00000010  /* Time stamp counter */
#define FEATURE_MSR     0x00000020  /* Model specific registers */
#define FEATURE_PAE     0x00000040  /* Physical address extentions */
#define FEATURE_MCE     0x00000080  /* Machine check exception */
#define FEATURE_CX8     0x00000100  /* CMPXCHG8B instruction */
#define FEATURE_APIC    0x00000200  /* On-chip APIC */
#define FEATURE_10      0x00000400
#define FEATURE_SEP     0x00000800  /* Supports fast system calls */
#define FEATURE_MTRR    0x00001000  /* Memory type range registers */
#define FEATURE_PGE     0x00002000  /* Page global enable */
#define FEATURE_MCA     0x00004000  /* Machine check architecture */
#define FEATURE_CMOV    0x00008000  /* CMOVcc instructions */
#define FEATURE_PAT     0x00010000  /* Page attribute table */
#define FEATURE_PSE36   0x00020000  /* 36-bit page size extentions */
#define FEATURE_18      0x00040000
#define FEATURE_19      0x00080000
#define FEATURE_20      0x00100000
#define FEATURE_21      0x00200000
#define FEATURE_22      0x00400000
#define FEATURE_MMX     0x00800000  /* Multimedia extentions */
#define FEATURE_FXSR    0x01000000  /* Fast floating point save and restore */
#define FEATURE_SIMD    0x02000000  /* Streaming SIMD extensions */
#define FEATURE_26      0x04000000
#define FEATURE_27      0x08000000
#define FEATURE_28      0x10000000
#define FEATURE_29      0x20000000
#define FEATURE_30      0x40000000
#define FEATURE_AMD3D   0x80000000  /* AMD 3DNow! Instructions */

#define CPU_FEATURE(x)     (cpudata.features_edx & x)

struct CPUInfo
{
   ulong cache_eax;
   ulong cache_ebx;
   ulong cache_ecx;
   ulong cache_edx;
   char vendor_id[16];
   ulong cpuid_flag;
   ulong cpu_type;
   ulong cpu_signature;
   ulong features_ebx;
   ulong features_ecx;
   ulong features_edx;
} __attribute__ ((packed));

extern struct CPUInfo cpudata;

#endif /* __CPU_H__ */
