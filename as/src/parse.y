
%{

/*
 *  parse.y
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
 * $Id: parse.y,v 1.2 2003/01/02 23:31:21 fredlie Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "as.h"

#define YYDEBUG   1
#define YYERROR_VERBOSE 1
#define yyerror error

extern int code_bits;
extern int lineno;
extern FILE *outfile;

static const char *reg8[] = 
   {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};

static const char *reg16[] = 
   {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};

static const char *reg32[] = 
   {"eax", "ebx", "ecx", "edx", "esp", "ebp", "esi", "edi"};

int i;

%}

%expect 2

%union {
   unsigned long long i;
   char *string;
   symbol *sym;
}

%token <sym> tIDENTIFIER
%token <i> tNUMBER tPC
%token <s> tSTRING

%token tAAD tAAM tARPL
%token tBOUND tBSWAP
%token tCALL
%token tDB tDD tDEC tDQ tDT tDUP tDW
%token tENTER tEQU
%token tIDIV tIMUL tIN tINVLPG tINC tINT
%token tJMP
%token tLEA
%token tOUT
%token tTEST

%token <i> tARITH
%token <i> tBSx tBTx
%token <i> tCMOVcc tCREG
%token <i> tDREG
%token <i> tJcc
%token <i> tLOOP
%token <i> tMOV tMREG
%token <i> tONEBYTE tONEBYTE16 tONEBYTE16S tONEBYTE32 tONEBYTE32S
%token <i> tREG8 tREG16 tREG32
%token <i> tSETcc tSHIFT tSREG
%token <i> tTHREEBYTE tTREG tTWOBYTE tTWOBYTE16 tTWOBYTE32

%type <i> const scaledindex

%right '=' tADDE tANDE tCOME tDIVE tMODE tMULE tORE tSHLE tSHRE tSUBE tXORE
%left tDOR
%left tDAND
%left '|'
%left '^'
%left '&'
%left tDEQ tNE
%left '<' '>' tGE tLE
%left tLSHIFT tRSHIFT
%left '+' '-'
%left '*' '/' '%'
%right UNARY tDADD tDSUB
%left '('
%left '['

%start program

%%

program
   : lines
   ;

lines
   : line
   | lines line
   ;

line
   : '\n'
   | statement '\n'
   ;

statement
   : tAAD                        { emitw (0xD50A); }
   | tAAD const                  { emitb (0xD5), emitb ($2); }
   | tAAM                        { emitw (0xD40A); }
   | tAAM const                  { emitb (0xD5), emitb ($2); }
   | tARITH tREG8 ',' const
      {
         if ($2)
            emitb (0x80), modrm (3, $1, $2);
         else
            modrm (0, $1, 4);
         emitb ($4);
      }
   | tARITH tREG16 ',' const     { prefix (16); }
   | tARITH tREG32 ',' const     { prefix (32); }
   | tARITH tREG8  ',' tREG8     { emitb ($1*8); modrm(3, $4, $2); }
   | tARITH tREG16 ',' tREG16
      {
         prefix (16);
         emitb ($1*8+1);
         modrm (3, $4, $2);
      }
   | tARITH tREG32 ',' tREG32
      {
         prefix (32);
         emitb ($1*8+1);
         modrm (3, $4, $2);
      }
   | tARITH tREG8  ',' regmem    { emitb ($1*8+2), reg ($2); }
   | tARITH tREG16 ',' regmem    { prefix (16); emitb ($1*8+3); reg ($2); }
   | tARITH tREG32 ',' regmem    { prefix (32); emitb ($1*8+3); reg ($2); }
   | tARITH regmem ',' tREG8     { emitb ($1*8), reg ($4); }
   | tARITH regmem ',' tREG16    { prefix (16); emitb ($1*8+1); reg ($4); }
   | tARITH regmem ',' tREG32    { prefix (32); emitb ($1*8+1); reg ($4); }
   | tARITH regmem ',' const     { }
   | tARPL tREG16 ',' tREG16     { emitb (0x63); modrm (3, $4, $2); }
   | tARPL regmem ',' tREG16     { emitb (0x63); reg ($4); }
   | tBOUND tREG16 ',' regmem    { prefix (16); emitb (0x62); reg ($2); }
   | tBOUND tREG32 ',' regmem    { prefix (32); emitb (0x62); reg ($2); }
   | tBSx tREG16 ',' tREG16      { prefix (16); emitb (0x0F); emitb ($1*8+0x83); modrm (3, $4, $2); }
   | tBSx tREG32 ',' tREG32      { prefix (32); emitb (0x0F); emitb ($1*8+0x83); modrm (3, $4, $2); }
   | tBSx tREG16 ',' regmem      { prefix (16); }
   | tBSx tREG32 ',' regmem      { prefix (32); }
   | tBSWAP tREG32               { prefix (32); }
   | tBTx tREG16 ',' tREG16
      {
         prefix (16);
         emitb (0x0F);
         emitb ($1*8+0x83);
         modrm (3, $4, $2);
      }
   | tBTx tREG32 ',' tREG32
      {
         prefix (32);
         emitb (0x0F);
         emitb ($1*8+0x83);
         modrm (3, $4, $2);
      }
   | tBTx tREG16 ',' const
      {
         prefix (16);
         emitb (0x0F);
         emitb (0xBA);
         modrm (3, $1, $2);
         emitb ($4);
      }
   | tBTx tREG32 ',' const
      {
         prefix (32);
         emitb (0x0F);
         emitb (0xBA);
         modrm (3, $1, $2);
         emitb ($4);
      }
   | tBTx regmem ',' tREG16      { prefix (16); emitb (0x0F); emitb ($1*8+0x83); reg ($4); }
   | tBTx regmem ',' tREG32      { prefix (32); emitb (0x0F); emitb ($1*8+0x83); reg ($4); }
   | tBTx regmem ',' const       { }
   | tCALL const                 { }
   | tCALL tREG16                { prefix (16); }
   | tCALL tREG32                { prefix (32); }
   | tCALL regmem                { }
   | tCMOVcc tREG16 ',' regmem   { prefix (16); emitb (0x0F); emitb ($1+0x40); reg ($2); }
   | tCMOVcc tREG32 ',' regmem   { prefix (32); emitb (0x0F); emitb ($1+0x40); reg ($2); }
   | tDB dblist                  { }
   | tDD ddlist                  { }
   | tDEC tREG8                  { emitb (0xFE); modrm (3, 1, $2); }
   | tDEC tREG16                 { prefix (16); emitb ($2+0x48); }
   | tDEC tREG32                 { prefix (32); emitb ($2+0x48); }
   | tDEC regmem                 { }
   | tDQ dqlist                  { }
   | tDT dtlist                  { }
   | tDW dwlist                  { }
   | tENTER const ',' const      { emitb (0xC8); emitw ($2); emitb ($4); }
   | tIDIV regmem                { }
   | tIMUL tREG8                 { emitb (0xF6); }
   | tIMUL tREG16		 { prefix (16); emitb (0xF7); }
   | tIMUL tREG32		 { prefix (32); emitb (0xF8); }
   | tIMUL regmem		 { }
   | tIMUL tREG16 ',' tREG16     { prefix (16); emitb (0x0F); emitb (0xAF); modrm (3, $4, $2); }
   | tIMUL tREG32 ',' tREG32     { prefix (32); emitb (0x0F); emitb (0xAF); modrm (3, $4, $2); }
   | tIMUL tREG16 ',' regmem     { prefix (16); emitb (0x0F); emitb (0xAF); reg ($2); }
   | tIMUL tREG32 ',' regmem     { prefix (32); emitb (0x0F); emitb (0xAF); reg ($2); }
   | tIMUL tREG16 ',' tREG16 ',' const { prefix (16); emitb (0x6B); }
   | tIMUL tREG32 ',' tREG32 ',' const { prefix (32); emitb (0x6B); }
   | tIMUL tREG16 ',' regmem ',' const { prefix (16); emitb (0x69); }
   | tIMUL tREG32 ',' regmem ',' const { prefix (32); emitb (0x69); }
   | tIMUL tREG16 ',' const 
      { 
         prefix (16);
         if ($4 > 0xFF)
            emitb (0x69), emitw ($4);
         else
            emitb (0x6B), emitb ($4);
      }
   | tIMUL tREG32 ',' const
      { 
         prefix (32);
         if ($4 > 0xFF)
            emitb (0x69), emitd ($4);
         else
            emitb (0x6B), emitb ($4);
      }
   | tIN tREG8  ',' tREG16
      { 
         if ($2 != 0)
            error ("`%s' is invalid for `in'", reg8[$2]);
         if ($4 != 3)
            error ("`%s' is invalid for `in'", reg16[$2]);
         emitb (0xEC);
      }
   | tIN tREG16 ',' tREG16
      {
         if ($2 != 0)
            error ("`%s' is invalid for `in'", reg16[$2]);
         if ($4 != 3)
            error ("`%s' is invalid for `in'", reg16[$2]);
         prefix (16);
         emitb (0xED);
      }
   | tIN tREG32 ',' tREG16
      {
         if ($2 != 0)
            error ("`%s' is invalid for `in'", reg32[$2]);
         if ($4 != 3)
            error ("`%s' is invalid for `in'", reg16[$2]);
         prefix (32);
         emitb (0xED);
      }
   | tIN tREG8  ',' const
      {
         if ($2 != 0)
            error ("`%s' is invalid for `in'", reg8[$2]);
         if ($4 > 0xFF)
            error ("Operand must be <= 0xFF");
         emitb (0xE4);
         emitb ($4);
      }
   | tIN tREG16 ',' const
      {
         if ($2 != 0)
            error ("`%s' is invalid for `in'", reg16[$2]);
         if ($4 > 0xFF)
            error ("Operand must be <= 0xFF");
         prefix (16);
         emitb (0xE5);
         emitb ($4);         
      }
   | tIN tREG32 ',' const
      {
         if ($2 != 0)
            error ("`%s' is invalid for `in'", reg32[$2]);
         if ($4 > 0xFF)
            error ("Operand must be <= 0xFF");
         prefix (16);
         emitb (0xE4);
         emitb ($4);
      }
   | tINC tREG8                  { }
   | tINC tREG16                 { prefix (16); emitb ($2+0x40); }
   | tINC tREG32                 { prefix (32); emitb ($2+0x40); }
   | tINT const                  { emitb (0xCD), emitb ($2); }
   | tINVLPG                     { }
   | tJcc                        { }
   | tJMP                        { }
   | tLEA                        { }
   | tLOOP const                 { }
   | tLOOP const ',' tREG16      { }
   | tLOOP const ',' tREG32      { }
   | tMOV                        { }
   | tONEBYTE                    { emitb ($1); }
   | tONEBYTE16                  { prefix (16); emitb ($1); }
   | tONEBYTE32                  { prefix (32); emitb ($1); }
   | tONEBYTE16S                 { prefix_s (16); emitb ($1); }
   | tONEBYTE32S                 { prefix_s (32); emitb ($1); }
   | tOUT tREG16 ',' tREG8
      {
         if ($2 != 2)   
            error ("`%s' invalid for `out'", reg16[$2]);
         if ($4 != 0)
            error ("`%s' invalid for `out'", reg8[$4]);
         emitb (0xEE);
      }
   | tOUT tREG16 ',' tREG16
      {
         if ($2 != 2)   
            error ("`%s' invalid for `out'", reg16[$2]);
         if ($4 != 0)
            error ("`%s' invalid for `out'", reg16[$4]);
         prefix (16);
         emitb (0xEF);
      }
   | tOUT tREG16 ',' tREG32
      {
         if ($2 != 2)   
            error ("`%s' invalid for `out'", reg16[$2]);
         if ($4 != 0)
            error ("`%s' invalid for `out'", reg32[$4]);
         prefix (32);
         emitb (0xEF);
      }
   | tOUT const ',' tREG8
      {
         if ($4 != 0)
            error ("`%s' invalid for `out'", reg8[$4]);
         if ($2 > 0xFF)
            error ("Operand must be <= 0xFF");
      }
   | tOUT const ',' tREG16
      {
         if ($4 != 0)
            error ("`%s' invalid for `out'", reg16[$4]);
         if ($2 > 0xFF)
            error ("Operand must be <= 0xFF");
         prefix (16);
      }
   | tOUT const ',' tREG32
      {
         if ($4 != 0)
            error ("`%s' invalid for `out'", reg32[$4]);
         if ($2 > 0xFF)
            error ("Second operand must be <= 0xFF");
         prefix (32);
      }
   | tSETcc                      { }
   | tSHIFT tREG8  ',' const
      {
         if ($4 == 1)
            emitb (0xD0), modrm (3, $2, 0);
         else
            emitb (0xC0), modrm (3, $2, 0), emitb ($4);
      }
   | tSHIFT tREG8  ',' tREG8     { }
   | tSHIFT tREG16 ',' const
      {
         prefix (32);
         if ($4 == 1)
            emitb (0xD1), modrm (3, $2, 0);
         else
            emitb (0xC1), modrm (3, $2, 0), emitb ($4);
      }
   | tSHIFT tREG16 ',' tREG8     { }
   | tSHIFT tREG32 ',' const     { }
         {
         prefix (32);
         if ($4 == 1)
            emitb (0xD1), modrm (3, $2, 0);
         else
            emitb (0xC1), modrm (3, $2, 0), emitb ($4);
      }
   | tSHIFT tREG32 ',' tREG8     { }
   | tTEST                       { }
   | tTHREEBYTE                  { emitb ($1 >> 16), emitb ($1 >> 8), emitb ($1); }
   | tTWOBYTE                    { emitb ($1 >> 8), emitb ($1); }
   | tTWOBYTE16                  { prefix (16); emitw ($1); }
   | tTWOBYTE32                  { prefix (32); emitw ($1); }
   ;

dblist
   : dbitem
   | dblist ',' dbitem
   ;

dbitem
   : const                    { emitb ($1); }
   | tSTRING                  { emit (yylval.string, strlen (yylval.string)); }
   | const tDUP const         { for (i=0; i<$1; ++i) emitb ($3); }
   ;

dwlist
   : dwitem
   | dwlist ',' dwitem
   ;

dwitem
   : const                    { emitw ($1); }
   | const tDUP const         { for (i=0; i<$1; ++i) emitw ($3); }
   ;
   
ddlist
   : dditem
   | ddlist ',' dditem
   ;

dditem
   : const                    { emitd ($1); }
   | const tDUP const         { for (i=0; i<$1; ++i) emitd ($3); }
   ;

dqlist
   : dqitem
   | dqlist ',' dqitem
   ;

dqitem
   : const                    { emitd ($1 >> 32); emitd ($1); }
   | const tDUP const         { for (i=0; i<$1; ++i) emitd ($3 >> 32), emitd ($3); }
   ;

dtlist
   : dtitem
   | dtlist ',' dtitem
   ;

dtitem
   : const                    { }
   | const tDUP const         { }
   ;

regmem
   : regmemitem '[' regmemexpr ']'  { }
   | '[' regmemexpr ']'             { }
   | tSREG ':' '[' regmemexpr ']'   { }
   ;

regmemexpr
   : regmemitem                  { }
   | regmemitem '+' regmemitem   { }
   | regmemitem '-' const        { }
   ;

regmemitem
   : tSREG ':' regmemitem     { }
   | tREG16                   { }
   | tREG32                   { }
   | scaledindex              { }
   | tIDENTIFIER              { }
   | const                    { }
   ;

scaledindex
   : tREG32 '*' const         { }
   | const '*' tREG32         { }
   | tREG32 tLSHIFT const     { }
   ;

const
   : tNUMBER               { $$ = $1; }
   | tPC                   { $$ = $1; }
   | const '+' const       { $$ = $1 + $3; }
   | const '-' const       { $$ = $1 - $3; }
   | const '/' const       { $$ = $1 / $3; }
   | const '*' const       { $$ = $1 * $3; }
   | const '%' const       { $$ = $1 % $3; }
   | const '^' const       { $$ = $1 ^ $3; }
   | const '|' const       { $$ = $1 | $3; }
   | const '&' const       { $$ = $1 & $3; }
   | const tRSHIFT const   { $$ = $1 >> $3; }
   | const tLSHIFT const   { $$ = $1 << $3; }
   | const tDEQ const      { $$ = $1 == $3; }
   | const tNE const       { $$ = $1 != $3; }
   | const tGE const       { $$ = $1 >= $3; }
   | const tLE const       { $$ = $1 <= $3; }
   | const '<' const       { $$ = $1 < $3; }
   | const '>' const       { $$ = $1 > $3; }
   | const tDOR const      { $$ = $1 || $3; }
   | const tDAND const     { $$ = $1 && $3; }
   | '(' const ')'         { $$ = $2; }
   | %prec UNARY '-' const { $$ = -$2; }
   | %prec UNARY '+' const { $$ = $2; }
   | %prec UNARY '!' const { $$ = !$2; }
   | %prec UNARY '~' const { $$ = ~$2; }
   ;

%%

void emit (void *ptr, int len)
{
   while (pc + len > outsize)
   {
      outsize += 4096;
      outbin = realloc (outbin, outsize);
   }
   memcpy (outbin + pc, ptr, len);
   pc += len;
}

void reg (int x)
{

}
