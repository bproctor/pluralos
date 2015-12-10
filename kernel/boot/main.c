
/*
 *  main.c
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
 * $Id: main.c,v 1.16 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <system.h>
#include <version.h>
#include <cpu.h>
#include <irq.h>
#include <config.h>

void monitor (void);
void delay (uint);
void init_irq (void);
void init_memory (ulong);
void init_dma (void);
void init_pit (ulong, uchar);
void init_timer (void);
void init_pci (void);
ulong init_delay (void);
void init_keyboard (void);
void init_floppy (void);
void init_ide (void);
void init_serial (void);
void init_sched (void);
void free_init_memory (void);

#if CPU >= 5
static void __init__ decode_tlb (int x)
{
   switch (x & 0xFF)
   {
      case 0x00: break;
      case 0x01: puts ("Instruction TLB: 4Kb pages, 4-way set assoc, 32 entries\n"); break;
      case 0x02: puts ("Instruction TLB: 4Mb pages, fully assoc, 2 entries\n"); break;
      case 0x03: puts ("Data TLB: 4Kb pages, 4-way set assoc, 64 entries\n"); break;
      case 0x04: puts ("Data TLB: 4Mb pages, 4-wat set assoc, 8 entries\n"); break;
      case 0x06: puts ("Instruction cache: 8KB, 4-way set assoc, 32 byte line size\n"); break;
      case 0x08: puts ("Instruction cache: 16KB, 4-way set assoc, 32 byte line size\n"); break;
      case 0x0A: puts ("Data cache: 8KB, 2-way set assoc, 32 byte line size\n"); break;
      case 0x0C: puts ("Data cache: 16KB, 2-way or 4-way set assoc, 32 byte line size\n"); break;
      case 0x40: puts ("No L2 cache\n"); break;
      case 0x41: puts ("L2 unified cache: 128KB, 4-way set assoc, 32 byte line size\n"); break;
      case 0x42: puts ("L2 unified cache: 256KB, 4-way set assoc, 32 byte line size\n"); break;
      case 0x43: puts ("L2 unified cache: 512KB, 4-way set assoc, 32 byte line size\n"); break;
      case 0x44: puts ("L2 unified cache: 1MB, 4-way set assoc, 32 byte line size\n"); break;
      case 0x45: puts ("L2 unified cache: 2MB, 4-way set assoc, 32 byte line size\n"); break;
      case 0x50: puts ("Instruction TLB: 4KB and 2MB or 4MB pages, 64 entries\n"); break;
      case 0x51: puts ("Instruction TLB: 4KB and 2MB or 4MB pages, 128 entries\n"); break;
      case 0x52: puts ("Instruction TLB: 4KB and 2MB or 4MB pages, 256 entries\n"); break;
      case 0x5b: puts ("Data TLB: 4KB and 4MB pages, 64 entries\n"); break;
      case 0x5c: puts ("Data TLB: 4KB and 4MB pages, 128 entries\n"); break;
      case 0x5d: puts ("Data TLB: 4KB and 4MB pages, 256 entries\n"); break;
      case 0x66: puts ("1st-level data cache: 8KB, 4-way set assoc, 64 byte line size\n"); break;
      case 0x67: puts ("1st-level data cache: 16KB, 4-way set assoc, 64 byte line size\n"); break;
      case 0x68: puts ("1st-level data cache: 32KB, 4-way set assoc, 64 byte line size\n"); break;
      case 0x70: puts ("Trace cache: 12K-micro-op, 8-way set assoc\n"); break;
      case 0x71: puts ("Trace cache: 16K-micro-op, 8-way set assoc\n"); break;
      case 0x72: puts ("Trace cache: 32K-micro-op, 8-way set assoc\n"); break;
      case 0x79: puts ("2nd-level cache: 128KB, 8-way set assoc, sectored, 64 byte line size\n"); break;
      case 0x7a: puts ("2nd-level cache: 256KB, 8-way set assoc, sectored, 64 byte line size\n"); break;
      case 0x7b: puts ("2nd-level cache: 512KB, 8-way set assoc, sectored, 64 byte line size\n"); break;
      case 0x7c: puts ("2nd-level cache: 1MB, 8-way set assoc, sectored, 64 byte line size\n"); break;
      case 0x82: puts ("2nd-level cache: 256KB, 8-way set assoc, 32 byte line size\n"); break;
      case 0x84: puts ("2nd-level cache: 1MB, 8-way set assoc, 32 byte line size\n"); break;
      case 0x85: puts ("2nd-level cache: 2MB, 8-way set assoc, 32 byte line size\n"); break;
      default:   printf ("unknown TLB/cache descriptor: 0x%02X\n", x); break;
   }
}
#endif

static void __init__ show_cpu_info (void)
{
   if (cpudata.cpuid_flag == 0)
   {
      if (cpudata.cpu_type == 3)
         puts ("CPU: 386\n");
      else if (cpudata.cpu_type == 4)
         puts ("CPU: 486\n");
      return;
   }
   puts ("CPUID: ");
   puts (cpudata.vendor_id);
   puts ("\nCPU: ");
   if (!strcmp ("GenuineIntel", cpudata.vendor_id))
   {
      if (cpudata.cpu_type == 4)
      {
         puts ("Genuine ");
         switch ((cpudata.cpu_signature >> 4) & 0x0F)
         {
            case 0:
            case 1: puts ("Intel486(tm)DX"); break;
            case 2: puts ("Intel486(tm)SX"); break;
            case 3: puts ("IntelDX2(tm)"); break;
            case 4: puts ("Intel486(tm)"); break;
            case 5: puts ("IntelSX2(tm)"); break;
            case 7: puts ("Write-back enhanced IntelDX2(tm)"); break;
            case 8: puts ("IntelDX4(tm)"); break;
            default: puts ("Intel486(tm)"); break;
         }
         puts ("Processor\n");
      }
      else if (cpudata.cpu_type == 5)
         puts ("Genuine Intel Pentium(R) Processor\n");
      else if (cpudata.cpu_type == 6 && ((cpudata.cpu_signature >> 4) & 0x0F) == 1)
         puts ("Genuine Intel Pentium Pro(R) Processor\n");
      else if (cpudata.cpu_type == 6 && ((cpudata.cpu_signature >> 4) & 0x0F) == 3)
         puts ("Genuine Intel Pentium II(R) Processor\n");
      else if ((cpudata.cpu_type == 6 && ((cpudata.cpu_signature >> 4) & 0x0F) == 5)
         || (cpudata.cpu_type == 6 && ((cpudata.cpu_signature >> 4) & 0x0F) == 7))
      {
         ulong celeron_flag = 0;
         ulong pentium_xeon_flag = 0;
         ulong cache_temp = cpudata.cache_eax & 0xFF000000;

         if (cache_temp == 0x40000000)
            celeron_flag = 1;
         else if (cache_temp >= 0x40000000 && cache_temp <= 0x45000000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_eax & 0xFF0000;
         if (cache_temp == 0x400000)
            celeron_flag = 1;
         else if (cache_temp >= 0x440000 && cache_temp <= 0x450000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_eax & 0xFF00;
         if (cache_temp == 0x4000)
            celeron_flag = 1;
         else if (cache_temp >= 0x4400 && cache_temp <= 0x4500)
            pentium_xeon_flag = 1;

         cache_temp = cpudata.cache_ebx & 0xFF000000;
         if (cache_temp == 0x40000000)
            celeron_flag = 1;
         else if (cache_temp >= 0x40000000 && cache_temp <= 0x45000000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_ebx & 0xFF00000;
         if (cache_temp == 0x400000)
            celeron_flag = 1;
         else if (cache_temp >= 0x400000 && cache_temp <= 0x450000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_ebx & 0xFF00;
         if (cache_temp == 0x400000)
            celeron_flag = 1;
         else if (cache_temp >= 0x4400 && cache_temp <= 0x4500)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_ebx & 0xFF;
         if (cache_temp == 0x40)
            celeron_flag = 1;
         else if (cache_temp >= 0x44 && cache_temp <= 0x45)
            pentium_xeon_flag = 1;

         cache_temp = cpudata.cache_ecx & 0xFF000000;
         if (cache_temp == 0x40000000)
            celeron_flag = 1;
         else if (cache_temp >= 0x40000000 && cache_temp <= 0x45000000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_ecx & 0xFF0000;
         if (cache_temp == 0x400000)
            celeron_flag = 1;
         else if (cache_temp >= 0x400000 && cache_temp <= 0x450000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_ecx & 0xFF00;
         if (cache_temp == 0x400000)
            celeron_flag = 1;
         else if (cache_temp >= 0x4400 && cache_temp <= 0x4500)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_ecx & 0xFF;
         if (cache_temp == 0x40)
            celeron_flag = 1;
         else if (cache_temp >= 0x44 && cache_temp <= 0x45)
            pentium_xeon_flag = 1;

         cache_temp = cpudata.cache_edx & 0xFF000000;
         if (cache_temp == 0x40000000)
            celeron_flag = 1;
         else if (cache_temp >= 0x40000000 && cache_temp <= 0x45000000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_edx & 0xFF0000;
         if (cache_temp == 0x400000)
            celeron_flag = 1;
         else if (cache_temp >= 0x400000 && cache_temp <= 0x450000)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_edx & 0xFF00;
         if (cache_temp == 0x400000)
            celeron_flag = 1;
         else if (cache_temp >= 0x4400 && cache_temp <= 0x4500)
            pentium_xeon_flag = 1;
         cache_temp = cpudata.cache_edx & 0xFF;
         if (cache_temp == 0x40)
            celeron_flag = 1;
         else if (cache_temp >= 0x44 && cache_temp <= 0x45)
            pentium_xeon_flag = 1;

         if (celeron_flag)
            puts ("Intel Celeron(tm) Processor, Model 5");
         else
         {
            if (pentium_xeon_flag)
            {
               puts ("Intel Pentium(R) ");
               if (((cpudata.cpu_signature >> 4) & 0x0F) == 5)
                  puts ("II");
               else
                  puts ("III");
               puts (" Xeon(tm) Processor");
            }
            else
            {
               puts ("Intel Pentium(R) ");
               if (((cpudata.cpu_signature >> 4) & 0x0F) == 5)
                  puts ("II, Model 5 or Pentium II");
               else
                  puts ("III, Pentium III");
               puts (" Xeon");
            }
         }
      }
      else if (cpudata.cpu_type == 6 && ((cpudata.cpu_signature >> 4) & 0x0F) == 6)
         puts ("Intel Celeron Processor, Model 6\n");
      else
         puts ("Unknown Genuine Intel Processor\n");
   }
   else if (!strcmp ("CyrixInstead", cpudata.vendor_id))
   {
      puts ("Cyrix ");
   }
   else if (!strcmp ("AuthenticAMD", cpudata.vendor_id))
   {
   }
   else
      puts ("I don't know\n");
   printf ("Family: %ld ", cpudata.cpu_type);
   printf ("Model: %ld ", (cpudata.cpu_signature >> 4) & 0x0F);
   printf ("Stepping: %ld\n", cpudata.cpu_signature & 0x0F);

   puts ("Features: ");
   if (CPU_FEATURE (FEATURE_FPU))   puts ("fpu ");
   if (CPU_FEATURE (FEATURE_VME))   puts ("vme ");
   if (CPU_FEATURE (FEATURE_DE))    puts ("de ");
   if (CPU_FEATURE (FEATURE_PSE))   puts ("pse ");
   if (CPU_FEATURE (FEATURE_TSC))   puts ("tsc ");
   if (CPU_FEATURE (FEATURE_MSR))   puts ("msr ");
   if (CPU_FEATURE (FEATURE_PAE))   puts ("pae ");
   if (CPU_FEATURE (FEATURE_MCE))   puts ("mce ");
   if (CPU_FEATURE (FEATURE_CX8))   puts ("cx8 ");
   if (CPU_FEATURE (FEATURE_APIC))  puts ("apic ");
   if (CPU_FEATURE (FEATURE_SEP))   puts ("sep ");
   if (CPU_FEATURE (FEATURE_MTRR))  puts ("mtrr ");
   if (CPU_FEATURE (FEATURE_PGE))   puts ("pge ");
   if (CPU_FEATURE (FEATURE_MCA))   puts ("mca ");
   if (CPU_FEATURE (FEATURE_CMOV))  puts ("cmov ");
   if (CPU_FEATURE (FEATURE_PAT))   puts ("pat ");
   if (CPU_FEATURE (FEATURE_PSE36)) puts ("pse36 ");
   if (CPU_FEATURE (FEATURE_MMX))   puts ("mmx ");
   if (CPU_FEATURE (FEATURE_FXSR))  puts ("fxsr ");
   if (CPU_FEATURE (FEATURE_AMD3D)) puts ("amd3d ");
   puts ("\n");

#if CPU >= 5
   {
      ulong i, sig, eax, ebx, ecx, edx, ntlb;
      ntlb = 255;
      for (i = 0; i < ntlb; ++i)
      {
         cpuid (2, &eax, &ebx, &ecx, &edx);
         ntlb = eax & 0xFF;
         decode_tlb (eax >> 8);
         decode_tlb (eax >> 16);
         decode_tlb (eax >> 24);
         if ((ebx & 0x80000000) == 0)
         {
            decode_tlb (ebx);
            decode_tlb (ebx >> 8);
            decode_tlb (ebx >> 16);
            decode_tlb (ebx >> 24);
         }
         if ((ecx & 0x80000000) == 0)
         {
            decode_tlb (ecx);
            decode_tlb (ecx >> 8);
            decode_tlb (ecx >> 16);
            decode_tlb (ecx >> 24);
         }
         if ((edx & 0x80000000) == 0)
         {
            decode_tlb (edx);
            decode_tlb (edx >> 8);
            decode_tlb (edx >> 16);
            decode_tlb (edx >> 24);
         }
      }
      cpuid (1, &eax, &ebx, &ecx, &edx);
      sig = eax;
      cpuid (3, &eax, &ebx, &ecx, &edx);
      puts ("Serial Number: ");
      printf ("%04lX-%04lX-%04lX-%04lX", sig >> 16, sig & 0xFFFF, edx >> 16, edx & 0xFFFF);
      printf ("-%04lX-%04lX\n", ecx >> 16, ecx & 0xFFFF);
   }
#endif
}

void __init__ start_kernel (ulong memsize)
{
   uint cpu_speed;
   puts ("Plural, Version "VERSION_STRING" (Build: "BUILD_NUM") "
      BUILD_BY"@"BUILD_HOST" "BUILD_DATE" "BUILD_TIME"\n");
   cpu_speed = init_delay () / 500;
   init_memory (memsize);
   init_timer ();
   init_sched ();
   show_cpu_info ();
   printf ("CPU Speed: %uMhz\n", (cpu_speed));

   /*
    * Driver init
    */

#ifdef CONFIG_PCI
   init_pci ();
#endif
#ifdef CONFIG_KEYBOARD
   init_keyboard ();
#endif
#ifdef CONFIG_SERIAL
   init_serial ();
#endif
#ifdef CONFIG_FLOPPY
   init_floppy ();
#endif
#ifdef CONFIG_IDE
   init_ide ();
#endif

   free_init_memory ();
#if 0
   monitor ();
#endif
   while (1);     /* Just in case */
}
