
%{

/*
 *  expr -- evaluate arguments as an expression
 *  Copyright (c) 2002-2003 Brad Proctor
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
 * $Id: expr.y,v 1.8 2003/02/16 15:26:35 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "utils.h"

#define YYERROR_VERBOSE    1
#define YYDEBUG            0
#define yyerror            error

static int yylex (void);
static long long power (long long, long long);

%}

%union {
   long long i;
   long double f;
}

%left '<' '>' tGE tLE tNE '='
%left '&'
%left '|'
%left '^'
%left '+' '-'
%left '*' '/' '%'
%left tSHL tSHR
%left tPOW
%right UNARY

%token <i> tNUMBER
%token <f> tFLOAT

%type <i> expr
%type <f> exprf

%start line

%%
/*************************************************************************/

line
   : expr                  { printf ("%lld\n", $1); }
   | exprf                 { printf ("%Lg\n", $1); }
   ;

expr
   : tNUMBER               { $$ = $1;        }
   | expr '+' expr         { $$ = $1 + $3;   }
   | expr '-' expr         { $$ = $1 - $3;   }
   | expr '*' expr         { $$ = $1 * $3;   }
   | expr '/' expr         { $$ = $1 / $3;   }
   | expr '%' expr         { $$ = $1 % $3;   }
   | expr '&' expr         { $$ = $1 & $3;   }
   | expr '|' expr         { $$ = $1 | $3;   }
   | expr '^' expr         { $$ = $1 ^ $3;   }
   | expr '<' expr         { $$ = $1 < $3;   }
   | expr '>' expr         { $$ = $1 > $3;   }
   | expr '=' expr         { $$ = $1 == $3;  }
   | expr tGE expr         { $$ = $1 >= $3;  }
   | expr tLE expr         { $$ = $1 <= $3;  }
   | expr tNE expr         { $$ = $1 != $3;  }
   | expr tSHL expr        { $$ = $1 << $3;  }
   | expr tSHR expr        { $$ = $1 >> $3;  }
   | expr tPOW expr        { $$ = power ($1, $3); }
   | %prec UNARY '-' expr  { $$ = -$2;       }
   | %prec UNARY '+' expr  { $$ = $2;        }
   | %prec UNARY '~' expr  { $$ = ~$2;       }
   | %prec UNARY '!' expr  { $$ = !$2;       }
   | '(' expr ')'          { $$ = $2;        }
   ;

exprf
   : tFLOAT                  { $$ = $1;        }
   | exprf '+' exprf         { $$ = $1 + $3;   }
   | exprf '-' exprf         { $$ = $1 - $3;   }
   | exprf '*' exprf         { $$ = $1 * $3;   }
   | exprf '/' exprf         { $$ = $1 / $3;   }
   | exprf '<' exprf         { $$ = $1 < $3;   }
   | exprf '>' exprf         { $$ = $1 > $3;   }
   | exprf '=' exprf         { $$ = $1 == $3;  }
   | exprf tGE exprf         { $$ = $1 >= $3;  }
   | exprf tLE exprf         { $$ = $1 <= $3;  }
   | exprf tNE exprf         { $$ = $1 != $3;  }
   | %prec UNARY '-' exprf  { $$ = -$2;       }
   | %prec UNARY '+' exprf  { $$ = $2;        }
   | %prec UNARY '!' exprf  { $$ = !$2;       }
   | '(' exprf ')'          { $$ = $2;        }
   ;


%%
/*************************************************************************/

static char flag_float = 0;
static int argc_1, arg_count = 1;
static char **argv_1;

static const char help_text[] =
{
   "Usage: expr long_option\n"
   "       expr [-f] operand\n"
   "Evalute arguments as an expression.\n"
   "\n"
   "  -f         Use floating point numbers\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static long long power (long long x, long long y)
{
   while (y--)
      x *= x;
   return (x);
}

static int yylex (void)
{
   char *ptr;
   
   if (arg_count >= argc_1)
      return (0);
      
   ptr = argv_1[arg_count++];

   switch (*ptr)
   {
      case '0': case '1': case '2': case '3':
      case '4': case '5': case '6': case '7':
      case '8': case '9': case '.':
         if (flag_float)
         {
            yylval.f = getnum_ld (ptr);
            return (tFLOAT);
         }
         else
         {
            yylval.i = getnum_ll (ptr);
            return (tNUMBER);
         }
      case '<':
         if (*(ptr+1) == '=')
            return (tLE);
         else if (*(ptr+1) == '<')
            return (tSHL);
         return '<';
      case '>':
         if (*(ptr+1) == '=')
            return (tGE);
         else if (*(ptr+1) == '>')
            return (tSHR);
         return '>';
      case '!':
         if (*(ptr+1) == '=')
            return (tNE);
         return '=';
      case '*':
         if (*(ptr+1) == '*')
            return (tPOW);
         return '*';
   }
   return (*ptr);
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   progname = argv[0];

   if (argc == 1)
      error ("to few arguments\nTry `expr --help'");
   else if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("expr: version "VERSION);
         return (EXIT_SUCCESS);
      }
   }

   if (!strcmp (argv[1], "-f"))
      flag_float = 1, arg_count++;

#if YYDEBUG == 1
   yydebug = 1;
#endif

   argc_1 = argc;
   argv_1 = argv;
   yyparse ();
   return (EXIT_SUCCESS);
}
