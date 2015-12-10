
/*
 *  debug.c
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
 * $Id: debug.c,v 1.4 2002/12/02 09:06:24 fredlie Exp $
 */

#include <sys/types.h>
#include <stdio.h>

static uchar getbyte (void);
static void decode (const char *s);
static void ohex (char c, int extend, int optional, int defsize);
static void do_sib (int m);
static void do_modrm (char t);

/*  
   The Intel 386 DX Programmer's Reference Manual provides a table that
   uses the following codes to assist in disassembly of 386 code (page A-3).
   The letters below are the same as the codes in the manual.  The ~ (tilde)
   is an escape character to signify expansion of the codes is
   required when the string is being outut.

   Tilde tokens in strings:
      First char after '~':
    A - Direct address
    C - Reg of R/M picks control register
    D - Reg of R/M picks debug register
    E - R/M picks operand
    F - Flag register
    G - Reg of R/M selects a general register
    I - Immediate data
    J - Relative IP offset
    M - R/M picks memory
    O - No R/M, offset only
    R - Mod of R/M picks register only
    S - Reg of R/M picks segment register
    T - reg of R/M picks test register
    X - DS:ESI
    Y - ES:EDI
    2 - prefix of two-byte opcode
    e - put in 'e' if use32 (second char is part of reg name)
   put in 'w' for use16 or 'd' for use32 (second char is 'w')
    f - Floating point (second char is esc value)
    g - do R/M group 'n'
    p - prefix
    s - Size override (second char is a,o)

      Second char after '~':
    a - Two words in memory (BOUND)
    b - Byte
    c - Byte or word
    d - DWord
    p - 32 or 48 bit pointer
    s - Six byte pseudo-descriptor
    v - Word or DWord
    w - Word
    1-8 - group number, esc value, etc
*/

static const char *const opmap1[] =
{
/* 0 */
  "add\t~Eb,~Gb", "add\t~Ev,~Gv",  "add\t~Gb,~Eb", "add\t~Gv,~Ev",
  "add\tal,~Ib",  "add\t~eax,~Iv", "push\tes",     "pop\tes",
  "or\t~Eb,~Gb",  "or\t~Ev,~Gv",   "or\t~Gb,~Eb",  "or\t~Gv,~Ev",
  "or\tal,~Ib",   "or\t~eax,~Iv",  "push\tcs",     "~2 ",
/* 1 */
  "adc\t~Eb,~Gb", "adc\t~Ev,~Gv",  "adc\t~Gb,~Eb", "adc\t~Gv,~Ev",
  "adc\tal,~Ib",  "adc\t~eax,~Iv", "push\tss",     "pop\tss",
  "sbb\t~Eb,~Gb", "sbb\t~Ev,~Gv",  "sbb\t~Gb,~Eb", "sbb\t~Gv,~Ev",
  "sbb\tal,~Ib",  "sbb\t~eax,~Iv", "push\tds",     "pop\tds",
/* 2 */
  "and\t~Eb,~Gb", "and\t~Ev,~Gv",  "and\t~Gb,~Eb", "AND\t~Gv,~Ev",
  "and\tal,~Ib",  "and\t~eax,~Iv", "~pE",         "daa",
  "sub\t~Eb,~Gb", "sub\t~Ev,~Gv",  "sub\t~Gb,~Eb", "sub\t~Gv,~Ev",
  "sub\tal,~Ib",  "sub\t~eax,~Iv", "~pC",         "das",
/* 3 */
  "xor\t~Eb,~Gb", "xor\t~Ev,~Gv",  "xor\t~Gb,~Eb", "xor\t~Gv,~Ev",
  "xor\tal,~Ib",  "xor\t~eax,~Iv", "~pS",         "aaa",
  "cmp\t~Eb,~Gb", "cmp\t~Ev,~Gv",  "cmp\t~Gb,~Eb", "cmp\t~Gv,~Ev",
  "cmp\tal,~Ib",  "cmp\t~eax,~Iv", "~pD",         "aas",
/* 4 */
  "inc\t~eax",    "inc\t~ecx",     "inc\t~edx",    "inc\t~ebx",
  "inc\t~esp",    "inc\t~ebp",     "inc\t~esi",    "inc\t~edi",
  "dec\t~eax",    "dec\t~ecx",     "dec\t~edx",    "dec\t~ebx",
  "dec\t~esp",    "dec\t~ebp",     "dec\t~esi",    "dec\t~edi",
/* 5 */
  "push\t~eax",   "push\t~ecx",    "push\t~edx",   "push\t~ebx",
  "push\t~esp",   "push\t~ebp",    "push\t~esi",   "push\t~edi",
  "pop\t~eax",    "pop\t~ecx",     "pop\t~edx",    "pop\t~ebx",
  "pop\t~esp",    "pop\t~ebp",     "pop\t~esi",    "pop\t~edi",
/* 6 */
  "pusha",       "popa",         "bound\t~Gv,~Ma", "arpl\t~Ew,~Rw",
  "~pF",         "~pG",          "~so",           "~sa",
  "push\t~Iv",    "imul\t~Gv=~Ev*~Iv", "push\t~Ib",  "imul\t~Gv=~Ev*~Ib",
  "insb\t~Yb,dx", "ins~ew\t~Yv,dx", "outsb dx,~Xb", "outs~ew dx,~Xv",
/* 7 */
  "jo\t~Jb",      "jno\t~Jb",       "jnc\t~Jb",      "jc\t~Jb",
  "jz\t~Jb",      "jnz\t~Jb",       "jbe\t~Jb",      "jnbe\t~Jb",
  "js\t~Jb",      "jns\t~Jb",       "jpe\t~Jb",      "jpo\t~Jb",
  "jl\t~Jb",      "jge\t~Jb",       "jle\t~Jb",      "jg\t~Jb",
/* 8 */
  "~g1\t~Eb,~Ib",  "~g1\t~Ev,~Iv",  "mov\tal,~Ib",   "~g1\t~Ev,~Ib",
  "test\t~Eb,~Gb", "test\t~Ev,~Gv", "xchg\t~Eb,~Gb", "xchg\t~Ev,~Gv",
  "mov\t~Eb,~Gb",  "mov\t~Ev,~Gv",  "mov\t~Gb,~Eb",  "mov\t~Gv,~Ev",
  "mov\t~Ew,~Sw",  "lea\t~Gv,~M ",  "mov\t~Sw,~Ew",  "pop\t~Ev",
/* 9 */
  "nop",           "xchg\t~eax,~ecx", "xchg\t~eax,~edx", "xchg\t~eax,~ebx",
  "xchg\t~eax,~esp", "xchg\t~eax,~ebp", "xchg\t~eax,~esi", "xchg\t~eax,~edi",
  "cbw",            "cdw",            "call\t~Ap",       "fwait",
  "push\t~eflags",   "pop\t~eflags",   "sahf",           "lahf",
/* a */
  "mov\tal,~Ov",     "mov\t~eax,~Ov",     "mov\t~Ov,al",    "mov\t~Ov,~eax",
  "movsb\t~Xb,~Yb",  "movs~ew\t~Xv,~Yv",  "cmpsb\t~Xb,~Yb", "cmps~ew\t~Xv,~Yv",
  "test\tal,~Ib",    "test\t~eax,~Iv",    "stosb\t~Yb,al",  "stos~ew\t~Yv,~eax",
  "lodsb\tal,~Xb",   "lods~ew\t~eax,~Xv", "scasb\tal,~Xb",  "scas~ew\t~eax,~Xv",
/* b */
  "mov\tal,~Ib",   "mov\tcl,~Ib",   "mov\tdl,~Ib",   "mov\tbl,~Ib",
  "mov\tah,~Ib",   "mov\tch,~Ib",   "mov\tdh,~Ib",   "mov\tbh,~Ib",
  "mov\t~eax,~Iv", "mov\t~ecx,~Iv", "mov\t~edx,~Iv", "mov\t~ebx,~Iv",
  "mov\t~esp,~Iv", "mov\t~ebp,~Iv", "mov\t~esi,~Iv", "mov\t~edi,~Iv",
/* c */
  "~g2\t~Eb,~Ib",   "~g2\t~Ev,~Ib",  "ret\t~Iw",      "ret",
  "les\t~Gv,~Mp",   "lds\t~Gv,~Mp",  "mov\t~Eb,~Ib",  "mov\t~Ev,~Iv",
  "enter\t~Iw,~Ib", "leave",        "retf\t~Iw",     "retf",
  "int\t3",         "int\t~Ib",      "into",         "iret",
/* d */
  "~g2\t~Eb,1", "~g2\t~Ev,1", "~g2\t~Eb,cl", "~g2\t~Ev,cl",
  "aam", "aad", 0, "xlat",

/*
  "esc\t0,~Ib", "esc\t1,~Ib", "esc\t2,~Ib", "esc\t3,~Ib",
  "esc\t4,~Ib", "esc\t5,~Ib", "esc\t6,~Ib", "esc\t7,~Ib",
*/

  "~f0", "~f1", "~f2", "~f3",
  "~f4", "~f5", "~f6", "~f7",


/* e */
  "loopne\t~Jb", "loope\t~Jb", "loop\t~Jb", "jcxz\t~Jb",
  "in\tal,~Ib", "in\t~eax,~Ib", "out\t~Ib,al", "out\t~Ib,~eax",
  "call\t~Jv", "jmp\t~Jv", "jmp\t~Ap", "jmp\t~Jb",
  "in\tal,dx", "in\t~eax,dx", "out\tdx,al", "out\tdx,~eax",
/* f */
  "lock~p ", 0, "repne~p ", "rep(e)~p ",
  "hlt", "cmc", "~g3", "~g0",
  "clc", "stc", "cli", "sti",
  "cld", "std", "~g4", "~g5"
};

static const char *const SecOp00[] =
{
/* 0 */
  "~g6", "~g7", "lar\t~Gv,~Ew", "lsl\t~Gv,~Ew", 0, 0, "clts", 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

static const char *const SecOp20[] =
{
/* 2 */
  "mov\t~Rd,~Cd", "mov\t~Rd,~Dd", "mov\t~Cd,~Rd", "mov\t~Dd,~Rd",
  "mov\t~Rd,~Td", 0, "mov\t~Td,~Rd", 0,
  0, 0, 0, 0, 0, 0, 0, 0
};

static const char *const SecOp80[] =
{
  "jo\t~Jv", "jno\t~Jv", "jc\t~Jv", "jnc\t~Jv",
  "jz\t~Jv", "jnz\t~Jv", "jbe\t~Jv", "ja\t~Jv",
  "js\t~Jv", "jns\t~Jv", "jpe\t~Jv", "jpo\t~Jv",
  "jl\t~Jv", "jge\t~Jv", "jle\t~Jv", "jg\t~Jv",
/* 9 */
  "seto\t~Eb", "setno\t~Eb", "setnc\t~Eb", "setc\t~Eb",
  "setz\t~Eb", "setnz\t~Eb", "setbe\t~Eb", "seta\t~Eb",
  "sets\t~Eb", "setns\t~Eb", "setp\t~Eb", "setnp\t~Eb",
  "setl\t~Eb", "setge\t~Eb", "setle\t~Eb", "setg\t~Eb",
/* a */
  "push\tfs",          "pop\tfs",        0,          "bt\t~Ev,~Gv",
  "shld\t~Ev,~Gv,~Ib", "shld\t~Ev,~Gv,cl", 0,           0,
  "push\tgs",          "pop\tgs",          0,          "bts\t~Ev,~Gv",
  "shrd\t~Ev,~Gv,~Ib", "shrd\t~Ev,~Gv,cl", 0,          "imul\t~Gv,~Ev",
/* b */
  0, 0, "lss\t~Mp", "btr\t~Ev,~Gv",
  "lfs\t~Mp", "lgs\t~Mp", "movzx\t~Gv,~Eb", "movzx\t~Gv,~Ew",
  0, 0, "~g8 ~Ev,~Ib", "btc\t~Ev,~Gv",
  "bsf\t~Gv,~Ev", "bsr\t~Gv,~Ev", "movsx\t~Gv,~Eb", "movsx\t~Gv,~Ew",
};
/* NOTE: Second byte of 2 byte OpCodes are Invalid if over 0xBF */


static const char *const groups[9][8] = 
{   /* group 0 is group 3 for ~Ev set */
  { "test\t~Ev,~Iv", "test\t~Ev,~Iv,", "not\t~Ev", "neg\t~Ev",
    "mul\t~eax,~Ev", "imul\t~eax,~Ev", "div\t~eax,~Ev", "idiv\t~eax,~Ev" },
  { "add", "or", "adc", "sbb", "and", "sub", "xor", "cmp" },
  { "rol", "ror", "rcl", "rcr", "shl", "shr", "shl", "sar" },
  { "test\t~Eb,~Ib", "test\t~Eb,~Ib,", "not\t~Eb", "neg\t~Eb",
    "mul\tal,~Eb", "imul\tal,~Eb", "div\tal,~Eb", "idiv\tal,~Eb" },
  { "inc\t~Eb", "dec\t~Eb", 0, 0, 0, 0, 0, 0 },
  { "inc\t~Ev", "dec\t~Ev", "call\t~Ev", "call\t~Ep",
    "jmp\t~Ev", "jmp\t~Ep", "push\t~Ev", 0 },
  { "sldt\t~Ew", "str\t~Ew", "lldt\t~Ew", "ltr\t~Ew",
    "verr\t~Ew", "verw\t~Ew", 0, 0 },
  { "sgdt\t~Ms", "sidt\t~Ms", "lgdt\t~Ms", "lidt\t~Ms",
    "smsw\t~Ew", 0, "lmsw\t~Ew", 0 },
  { 0, 0, 0, 0, "bt", "bts", "btr", "btc" }
};

   /* for display */
static const char *const seg_names[] = {"es","cs","ss","ds","fs","gs"};
static const char *const breg_names[] = {"al","cl","dl","bl","ah","ch","dh","bh" };
static const char *const wreg_names[] = {"ax","cx","dx","bx","sp","bp","si","di" };

#define reg(x)       (((x) >> 3) & 7)

uchar *addrIn;
short prefix, opsize;
uchar flag_modrmv, flag_sibv;
uchar modrmv, sibv;

/*****************************************************
Gets a byte to disassemble and update addrIn.
******************************************************/

static uchar getbyte (void)
{
   return (*addrIn++);
}

static inline uchar modrm (void)
{
   if (!flag_modrmv)
   {
      modrmv = getbyte ();
      flag_modrmv = 1;
   }
   return (modrmv);
}

static inline uchar sib (void)
{
   if (!flag_sibv)
   {
      sibv = getbyte ();
      flag_sibv = 1;
   }
   return (sibv);
}

static inline int bytes (char c)
{
   switch (c)
   {
      case 'b': return (1);
      case 'w': return (2);
      case 'd': return (4);
      case 'v': return (opsize == 32 ? 4 : 2);
   }
   return (0);
}

static void ohex (char c, int extend, int optional, int defsize)
{
   int n, s, i;
   uchar buf[6];
   
   n = s = 0;
   switch (c)
   {
      case 'a': break;
      case 'b': n = 1; break;
      case 'w': n = 2; break;
      case 'd': n = 4; break;
      case 's': n = 6; break;
      case 'c':
      case 'v': n = (defsize == 32) ? 4 : 2; break;
      case 'p': n = (defsize == 32) ? 6 : 4; s = 1; break;
   }
   for (i = 0; i < n; ++i);
      buf[i] = getbyte ();
   for (; i < extend; ++i)
      buf[i] = (buf[i-1] & 0x80) ? 0xFF : 0;
   if (s)
   {
      printf ("%02X%02X", buf[n-1], buf[n-2]);
      n -= 2;
   }
   if (extend > n)
   {
      if (!optional)
    puts ("+");
      n = 4;
   }
   switch (n)
   {
      case 1:
    printf ("%02X", buf[0]);
    break;
      case 2:
    printf ("%02X%02X", buf[1], buf[0]);
    break;
      case 4:
    printf ("%02X%02X%02X%02X", buf[3], buf[2], buf[1], buf[0]);
    break;
   }
}

static void reg_name (uchar which, char size)
{
   if (size == 'F')
      printf ("st%d", which);
   else
   {
      if ((size == 'v' && opsize == 32) || size == 'd')
    puts ("e");
      if (size == 'b')
    printf ("%s", breg_names[which]);
      else
    printf ("%s", wreg_names[which]);
   }
}

static void escape (char c, char t)
{
  int delta, vals = 0;
  uchar b2;
  char valsb;
  short valsw;

  switch (c)
  {
    case 'A':                             /* Direct Address */
       ohex (t, 4, 0, 32);
       break;
    case 'C':                             /* Reg of R/M picks control reg */
      printf ("cr%d",reg (modrm ()));
       break;
    case 'D':                             /* Reg of R/M pick debug reg */
      printf ("dr%d",modrm ());
      break;
    case 'E':                             /* R/M picks operand */
      do_modrm (t);
      break;
    case 'G':                             /* Reg of R/M picks general reg */
      if (t == 'F')
      reg_name ((modrm () & 7), t);
      else
      reg_name (reg (modrm ()), t);
      break;
    case 'I':                             /* Immediate data */
      ohex (t, 0, 0, opsize);
      break;
    case 'J':                             /* Relative IP offset */
      switch (bytes (t))
      {
         case 1:
           valsb = getbyte ();            /* must remian signed! */
           vals = valsb;
           break;
         case 2:
           valsb = getbyte ();        /*RAB  Made SIGNEd bytes/Words */
           valsw = getbyte () << 8;
           vals = valsw + valsb;
           break;
         case 4:
           vals = getbyte ();
           vals |= getbyte () << 8;
           vals |= getbyte () << 16;
           vals |= getbyte () << 24;
           break;
      }
      delta = (ulong)addrIn + vals;
      printf ("%x", delta);
      break;
    case 'M':                             /* R/M picks memory */
      do_modrm (t);
      break;
   case 'O':                             /* NO R/M, Offset only */
      decode ("~p:[");
      ohex (t, 4, 0, 32);
      printf ("]");
      break;
    case 'R':                             /* Mod of R/M pick REG only */
      do_modrm (t);
      break;
    case 'S':                             /* Reg of R/M picks seg reg */
      printf ("%s", seg_names[reg (modrm ())]);
      break;
    case 'T':                             /* Reg of R/M picks test reg */
      printf ("tr%d",modrm ());
      break;
    case 'X':                             /* DS:ESI */
      printf ("ds:[esi]");
      break;
   case 'Y':                             /* ES:EDI */
      printf ("es:[edi]");
      break;
    case '2':                             /* Prefix of 2 byte opcode */
      b2 = getbyte ();
      if (b2 < 0x10)
         decode (SecOp00[b2]);
      else if ((b2 > 0x1F) && (b2 < 0x30))
         decode (SecOp20[b2-0x20]);
      else if ((b2 > 0x7F) && (b2 < 0xC0))
         decode (SecOp80[b2-0x80]);
      else
          printf ("<bogus>");
      break;
   case 'e':                 /*  t is part of reg name */
      if (opsize == 32)
      {
         if (t == 'w')     /* put out "d" if t is "w" on 32 bit opsize */
            printf ("D");
         else
         {
            printf ("E");  /* put out "E" if not t <> "w" then put t */
            printf ("%c",t);
         }
      }
      else 
         printf ("%c",t);
      break;
    case 'f':                /* floating point */
       printf ("<Float Op>");

/*              floating_point(t-'0');  */

      break;
    case 'g':                             /* do R/M group 'n' */
      decode (groups[t-'0'][reg (modrm ())]);
      break;
    case 'p':                             /* Segment prefix */
      switch (t)
      {
         case 'C':                         /* CS */
         case 'D':                         /* DS */
         case 'E':                         /* ES */
         case 'F':                         /* FS */
         case 'G':                         /* GS */
         case 'S':                         /* SS */
           prefix = t;
           decode (opmap1[getbyte ()]);
           break;
         case ':':
           if (prefix)
              printf ("%cs:", prefix);
           break;
         case ' ':
           decode (opmap1[getbyte ()]);
           break;
      }
      break;
    case 's':                                                           /* Size override */
      if (t == 'o')
      {                                          /* o is operand */
         opsize = 48 - opsize;
         decode (opmap1[getbyte ()]);
      }
      break;
   }
}

static void decode (const char *s)
{
   char c;

   if (s == 0)                   /* if NULL pointer, then it's BAD */
      puts ("<invalid>");
   while ((c = *s++) != 0)       /* put next char in c */
   {
      if (c == '~')               /* if c is ~ then ESCAPE */
      {
         c = *s++;                 /* get letter representing value */
         escape (c, *s++);
      }
      else if (c == ' ')              /* space */
         puts (" ");
      else
         printf ("%c", c);         /* else put out the char found! */
   }
}


/* outputs 'scale-index-base' instructions */

static void do_sib (int m)
{
  int s, i, b;
  s = ((sib ()) >> 6) & 7;               /* SSxxxxxx Scale */
  i = ((sib ()) >> 3) & 7;               /* xxIIIxxx Index */
  b = sib () & 7;                                /* xxxxxBBB Base  */
  switch (b)
  {
    case 0: decode("~p:[eax"); break;
    case 1: decode("~p:[ecx"); break;
    case 2: decode("~p:[edx"); break;
    case 3: decode("~p:[ebp"); break;
    case 4: decode("~p:[esp"); break;
    case 5:
      if (m == 0)
      {
         decode ("~p:[");
         ohex ('d', 4, 0, 32);
      }
      else
         decode("~p:[ebp");
      break;
    case 6: decode("~p:[esi"); break;
    case 7: decode("~p:[edi"); break;
  }
  switch (i)
  {
    case 0: puts ("+eax"); break;
    case 1: puts ("+ecx"); break;
    case 2: puts ("+edx"); break;
    case 3: puts ("+ebx"); break;
    case 4: break;
    case 5: puts ("+ebp"); break;
    case 6: puts ("+esi"); break;
    case 7: puts ("+edi"); break;
  }
  if (i != 4)
    switch (s)
    {
      case 0: break;
      case 1: puts ("*2"); break;
      case 2: puts ("*4"); break;
      case 3: puts ("*8"); break;
    }
}

static void do_modrm (char t)
{
  int m;
  int r;

  m = ((modrm()) >> 6) & 7;
  r = modrm() & 7;

  if (m == 3)
  {
    reg_name(r, t);
    return;
  }
  if ((m == 0) && (r == 5))
  {
    decode("~p:[");
    ohex('d', 4, 0, 32);
    puts ("]");
    return;
  }

  if (r != 4)
    decode("~p:[");

  switch (r)
    {
      case 0: puts ("eax"); break;
      case 1: puts ("ecx"); break;
      case 2: puts ("edx"); break;
      case 3: puts ("ebx"); break;
      case 4: do_sib (m); break;
      case 5: puts ("ebp"); break;
      case 6: puts ("esi"); break;
      case 7: puts ("edi"); break;
  }
  switch (m)
  {
    case 1:
      ohex ('b', 4, 0, 32);
      break;
    case 2:
      puts ("+");
      ohex ('v', 4, 0, 32);
      break;
  }
  puts ("]");
}

ulong disassemble (ulong Addr)
{
  prefix = 0;
  flag_modrmv = 0;
  flag_sibv = 0;
  opsize = 32;      /* default operand size is DWORD */
  addrIn = (uchar *)Addr;

  printf ( "%08x   ", (uint)addrIn);

  decode (opmap1[getbyte ()]);    /* decode instruction and output */

  puts ("\n");
  return ((ulong)addrIn);
}
