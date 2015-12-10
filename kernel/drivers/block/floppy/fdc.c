
/*
 *  fdc.c
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
 * $Id: fdc.c,v 1.6 2002/12/02 04:16:28 fredlie Exp $
 */

#include <sys/types.h>
#include <irq.h>
#include <system.h>
#include <io.h>
#include <stdio.h>
#include <dma.h>

#define FDC_DOR      0x3F2
#define FDC_MSR      0x3F4
#define FDC_DRS      0x3F4
#define FDC_DATA     0x3F5
#define FDC_DIR      0x3F7
#define FDC_CCR      0x3F7

#define CMD_SPECIFY  0x03
#define CMD_WRITE    0xC5
#define CMD_READ     0xE6
#define CMD_RECAL    0x07
#define CMD_SENSEI   0x08
#define CMD_FORMAT   0x4D
#define CMD_SEEK     0x0F
#define CMD_VERSION  0x10

#define D144_HEADS      2
#define D144_TRACKS     80
#define D144_SPT        18
#define D144_GAP3FMT    0x54
#define D144_GAP3RW     0x1B

typedef struct drv_geom
{
   uint size;
   uchar spt;
   uchar heads;
   uchar tracks;
   uchar stretch;
   uchar gap;
   uchar rate;
   uchar spec1;
   uchar gap2;
   char *desc;
} drv_geom;

/*
        Size
        |   Sectors per track
        |   |  Heads
        |   |  |   Tracks
        |   |  |   |  Stretch
        |   |  |   |  |     Gap 1 size
        |   |  |   |  |     |     Data rate, | 0x40 for perp
        |   |  |   |  |     |     |     Spec1 (stepping rate, head unload
        |   |  |   |  |     |     |     |     /fmt gap (gap2) */
static const drv_geom floppy_type[] =
{
   {    0,  0, 0,  0, 0, 0x00, 0x00, 0x00, 0x00, NULL    }, /*  0 no testing    */
   {  720,  9, 2, 40, 0, 0x2A, 0x02, 0xDF, 0x50, "d360"  }, /*  1 360KB PC      */
   { 2400, 15, 2, 80, 0, 0x1B, 0x00, 0xDF, 0x54, "h1200" }, /*  2 1.2MB AT      */
   {  720,  9, 1, 80, 0, 0x2A, 0x02, 0xDF, 0x50, "D360"  }, /*  3 360KB SS 3.5" */
   { 1440,  9, 2, 80, 0, 0x2A, 0x02, 0xDF, 0x50, "D720"  }, /*  4 720KB 3.5"    */
   {  720,  9, 2, 40, 1, 0x23, 0x01, 0xDF, 0x50, "h360"  }, /*  5 360KB AT      */
   { 1440,  9, 2, 80, 0, 0x23, 0x01, 0xDF, 0x50, "h720"  }, /*  6 720KB AT      */
   { 2880, 18, 2, 80, 0, 0x1B, 0x00, 0xCF, 0x6C, "H1440" }, /*  7 1.44MB 3.5"   */
   { 5760, 36, 2, 80, 0, 0x1B, 0x43, 0xAF, 0x54, "E2880" }, /*  8 2.88MB 3.5"   */
   { 6240, 39, 2, 80, 0, 0x1B, 0x43, 0xAF, 0x28, "E3120" }, /*  9 3.12MB 3.5"   */
   { 2880, 18, 2, 80, 0, 0x25, 0x00, 0xDF, 0x02, "h1440" }, /* 10 1.44MB 5.25"  */
   { 3360, 21, 2, 80, 0, 0x1C, 0x00, 0xCF, 0x0C, "H1680" }, /* 11 1.68MB 3.5"   */
   {  820, 10, 2, 41, 1, 0x25, 0x01, 0xDF, 0x2E, "h410"  }, /* 12 410KB 5.25"   */
   { 1640, 10, 2, 82, 0, 0x25, 0x02, 0xDF, 0x2E, "H820"  }, /* 13 820KB 3.5"    */
   { 2952, 18, 2, 82, 0, 0x25, 0x00, 0xDF, 0x02, "h1476" }, /* 14 1.48MB 5.25"  */
   { 3444, 21, 2, 82, 0, 0x25, 0x00, 0xDF, 0x0C, "H1722" }, /* 15 1.72MB 3.5"   */
   {  840, 10, 2, 42, 1, 0x25, 0x01, 0xDF, 0x2E, "h420"  }, /* 16 420KB 5.25"   */
   { 1660, 10, 2, 83, 0, 0x25, 0x02, 0xDF, 0x2E, "H830"  }, /* 17 830KB 3.5"    */
   { 2988, 18, 2, 83, 0, 0x25, 0x00, 0xDF, 0x02, "h1494" }, /* 18 1.49MB 5.25"  */
   { 3486, 21, 2, 83, 0, 0x25, 0x00, 0xDF, 0x0C, "H1743" }, /* 19 1.74 MB 3.5"  */
   { 1760, 11, 2, 80, 0, 0x1C, 0x09, 0xCF, 0x00, "h880"  }, /* 20 880KB 5.25"   */
   { 2080, 13, 2, 80, 0, 0x1C, 0x01, 0xCF, 0x00, "D1040" }, /* 21 1.04MB 3.5"   */
   { 2240, 14, 2, 80, 0, 0x1C, 0x19, 0xCF, 0x00, "D1120" }, /* 22 1.12MB 3.5"   */
   { 3200, 20, 2, 80, 0, 0x1C, 0x20, 0xCF, 0x2C, "h1600" }, /* 23 1.6MB 5.25"   */
   { 3520, 22, 2, 80, 0, 0x1C, 0x08, 0xCF, 0x2e, "H1760" }, /* 24 1.76MB 3.5"   */
   { 3840, 24, 2, 80, 0, 0x1C, 0x20, 0xCF, 0x00, "H1920" }, /* 25 1.92MB 3.5"   */
   { 6400, 40, 2, 80, 0, 0x25, 0x5B, 0xCF, 0x00, "E3200" }, /* 26 3.20MB 3.5"   */
   { 7040, 44, 2, 80, 0, 0x25, 0x5B, 0xCF, 0x00, "E3520" }, /* 27 3.52MB 3.5"   */
   { 7680, 48, 2, 80, 0, 0x25, 0x63, 0xCF, 0x00, "E3840" }, /* 28 3.84MB 3.5"   */
   { 3680, 23, 2, 80, 0, 0x1C, 0x10, 0xCF, 0x00, "H1840" }, /* 29 1.84MB 3.5"   */
   { 1600, 10, 2, 80, 0, 0x25, 0x02, 0xDF, 0x2E, "D800"  }, /* 30 800KB 3.5"    */
   { 3200, 20, 2, 80, 0, 0x1C, 0x00, 0xCF, 0x2C, "H1600" }, /* 31 1.6MB 3.5"    */
};

static int type = 6;
static uchar fdc_track = 0xFF;
static uchar status[7] = {0};
static int mtick = 0;
static char motor = 0;
static char dchange = 0;
static uchar statsz = 0;
static uchar sr0 = 0;
static volatile char done = 0;
static volatile int tmout = 0;

ulong tbaddr = 0x80000L;

void delay (ulong);
void int_floppy (void);
void int_floppy1 (void);

static void sendbyte (int byte)
{
   volatile int msr;
   int tmo;
   
   for (tmo = 0; tmo < 128; ++tmo)
   {
      msr = inb (FDC_MSR);
      if ((msr & 0xC0) == 0x80)
      {
         outb (FDC_DATA, byte);
         return;
      }
      inb (0x80);
   }
}

static int getbyte (void)
{
   volatile int msr;
   int tmo;
   
   for (tmo = 0; tmo < 128; ++tmo)
   {
      msr = inb (FDC_MSR);
      if ((msr & 0xD0) == 0xD0)
         return (inb (FDC_DATA));
      inb (0x80);
   }
   return (-1);
}

static int wait_fdc (int sensei)
{
   tmout = 5;     /* Hacked! for broken floppy code */
   
   while (!done && tmout)
      ;

   statsz = 0;
   while ((statsz < 7) && (inb (FDC_MSR) & (1 << 4)))
      status[(uint)statsz++] = getbyte ();
   
   if (sensei)
   {
      sendbyte (CMD_SENSEI);
      sr0 = getbyte ();
      fdc_track = getbyte ();
   }
   done = 0;

   if (!tmout)
   {
      if (inb (FDC_DIR) & 0x80)
         dchange = 1;
      return (0);
   }
   else
      return (1);
}

static void motoron (void)
{
   if (!motor)
   {
      mtick = -1;
      outb (FDC_DOR, 0x1C);
      delay (500);
      motor = 1;
   }
}

static void motoroff (void)
{
   if (motor)
      mtick = 13500;
}

static void recalibrate (void)
{
   motoron ();
   sendbyte (CMD_RECAL);
   sendbyte (0);
   wait_fdc (1);
   motoroff ();
}

static int seek (int track)
{
   if (fdc_track == track)
      return (1);
   sendbyte (CMD_SEEK);
   sendbyte (0);
   sendbyte (track);
   
   if (!wait_fdc (1))
      return (0);
   
   delay (15);

   if ((sr0 != 0x20) || (fdc_track != track))
      return (0);
   else
      return (1);
}

static void reset (void)
{
   outb (FDC_DOR, 0);
   mtick = 0;
   motor = 0;

#if 0
   outb (FDC_DRS, 0);
#endif
   outb (FDC_DOR, 0x0C);
   done = 1;
   wait_fdc (1);
   
   sendbyte (CMD_SPECIFY);
   sendbyte (0xDF);
   sendbyte (0x02);
   seek (1);
   recalibrate ();
   dchange = 0;
}

static void block2hts (int block, int *head, int *track, int *sector)
{
   *head = (block % (floppy_type[type].spt * floppy_type[type].heads)) / floppy_type[type].spt;
   *track = block / (floppy_type[type].spt * floppy_type[type].heads);
   *sector = block % floppy_type[type].spt + 1;
}

static int fdc_rw (int block, uchar *blockbuff, uchar read, ulong nosectors)
{
   int head, track, sector, tries, copycount = 0;
   uchar *p_tbaddr = (uchar *)0xE0080000;
   uchar *p_blockbuff = blockbuff;
   
   block2hts (block, &head, &track, &sector);
   motoron ();
   
   if (!read && blockbuff)
      for (copycount = 0; copycount < (nosectors*512); copycount++)
         *p_tbaddr++ = *p_blockbuff++;
   for (tries = 0; tries < 3; ++tries)
   {
      if (inb (FDC_DIR) & 0x80)
      {
         dchange = 1;
         seek (1);
         recalibrate ();
         motoroff ();
         puts ("FDC: Disk change detected. Trying again.\n");
         return (fdc_rw (block, blockbuff, read, nosectors));
      }
      if (!seek (track))
      {
         motoroff ();
         printf ("FDC: Error seeking to track: %d\n", track);
         return (0);
      }
      outb (FDC_CCR, 0);
      if (read)
      {
         dma_transfer (2, tbaddr, nosectors*512, 0);
         sendbyte (CMD_READ);
      }
      else
      {
         dma_transfer (2, tbaddr, nosectors*512, 1);
         sendbyte (CMD_WRITE);
      }
      sendbyte (head << 2);
      sendbyte (track);
      sendbyte (head);
      sendbyte (sector);
      sendbyte (2);
      sendbyte (floppy_type[type].spt);
      if (floppy_type[type].spt == D144_SPT)
         sendbyte (D144_GAP3RW);
      sendbyte (0xFF);

      if (!wait_fdc (1))
      {
         puts ("FDC: timed out, trying again after reset\n");
         reset ();
         return (fdc_rw (block, blockbuff, read, nosectors));
      }
      if ((status[0] & 0xC0) == 0)
         break;
      recalibrate ();
   }
   motoroff ();
   if (read && blockbuff)
   {
      p_blockbuff = blockbuff;
      p_tbaddr = (char *)0x80000;
      for (copycount = 0; copycount < (nosectors*512); copycount++)
         *p_blockbuff++ = *p_tbaddr++;
   }
   return (tries != 3);
}

static int read_block (int block, uchar *blockbuff, ulong nosectors)
{
   int track = 0, head = 0, sector = 0;
   int track2 = 0, result = 0, loop = 0;
   
   block2hts (block, &head, &track, &sector);
   block2hts (block+nosectors, &head, &track2, &sector);
   
   if (track != track2)
   {
      for (loop = 0; loop < nosectors; ++loop)
         result = fdc_rw (block+loop, blockbuff+loop*512, 1, 1);
      return (result);
   }
   return (fdc_rw (block, blockbuff, 1, nosectors));
}

static int write_block (int block, uchar *blockbuff, ulong nosectors)
{
   return (fdc_rw (block, blockbuff, 0, nosectors));
}

static int log_disk (drv_geom *g)
{
   reset ();
   
   if (read_block (17, NULL, 1))
   {
      if (g)
      {
         g->heads = floppy_type[type].heads;
         g->tracks = floppy_type[type].tracks;
         g->spt = floppy_type[type].spt;
      }
      return (1);
   }
   
   /* If it's not 1.44Mb, it's not yet supported */
   return (0);
}

void __init__ init_floppy (void)
{
   int i;

   puts ("Initializing floppy driver... \n");

   set_interrupt_gate (0x26, int_floppy);
   set_interrupt_gate (0x1C, int_floppy1);
   irq_enable (6);
   
   reset ();
   sendbyte (CMD_VERSION);
   i = getbyte ();
   
   if (i == 0x80)
      puts ("   NEC765 controller found.\n");
   else
      puts ("   Enhanced controller found.\n");
}

static void int_1C (void)
{
   if (tmout)
      --tmout;
   
   if (mtick > 0)
      --mtick;
   else if (!mtick && motor)
   {
      outb (FDC_DOR, 0x0C);
      motor = 0;
   }
}

static void irq6 (void)
{
   puts ("IRQ6");
   done = 1;
}

asm (
"  .text                   \n"
"  .align   16             \n"
"  .globl   int_floppy     \n"
"int_floppy:               \n"
"  pushal                  \n"
"  call     irq6           \n"
"  movb     $0x20,%al      \n"
"  outb     %al,$0x20      \n"
"  popal                   \n"
"  iret                    \n");

asm (
"  .text                   \n"
"  .align   16             \n"
"  .globl   int_floppy1    \n"
"int_floppy1:              \n"
"  pushal                  \n"
"  call     int_1C         \n"
"  popal                   \n"
"  iret                    \n");
