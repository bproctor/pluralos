
/*
 *  lex.c
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
 * $Id: lex.c,v 1.2 2003/01/02 23:31:21 fredlie Exp $
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "as.h"
#include "parse.h"

extern int lineno;
extern FILE *infile;
extern token_type *tokens[];

char string[256];

static char input_buffer[4096];
static char *input_ptr = input_buffer;
static int input_bufsize = 0;
static int last_char = 0;

/*
 * Return the next character from the input file.
 * Also fills the buffer if necessary.
 */

int get (void)
{
   int i;
   
   if (last_char)
   {
      i = last_char;
      last_char = 0;
      return (i);
   }
      
   if (input_ptr >= input_buffer + input_bufsize)
   {
      input_bufsize = fread (input_buffer, 1, 4096, infile);
      if (input_bufsize == 0)
         return (EOF);
      input_ptr = input_buffer;
   }
   return (*input_ptr++);   
}

/*
 * Puts a character back in the input buffer.
 * There is a place to put a spare character if the buffer has
 * just been filled and we do an unget().  Only one character can
 * pushed back.
 */

void unget (int c)
{
   if (input_ptr <= input_buffer)
      last_char = c;
   else
      last_char = 0, *--input_ptr = c;
}

int yylex (void)
{
   int c, c1;
   unsigned int i;
   char *ptr;
   token_type *t;

   i = 0;   
lex_top:
   c = get ();
   switch (c)
   {
      case EOF:
         return (0);
      case ' ':
      case '\a':
      case '\b':
      case '\f':
      case '\r':
      case '\t':
      case '\v':
         goto lex_top;
      case 'a': case 'b': case 'c': case 'd': case 'e':
      case 'f': case 'g': case 'h': case 'i': case 'j':
      case 'k': case 'l': case 'm': case 'n': case 'o':
      case 'p': case 'q': case 'r': case 's': case 't':
      case 'u': case 'v': case 'w': case 'x': case 'y':
      case 'z': case 'A': case 'B': case 'C': case 'D':
      case 'E': case 'F': case 'G': case 'H': case 'I':
      case 'J': case 'K': case 'L': case 'M': case 'N':
      case 'O': case 'P': case 'Q': case 'R': case 'S':
      case 'T': case 'U': case 'V': case 'W': case 'X':
      case 'Y': case 'Z':
         ptr = string;
         do {
            *ptr++ = c;
            c = get ();
         } while (isalpha (c) || c == '_');
         unget (c);
         *ptr = '\0';
         t = tokens[*string - 'a'];
         while (t)
         {
            if (!strcmp (t->name, string))
            {
               yylval.i = t->value;
               return (t->id);
            }
            ++t;
         }

      /*
       * Hexidecimal and Octal numbers start with 0, so we
       * seperate it from the rest of the digits.
       */
      case '0':
         if ((c = get ()) == 'x' || c == 'X')
         {
            yylval.i = 0;
            c = get ();
            while (isxdigit (c))
            {
               yylval.i <<= 4;
               if (c >= 'a' && c <= 'f')
                  yylval.i += c - 'a' + 10;
               else if (c >= 'A' && c <= 'F')
                  yylval.i += c - 'A' + 10;
               else
                  yylval.i += c - '0';
               c = get ();
            }
            unget (c);
            return (tNUMBER);
         }
         else if (c >= '0' && c <= '7')
         {
            yylval.i = 0;
            do {
               yylval.i <<= 3;
               yylval.i += c - '0';
               c = get ();
            } while (c >= '0' && c <= '7');
            unget (c);
            return (tNUMBER);
         }
      case '1': case '2': case '3': case '4': case '5':
      case '6': case '7': case '8': case '9':
         yylval.i = 0;
         do {
            yylval.i *= 10;
            yylval.i += c - '0';
            c = get ();
            if (c == '.')
            {
               error ("Floating point number not yet implemented");
               do
                  c = get ();
               while (isdigit (c));
            }
         } while (isdigit (c));
         unget (c);
         return (tNUMBER);
      case '!':
         if ((c = get ()) == '=')
            return (tNE);
         unget (c);
         return '!';
      case '%':
         if ((c = get ()) == '=')
            return (tMODE);
         unget (c);
         return '%';
      case '^':
         if ((c = get ()) == '=')
            return (tXORE);
         unget (c);
         return '^';
      case '&':
         if ((c = get ()) == '&')
            return (tDAND);
         else if (c == '=')
            return (tANDE);
         unget (c);
         return '&';
      case '*':
         if ((c = get ()) == '=')
            return (tMULE);
         unget (c);
         return '*';
      case '-':
         if ((c = get ()) == '-')
            return (tDSUB);
         else if (c == '=')
            return (tSUBE);
         unget (c);
         return '-';
      case '+':
         if ((c = get ()) == '+')
            return (tDADD);
         else if (c == '=')
            return (tADDE);
         unget (c);
         return '+';
      case '=':
         if ((c = get ()) == '=')
            return (tDEQ);
         unget (c);
         return '=';
      case '<':
         if ((c = get ()) == '<')
         {
            if ((c = get ()) == '=')
               return (tSHLE);
            unget (c);
            return (tLSHIFT);
         }
         else if (c == '=')
            return (tLE);
         unget (c);
         return '<';
      case '>':
         if ((c = get ()) == '>')
         {
            if ((c = get ()) == '=')
               return (tSHRE);
            unget (c);
            return (tRSHIFT);
         }
         else if (c == '=')
            return (tGE);
         unget (c);
         return '>';
      case '~':
         if ((c = get ()) == '=')
            return (tCOME);
         unget (c);
         return '~';
      case '|':
         if ((c = get ()) == '|')
            return (tDOR);
         else if (c == '=')
            return (tORE);
         unget (c);
         return '|';
      case '/':
         if ((c = get ()) == '=')
            return (tDIVE);
         unget (c);
         return '/';
      case '\\':
         c = get ();
         if (c == '\n')
            lineno++;
         else
            error ("stray `\\' in program");

      /*
       * Both strings and characters are interpreted here.
       */
      case '\'':
      case '\"':
         c1 = c;
         ptr = string;
         while (1)
         {
            c = get ();
            if (c == c1)
            {
               *ptr = '\0';
               if (*string == '\'')
               {
                  yylval.i = string[1];
                  return (tNUMBER);
               }
               else
               {
                  yylval.string = string;
                  return (tSTRING);
               }
            }
            else if (c == '\\')  /* Handle escape sequences */
            {
               c = get ();
               switch (c)
               {
                  case 'a': *ptr++ = '\a'; break;
                  case 'b': *ptr++ = '\b'; break;
                  case 'f': *ptr++ = '\f'; break;
                  case 'n': *ptr++ = '\n'; break;
                  case 'r': *ptr++ = '\r'; break;
                  case 't': *ptr++ = '\t'; break;
                  case 'v': *ptr++ = '\v'; break;
                  
                  /* These can't be simplified in the obvious manner
                     because of the default statement below */
                  case '\?': *ptr++ = '\?'; break;
                  case '\\': *ptr++ = '\\'; break;
                  case '\"': *ptr++ = '\"'; break;
                  case '\'': *ptr++ = '\''; break;
                  
                  case 'x':      /* Hexadecimal escape sequence */
                     i = 0;
                     c = get ();
                     while (isxdigit (c))
                     {
                        i <<= 4;
                        if (c >= 'a' && c <= 'f')
                           i += c - 'a' + 10;
                        else if (c >= 'A' && c <= 'F')
                           i += c - 'A' + 10;
                        else
                           i += c - '0';
                        c = get ();
                     }
                     if (i > 0xFF)
                        warning ("Hex escape sequence is out of range");
                     *ptr++ = i;
                     break;
                  case '0':         /* Octal escape sequence */
                     yylval.i = 0;
                     c = get ();
                     while (c >= '0' && c <= '9')
                     {
                        i <<= 3;
                        i += c - '0';
                        c = get ();
                     }
                     if (i > 0xFF)
                        warning ("Octal escape sequence is out of range");
                     *ptr++ = i;
                     break;
                  default:
                     *ptr++ = i;
                     warning ("Invalid escape sequence");
               }
            }
            else
               *ptr++ = c;
         }
      case '#':   /* Preprocessor directives */
         ptr = string;
         ++ptr;
         do {
            *ptr++ = c;
            c = get ();
         } while (isalpha (c) || c == '_');
         unget (c);
         *ptr = '\0';         
         if (!strcmp (ptr, "define"));
         else if (!strcmp (ptr, "ifdef"));
         else if (!strcmp (ptr, "ifndef"));
         else if (!strcmp (ptr, "else"));
         else if (!strcmp (ptr, "endif"));
         else if (!strcmp (ptr, "undef"));
         else
            error ("Invalid preprocessor directive");
         break;
      default:
         return (c);
   }
   return (c);
}
