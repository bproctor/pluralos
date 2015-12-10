
%{

/*
 *  bc -- Arbitrary precision arithmetic language
 *  Copyright (c) 2003 Brad Proctor
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
 * $Id: bc.y,v 1.5 2003/02/16 18:46:40 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

#define YYERROR_VERBOSE 1
#define YYDEBUG         1
#define yyerror         error
#define get()           getc(stdin)
#define unget(c)        ungetc(c, stdin)

static int yylex (void);

%}

%union {
   char *s;
   char l;
   int i;
}

%token tEOF
%token <s> tSTRING
%token tLETTER
%token tNUMBER

%token tMUL_OP tASSIGN_OP tREL_OP tINC_DEC
%token tDEFINE tQUIT tBREAK tLENGTH tRETURN tFOR tIF tWHILE
%token tSQRT tSCALE tIBASE tOBASE tAUTO

%start program

%%

program
   : tEOF
   | input_item program
   ;

input_item
   : semicolon_list '\n'
   | function
   ;

semicolon_list
   : /* empty */
   | statement
   | semicolon_list ';' statement
   | semicolon_list ';'
   ;

statement_list
   : /* empty */
   | statement
   | statement_list '\n'
   | statement_list '\n' statement
   | statement_list ';'
   | statement_list ';' statement
   ;

statement
   : expression
   | tSTRING
   | tBREAK
   | tQUIT
   | tRETURN
   | tRETURN '(' return_expression ')'
   | tFOR '(' expression ';' relational_expression ';' expression ')'
   | tIF '(' relational_expression ')' statement
   | tWHILE '(' relational_expression ')' statement
   | '{' statement_list '}'
   ;

function
   : tDEFINE tLETTER '(' opt_parameter_list ')' 
      '{' '\n' opt_auto_define_list statement_list '}'
   ;

opt_parameter_list
   : /* empty */
   | parameter_list
   ;

parameter_list
   : tLETTER
   | define_list ',' tLETTER
   ;

opt_auto_define_list
   : /* empty */
   | tAUTO define_list '\n'
   | tAUTO define_list ';'
   ;

define_list
   : tLETTER
   | tLETTER '[' ']'
   | define_list ',' tLETTER
   | define_list ',' tLETTER '[' ']'
   ;

opt_argument_list
   : /* empty */
   | argument_list
   ;

argument_list
   : expression
   | tLETTER '[' ']' ',' argument_list
   ;

relational_expression
   : expression
   | expression tREL_OP expression
   ;

return_expression
   : /* empty */
   | expression
   ;

expression
   : named_expression
   | tNUMBER
   | tLETTER
   | '(' expression ')'
   | tLETTER '(' opt_argument_list ')'
   | '-' expression
   | expression '+' expression
   | expression '-' expression
   | expression tMUL_OP expression
   | expression '^' expression
   | tINC_DEC named_expression
   | named_expression tINC_DEC
   | named_expression tASSIGN_OP expression
   | tLENGTH '(' expression ')'
   | tSQRT '(' expression ')'
   | tSCALE '(' expression ')'
   ;

named_expression
   : tLETTER '[' expression ']'
   | tSCALE
   | tIBASE
   | tOBASE
   ;
   
%%

static const char help_text[] =
{
   "Usage: bc long_option\n"
   "       bc [-l][file ...]\n"
   "Arbitrary precision arithmetic language.\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static int yylex (void)
{
   int c;

lex_top:   
   c = get();
   switch (c)
   {
      case ' ':
      case '\a':
      case '\b':
      case '\f':
      case '\n':
      case '\r':
      case '\t':
      case '\v':
         goto lex_top;

      case '0': case '1': case '2':
      case '3': case '4': case '5':
      case '6': case '7': case '8':
      case '9':
         fscanf (stdin, "%d", &yylval.i);
         return (tNUMBER);
      case 'a': case 'c': case 'd': case 'e': case 'g':
      case 'h': case 'j': case 'k': case 'l': case 'm':
      case 'n': case 'o': case 'p': case 'q': case 'r':
      case 't': case 'u': case 'v': case 'x': case 'y':
      case 'z': case 'A': case 'B': case 'C': case 'D':
      case 'E': case 'F': case 'G': case 'H': case 'I':
      case 'J': case 'K': case 'L': case 'M': case 'N':
      case 'O': case 'P': case 'Q': case 'R': case 'S':
      case 'T': case 'U': case 'V': case 'W': case 'X':
      case 'Y': case 'Z':
         yylval.l = c;
         return (tLETTER);
      case 'b':
         if ((c = get()) != 'r') { unget (c); return (tLETTER); }
         if ((c = get()) != 'e') { unget (c); return (tLETTER); }
         if ((c = get()) != 'a') { unget (c); return (tLETTER); }
         if ((c = get()) != 'k') { unget (c); return (tLETTER); }
         return (tBREAK);
      case 'i':
         if ((c = get()) != 'f') { unget (c); return (tLETTER); }
         return (tIF);
      case 'f':
         if ((c = get()) != 'o') { unget (c); return (tLETTER); }
         if ((c = get()) != 'r') { unget (c); return (tLETTER); }
         return (tFOR);
      case 's':
         if ((c = get()) != 'q') { unget (c); return (tLETTER); }
         if ((c = get()) != 'r') { unget (c); return (tLETTER); }
         if ((c = get()) != 't') { unget (c); return (tLETTER); }
         return (tSQRT);
      default:
         return (c);
   }
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   progname = argv[0];
   
   if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("bc: version "VERSION);
         return (EXIT_SUCCESS);
      }
   }

   yyparse ();

   return (EXIT_SUCCESS);
}
