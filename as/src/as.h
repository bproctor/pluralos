
/*
 *  as.h
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
 * $Id: as.h,v 1.2 2003/01/02 23:31:21 fredlie Exp $
 */

#ifndef __AS_H__
#define __AS_H__

typedef struct token_type
{
   char *name;    /* Name of the reserved word */
   int id;        /* Token identifier for the parser */
   int value;     /* Value or opcode */
} token_type;

typedef struct symbol
{
   char *name;
   unsigned int addr;
   unsigned int type;
   struct symbol *left;
   struct symbol *right;
} symbol;

void error (const char *, ...);
void warning (const char *, ...);
void fatal_error (const char *, ...);
int yylex (void);
int yyparse (void);
void emit (void *, int);
void reg (int);

#define prefix(c)    (((c) != code_bits) ? emitb (0x66) : 0)
#define prefix_s(c)  (((c) != code_bits) ? emitw (0x6667) : 0)

static inline void emitb (int c)
{
   unsigned char b = c;
   emit (&b, 1);
}

static inline void emitw (int w)
{
   emitb (w);
   emitb (w >> 8);
}

static inline void emitd (unsigned long d)
{
   emitw (d);
   emitw (d >> 16);
}

static inline void modrm (int mod, int reg, int rm)
{
   emitb ((mod << 6) | (reg << 3) | rm);
}

unsigned long pc, outsize;
void *outbin;

#endif /* __AS_H__ */
