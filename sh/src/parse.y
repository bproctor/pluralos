
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
 * $Id: parse.y,v 1.5 2003/01/23 06:44:08 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "sh.h"

#define YYDEBUG         1
#define YYERROR_VERBOSE	1
#define yyerror         error


static int yylex (void);
static void help (void);

%}

%token tALIAS
%token tBG
%token tCASE tCD tCOMMAND tCONTINUE
%token tDO tDONE
%token tELIF tELSE tESAC tEXEC tEXIT
%token tFALSE tFG tFI tFOR tFUNCTION
%token tGETOPS
%token tHELP tHISTORY
%token tIF
%token tJOBS
%token tKILL
%token tLET tLOCAL tLOGOUT
%token tNEWGRP
%token tPRINTF tPWD
%token tRETURN
%token tSELECT tSET tSHIFT
%token tTHEN tTRUE
%token tUNALIAS tUNSET tUNTIL
%token tWAIT tWHILE

%start program

%%


program
   : tHELP '\n'      { help (); }
   ;



%%

static int yylex (void)
{
   int c;
   

lex_top:
   c = getchar ();
   switch (c)
   {
      case ' ':
         goto lex_top;
      case 'a': case 'b': case 'c': case 'd':
      case 'e': case 'f': case 'g': case 'h':
      case 'i': case 'j': case 'k': case 'l':
      case 'm': case 'n': case 'o': case 'p':
      case 'q': case 'r': case 's': case 't':
      case 'u': case 'v': case 'w': case 'x':
      case 'y': case 'z':
         break;
   }
   
   return (0);
}

static void help (void)
{
   puts (
      "Commands:\n"
      "\n"
      "alias [name[=string] ...]       bg [id ...]\n"
      "break [n]                       case word in [pat [|pat]\n"
      "cd [-L] [-P] [dir]              command [-pvV] cmd [arg ...]\n"
      "continue [n]                    echo [-n] string\n"
      "eval [n]                        exec [-cl] [-a name] cmd\n"
      "exit [n]                        export [-nf] [name[=string]]\n"
      "false                           fc [-e name] [-nlr] [first] [last]\n"
      "fg [job]                        for name [in words ...;] do ... done\n"
      "function name { ...; }          getopts\n"
      "history                         if\n"
      "jobs                            kill\n"
      "let                             local\n"
      "logout                          newgrp\n"
      "printf                          pwd\n"
      "return                          shift\n"
      "suspend                         true\n"
      "until                           while\n");
}

