
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "man.h"

#define YYERROR_VERBOSE 1
#define YYDEBUG         1
#define yyerror         error

int text_type = 0;

static void output_text (const char *);
static void do_title (const char *);


%}

%union {
   int i;
   char *s;
}

%token tA
%token tB
%token tCENTER
%token tHR tHREF
%token tI
%token tLI
%token tOL
%token tP tPRE
%token tSTRONG
%token tTABLE tTD tTR
%token tU tUL

%token tBEGIN_HTML tBEGIN_HEAD tBEGIN_TITLE tBEGIN_BODY
%token tEND_HTML tEND_HEAD tEND_TITLE tEND_BODY

%token <s> tSTRING

%start page

%%

page
   : tBEGIN_HTML head_block body_block tEND_HTML   { putchar ('\n'); }
   ;

head_block
   : tBEGIN_HEAD head_contents tEND_HEAD
   ;

body_block
   : tBEGIN_BODY body_contents tEND_BODY
   ;

head_contents
   : title
   ;

title
   : tBEGIN_TITLE tSTRING tEND_TITLE    { do_title ($2); }
   ;

body_contents
   : body_item
   | body_contents body_item
   ;

body_item
   : tags
   | tSTRING               { output_text ($1); }
   ;
   
tags
   : tag
   | tags tag
   ;

tag
   : text_tag
   | tHR                   { puts ("\n-------------------------------------------------------------------------------"); }
   ;

text_tag
   : tB                    { text_type &= xBOLD; }
   | tCENTER               { text_type &= xCENTER; }
   | tI                    { text_type &= xITALIC; }
   | tU                    { text_type &= xUNDERLINE; }
   ;

%%

static void output_text (const char *s)
{
   if (text_type & xBOLD)
   {
   }

   if (text_type & xITALIC)
   {
   }

   if (text_type & xUNDERLINE)
   {
   }

   if (text_type & xCENTER)
   {
      int n = (80 - strlen (s)) / 2;
      while (--n)
         putchar (' ');
   }
   
   fputs (s, stdout);
}

static void do_title (const char *s)
{
   int i;
   
   i = 80 - strlen (s);

   while (--i)
      putchar (' ');   
   
   puts (s);
}
