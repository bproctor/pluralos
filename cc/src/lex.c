
/*
 *  lex.c
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
 * $Id: lex.c,v 1.2 2002/12/22 18:24:03 fredlie Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cc.h"
#include "parse.h"

#define pDEFINE   1
#define pELSE     2
#define pENDIF    3
#define pIF       4
#define pIFDEF    5
#define pIFNDEF   6
#define pUNDEF    7
#define NUM_DIR   7

extern flag_type flags;

typedef struct token_type
{
   char *name;
   int id;
} token_type;

static struct token_type pre_tokens[NUM_DIR+1];
static struct token_type *tokens[26];
static int comment_line;

extern int lineno;
extern FILE *infile;

char string[4096];

static char input_buffer[65536];
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

/*
 * Skip a C comment, this function is recursive to allow nested comments.
 * If 'flag.ansi89' or 'flag.ansi99' is set, we play dump and pretend we
 * don't know about them, which might need to be rethought.
 */

static void skip_c_comment (void)
{
   int c;

   while (1)
   {
      c = get ();
      switch (c)
      {
         case '/':
            if (flags.ansi89 == 0 && flags.ansi99 == 0)
               if ((c = get ()) == '*')
               {
                  if (flags.warn_ansi89 || flags.warn_ansi99)
                     warning ("ANSI C does not allow nested comments");
                  skip_c_comment ();
               }
            break;
         case '*':
            if ((c = get ()) == '/')
               return;
         case EOF:
            fatal_error ("Unterminated comment from line: %d", comment_line);
      }
   }
}

/*
 * This is the lexical analyzer, the parser calls this function ever
 * time it needs another token.
 */

int yylex (void)
{
   int i, c, c1;
   token_type *t;
   char *ptr;
   
lex_top:
   i = 0;
   c = get ();
   switch (c)
   {
      case EOF:
         return 0;      /* End of file, the parse recognizes 0 as EOF */
      case '\n':
         lineno++;      /* Count the line numbers */
      case ' ':         /* Skip white space */
      case '\a':
      case '\b':
      case '\f':
      case '\r':
      case '\t':
      case '\v':
         goto lex_top;

      /* 
       * All reserved words start with one of the letters below.
       * We get the word and then check the reserved word table
       * for a match, if none is found jump down to the symbol
       * table lookup in the next section.
       */
      case 'a': case 'b': case 'c': case 'd': case 'e':
      case 'f': case 'g': case 'i': case 'l': case 'r':
      case 's': case 't': case 'u': case 'v': case 'w':
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
               return (t->id);
            ++t;
         }
         goto label;
         
      case '_':
         ptr = string;
         do {
            *ptr++ = c;
            c = get ();
         } while (isalnum (c) || c == '_');
         unget (c);
         *ptr = '\0';

         /* 
          * If we are compiling ANSI89 code, then
          * skip these ANSI99 keywords and treat it
          * as a label.  May need to consider giving
          * a warning if any of the ANSI99 keywords
          * match...
          */
         
         if (flags.ansi89 == 1)
            goto label;
            
         if (!strcmp (string, "_Bool"))
            return (tBOOL);
         else if (!strcmp (string, "_Imaginary"))
            return (tIMAGINARY);
         else if (!strcmp (string, "_Complex"))
            return (tCOMPLEX);
         else
            goto label;
         
      /*
       * No reserved word starts with these letter so we know it
       * is an identifier right away.  We get the word and then
       * check the symbol tables.
       */
      case 'h': case 'j': case 'k': case 'm': case 'n':
      case 'o': case 'p': case 'q': case 'x': case 'y':
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
         } while (isalnum (c) || c == '_');
         unget (c);
         *ptr = '\0';
      label:
         yylval.sym = insert_symbol (string, 0);
         return (tIDENTIFIER);
         
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
            do {
               yylval.i <<= 3;
               yylval.i += c - '0';
               c = get ();
            } while (c >= '0' && c <= '7');
            unget (c);
            return (tNUMBER);
         }
         unget (c);
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
         break;
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
            else if (c == '<' && flags.ansi89 == 0 && flags.ansi99 == 0)
            {
               if ((c = get ()) == '=')
               {
                  if (flags.warn_ansi89 || flags.warn_ansi99)
                     warning ("`<<<=' is not an ANSI operator");
                  return (tROLE);
               }
               else
               {
                  if (flags.warn_ansi89 || flags.warn_ansi99)
                     warning ("`<<<' is not an ANSI operator");
                  return (tROL);
               }
               unget (c);
            }
            unget (c);
            return (tSHL);
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
            else if (c == '>' && flags.ansi89 == 0 && flags.ansi99 == 0)
            {
               if ((c = get ()) == '=')
               {
                  if (flags.warn_ansi89 || flags.warn_ansi99)
                     warning ("`>>>=' is not an ANSI operator");
                  return (tRORE);
               }
               else
               {
                  if (flags.warn_ansi89 || flags.warn_ansi99)
                     warning ("`>>>' is not an ANSI operator");
                  return (tROR);
               }
               unget (c);
            }
            unget (c);
            return (tSHR);
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
         if ((c = get ()) == '*')
         {
            comment_line = lineno;
            skip_c_comment ();
            goto lex_top;
         }
         else if (c == '/')
         {
            if (flags.warn_ansi89)
               warning ("ANSI C does not allow C++ style comments");
            while (c != '\n' && c != '\0')
               c = get ();
            goto lex_top;
         }
         else if (c == '=')
            return (tDIVE);
         unget (c);
         return '/';

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
      case '\\':
         c = get ();
         if (c == '\n')
            lineno++;
         else
            error ("stray `\\' in program");
      case '#':
         c = get ();
         while (isspace (c) && c != '\n');
         if (c == '\n')
         {
            lineno++;
            goto lex_top;
         }
         else if (c == '#')
         {
         }
         else
         {
            ptr = string;
            do {
               *ptr++ = c;
               c = get ();
            } while (isalpha (c) || c == '_');
            unget (c);
            *ptr = '\0';
            for (i = 0; i < NUM_DIR; ++i)
            {
               c1 = strcmp (string, pre_tokens[i].name);
               if (c1 == 0)
               {
                  switch (i)
                  {
                     case pDEFINE:
                     case pELSE:
                     case pENDIF:
                     case pIF:
                     case pIFDEF:
                     case pIFNDEF:
                     case pUNDEF:
                        break;
                  }
               }
            }
         }
      case '?':
         if ((c = get ()) == '?')
         {
            if ((c = get ()) == '?')
            {
               c = get ();
               switch (c)
               {
                  case '=':   c1 = '#';   break;
                  case '(':   c1 = '[';   break;
                  case '/':   c1 = '\\';  break;
                  case ')':   c1 = ']';   break;
                  case '\'':  c1 = '^';   break;
                  case '<':   c1 = '{';   break;
                  case '!':   c1 = '|';   break;
                  case '>':   c1 = '}';   break;
                  case '-':   c1 = '~';   break;
                  default:
                     error ("Invalid trigraph sequence");
                     goto lex_top;
               }
               unget (c1);
               goto lex_top;
            }
            else
               error ("Invalid trigraph sequence");
         }
         else
            error ("Invalid trigraph sequence");
         break;
   }
   return (c);
}

static token_type pre_tokens[NUM_DIR+1] =
{
   {"define", pDEFINE},
   {"else",   pELSE},
   {"endif",  pENDIF},
   {"if",     pIF},
   {"ifdef",  pIFDEF},
   {"ifndef", pIFNDEF},
   {"undef",  pUNDEF},
   {0, 0}
};

static token_type a_tokens[] =
{
   {"asm",  tFUTURE},      /* Future reserved word */
   {"auto", tAUTO},
   {0, 0}
};

static token_type b_tokens[] =
{
   {"bool",  tBOOL},
   {"break", tBREAK},
   {0, 0}
};

static token_type c_tokens[] =
{
   {"case", tCASE},
   {"char", tCHAR},
   {"const", tCONST},
   {"continue", tCONTINUE},
   {0, 0}
};

static token_type d_tokens[] =
{
   {"default", tDEFAULT},
   {"do", tDO},
   {"double", tDOUBLE},
   {0, 0}
};

static token_type e_tokens[] =
{
   {"else", tELSE},
   {"enum", tENUM},
   {"extern", tEXTERN},
   {0, 0}
};

static token_type f_tokens[] =
{
   {"false", tFALSE},
   {"float", tFLOAT},
   {"for", tFOR},
   {0, 0}
};

static token_type g_tokens[] =
{
   {"goto", tGOTO},
   {0, 0}
};

static token_type i_tokens[] =
{
   {"if", tIF},
   {"inline", tINLINE},
   {"int", tINT},
   {"interrupt", tFUTURE},    /* Future reserved word */
   {0, 0}
};

static token_type l_tokens[] =
{
   {"long", tLONG},
   {0, 0}
};

static token_type r_tokens[] =
{
   {"register", tREGISTER},
   {"return", tRETURN},
   {0, 0}
};

static token_type s_tokens[] =
{
   {"short", tSHORT},
   {"signed", tSIGNED},
   {"sizeof", tSIZEOF},
   {"static", tSTATIC},
   {"struct", tSTRUCT},
   {"switch", tSWITCH},
   {0, 0}
};

static token_type t_tokens[] =
{
   {"true",    tTRUE},
   {"typedef", tTYPEDEF},
   {0, 0}
};

static token_type u_tokens[] =
{
   {"union", tUNION},
   {"unsigned", tUNSIGNED},
   {0, 0}
};

static token_type v_tokens[] =
{
   {"void", tVOID},
   {"volatile", tVOLATILE},
   {0, 0}
};

static token_type w_tokens[] =
{
   {"while", tWHILE},
   {0, 0}
};

static token_type *tokens[26] =
{
   a_tokens, b_tokens, c_tokens, d_tokens, e_tokens,
   f_tokens, g_tokens, 0,        i_tokens, 0,
   0,        l_tokens, 0,        0,        0,
   0,        0,        r_tokens, s_tokens, t_tokens,
   u_tokens, v_tokens, w_tokens, 0,        0,
   0,
};
