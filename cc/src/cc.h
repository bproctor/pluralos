
/*
 *  cc.h
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
 * $Id: cc.h,v 1.1 2002/12/18 06:10:47 fredlie Exp $
 */
 
#ifndef __CC_H__
#define __CC_H__

typedef struct
{
   int ansi89 : 1;
   int ansi99 : 1;
   int warn_ansi89 : 1;
   int warn_ansi99 : 1;
} flag_type;

typedef struct Symbol
{
   char *name;
   unsigned long type;
   unsigned long value;
   struct Symbol *left;
   struct Symbol *right;
} Symbol;


void error (const char *, ...);
void warning (const char *, ...);
void fatal_error (const char *, ...);
int  get (void);
void unget (int);
void preprocess (void);
int  yylex (void);
int  yyparse (void);
Symbol *insert_symbol (char *, unsigned long);
void asm_start_file (void);
void asm_finish_file (void);

#define xAUTO        0x00000001
#define xCHAR        0x00000002
#define xCONST       0x00000004
#define xENUM        0x00000008
#define xENUMDEF     0x00000010
#define xENUMMEM     0x00000020
#define xEXTERN      0x00000040
#define xINT         0x00000080
#define xLONG        0x00000100
#define xREGISTER    0x00000200
#define xRESTRICT    0x00000400
#define xSHORT       0x00000800
#define xSIGNED      0x00001000
#define xSTATIC      0x00002000
#define xSTRUCT      0x00004000
#define xSTRUCTDEF   0x00008000
#define xSTRUCTMEM   0x00010000
#define xTYPEDEF     0x00020000
#define xUNION       0x00040000
#define xUNIONDEF    0x00080000
#define xUNIONMEM    0x00100000
#define xUNSIGNED    0x00200000
#define xVOID        0x00400000
#define xVOLATILE    0x00800000
#define xPOINTER     0x01000000

#endif /* __CC_H__ */
