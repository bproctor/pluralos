
%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cc.h"

#define YYDEBUG         1
#define YYERROR_VERBOSE 1

#define yyerror	      error

int yylex (void);

%}

%union
{
   char *string;
   unsigned long i;
   Symbol *sym;
}

%token <sym> tIDENTIFIER
%token <string> tSTRING
%token <i> tNUMBER

%token tAUTO
%token tBOOL tBREAK
%token tCASE tCHAR tCOMPLEX tCONST tCONTINUE
%token tDEFAULT tDO tDOUBLE
%token tELSE tENUM tEXTERN
%token tFALSE tFLOAT tFOR tFUTURE
%token tGOTO
%token tIF tIMAGINARY tINT tINLINE
%token tLONG
%token tREGISTER tRETURN tRESTRICT
%token tSHORT tSIGNED tSIZEOF tSTATIC tSTRUCT tSWITCH
%token tTRUE tTYPEDEF
%token tUNION tUNSIGNED
%token tVOID tVOLATILE
%token tWHILE

%right '=' tADDE tANDE tCOME tDIVE tMODE tMULE tORE tROLE tRORE tSHLE tSHRE tSUBE tXORE
%left tDEQ tNE
%left tDAND tDOR
%left '&'
%left '|'
%left '^'
%right tDSUB tDADD
%left '<' '>' tLE tGE
%left '+' '-'
%left '*' '/' '%'
%left tSHR tSHL tROL tROR
%right UNARY
%left '('

%type <i> const

%start program

%%

program
   : extdef
   | funcdef
   ;

extdef
   : enum
   ;
   
funcdef
   : typename tIDENTIFIER '(' ')' block
   ;   

block
   : statements
   | '{' statements '}'
   ;

statements
   : statement ';'
   | statements statement
   ;

statement
   : /* empty */
   | tFOR '(' maybe_expr ';' maybe_expr ';' maybe_expr ')' block
   | tWHILE '(' expr ')' block
   | tIF '(' expr ')' block maybe_else
   | tDO block tWHILE '(' expr ')' ';'
   | tSWITCH '(' expr ')' statement
   | tCASE const ':' statement
   | tDEFAULT ':' statement
   | tRETURN maybe_expr ';'
   | tGOTO tIDENTIFIER ';'
   | tBREAK ';'
   ;

maybe_else
   : /* empty */
   | tELSE block
   ;

maybe_expr
   : /* empty */
   | expr
   ;

enum
   : tENUM '{' enum_list '}' ';'
   | tENUM tIDENTIFIER '{' enum_list '}' ';'
   ;

enum_list
   : enumerator
   | enum_list ',' enumerator
   ;

enumerator
   : tIDENTIFIER
   | tIDENTIFIER '=' const
   ;

typename
   : basic_type_name
   | tIDENTIFIER
   ;

basic_type_name
   : tCHAR
   | tSHORT
   | tINT
   | tLONG
   | tFLOAT
   | tDOUBLE
   | tUNSIGNED
   | tSIGNED
   | tVOID
   | tBOOL
   ;

const_or_vol
   : tCONST
   | tVOLATILE
   ;

   
expr
   : const
   | expr '+' expr
   | expr '-' expr
   | expr '*' expr
   | expr '/' expr
   | expr '%' expr
   | expr '&' expr
   | expr '|' expr
   | expr '^' expr
   | expr '<' expr
   | expr '>' expr
   | expr tLE expr
   | expr tGE expr
   | expr tNE expr
   | expr tSHL expr
   | expr tSHR expr
   | expr tROL expr
   | expr tROR expr
   | expr tDEQ expr
   | expr '=' expr
   | expr tADDE expr
   | expr tANDE expr
   | expr tCOME expr
   | expr tDIVE expr
   | expr tMODE expr
   | expr tMULE expr
   | expr tORE expr
   | expr tROLE expr
   | expr tRORE expr
   | expr tSHLE expr
   | expr tSHRE expr
   | expr tSUBE expr
   | expr tXORE expr
   | '(' expr ')'
   | %prec UNARY '-' expr
   | %prec UNARY '+' expr
   | %prec UNARY '~' expr
   | %prec UNARY '!' expr
   | tDADD expr
   | tDSUB expr
   | expr tDADD
   | expr tDSUB
   ;

const
   : tTRUE                       { $$ = 1;         }
   | tFALSE                      { $$ = 0;         }
   | tNUMBER                     { $$ = $1;        }
   | const '+' const             { $$ = $1 + $3;   }
   | const '-' const             { $$ = $1 - $3;   }
   | const '/' const             { $$ = $1 / $3;   }
   | const '*' const             { $$ = $1 * $3;   }
   | const '%' const             { $$ = $1 % $3;   }
   | const '&' const             { $$ = $1 & $3;   }
   | const '|' const             { $$ = $1 | $3;   }
   | const '^' const             { $$ = $1 ^ $3;   }
   | const tSHL const            { $$ = $1 << $3;  }
   | const tSHR const            { $$ = $1 >> $3;  }
   | const tDOR const            { $$ = $1 || $3;  }
   | const tDAND const           { $$ = $1 && $3;  }
   | %prec UNARY '-' const       { $$ = -$2;       }
   | %prec UNARY '+' const       { $$ = $2;        }
   | %prec UNARY '~' const       { $$ = ~$2;       }
   | %prec UNARY '(' const ')'   { $$ = $2;        }
   ;

string
   : tSTRING
   | string tSTRING
   ;

%%
   

Symbol *symbol_head;

static Symbol *__insert_symbol (Symbol *sym)
{
   int c;
   Symbol *ptr, *prev;
   if (symbol_head == 0)
   {
      symbol_head = sym;
      return (sym);
   }
   ptr = symbol_head;
   while (ptr)
   {
      c = strcmp (sym->name, ptr->name);
      prev = ptr;
      if (c == 0)
      {
         error ("`%s' already declared", sym->name);
         return (NULL);
      }
      ptr = c < 0 ? ptr->left : ptr->right;
   }
   if (c < 0)
      prev->left = sym;
   else
      prev->right = sym;
   return (sym);
}

Symbol *insert_symbol (char *name, unsigned long type)
{
   Symbol *sym = (Symbol *)malloc (sizeof (Symbol));
   sym->name = (char *)malloc (strlen (name));
   strcpy (sym->name, name);
   sym->type = type;
   return (__insert_symbol (sym));
}
