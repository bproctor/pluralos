
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "man.h"
#include "parse.h"

typedef struct {
   char *name;
   int id;
} token_type;

static token_type *tokens[];

extern int lineno;
extern FILE *infile;

static char string[4096];
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
 * just been filled and we do an unget().  Only one character can be
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
   int c;
   char *ptr;
   token_type *t;
   
lex_top:
   c = get ();

   switch (c)
   {
      case EOF:
         return (0);
      case '\n':
         lineno++;
      case ' ':
      case '\a':
      case '\b':
      case '\f':
      case '\r':
      case '\t':
      case '\v':
         goto lex_top;
      case '<':
         if ((c = get ()) == '/')
         {
            ptr = string;
            c = get ();
            do {
               *ptr++ = c;
               c = get ();
            } while (isalpha (c));
            if (c != '>')
            {
               error ("invalid tag");
               unget (c);
            }
            *ptr = '\0';
            t = tokens[string[0] - 'a'];
            while (t)
            {
               if (!strcmp (t->name, string))
               {
                  switch (t->id)
                  {
                     case tBEGIN_BODY:    return (tEND_BODY);
                     case tBEGIN_HEAD:    return (tEND_HEAD);
                     case tBEGIN_HTML:    return (tEND_HTML);
                     case tBEGIN_TITLE:   return (tEND_TITLE);
                     default:
                        return (t->id);
                  }
               }
               ++t;
            }
         }
         else
         {
            ptr = string;
            do {
               *ptr++ = c;
               c = get ();
            } while (isalpha (c));
            if (c != '>')
            {
               error ("invalid tag");
               unget (c);
            }
            *ptr = '\0';
            t = tokens[string[0] - 'a'];
            while (t)
            {
               if (!strcmp (t->name, string))
                  return (t->id);
               ++t;
            }
                 
         }
      default:
         ptr = string;
         *ptr++ = c;
         while (ptr + 1 < &string[4095])
         {
            c = get ();
            if (c == '<')
            {
               unget (c);
               break;
            }
            else if (c == '\n')
               lineno++;
            *ptr++ = c;
         }
         *ptr = '\0';
         yylval.s = string;
         return (tSTRING);
   }
   return (c);
}

static token_type a_tokens[] =
{
   {"a" tA},
};

static token_type b_tokens[] =
{
   {"b", tB},
   {"body", tBEGIN_BODY},
};

static token_type c_tokens[] =
{
   {"center", tCENTER},
};

static token_type d_tokens[] =
{
};

static token_type e_tokens[] =
{
};

static token_type f_tokens[] =
{
};

static token_type g_tokens[] =
{
};

static token_type h_tokens[] =
{
   {"head", tBEGIN_HEAD},
   {"hr", tHR},
   {"href", tHREF},
   {"html", tBEGIN_HTML},
};

static token_type i_tokens[] =
{
   {"i", tI},
};

static token_type j_tokens[] =
{
};

static token_type k_tokens[] =
{
};

static token_type l_tokens[] =
{
   {"li", tLI},
};

static token_type m_tokens[] =
{
};

static token_type n_tokens[] =
{
};

static token_type o_tokens[] =
{
   {"ol", tOL},
};

static token_type p_tokens[] =
{
   {"p", tP},
   {"pre", tPRE},
};

static token_type q_tokens[] =
{
};

static token_type r_tokens[] =
{
};

static token_type s_tokens[] =
{
   {"strong", tSTRONG},
};

static token_type t_tokens[] =
{
   {"table", tTABLE},
   {"td", tTD},
   {"title", tBEGIN_TITLE},
   {"tr", tTR},
};

static token_type u_tokens[] =
{
   {"u", tU},
   {"ul", tUL},
};

static token_type v_tokens[] =
{
};

static token_type w_tokens[] =
{
};

static token_type x_tokens[] =
{
};

static token_type y_tokens[] =
{
};

static token_type z_tokens[] =
{
};

static token_type *tokens[] =
{
   a_tokens, b_tokens, c_tokens, d_tokens, e_tokens,
   f_tokens, g_tokens, h_tokens, i_tokens, j_tokens,
   k_tokens, l_tokens, m_tokens, n_tokens, o_tokens,
   p_tokens, q_tokens, r_tokens, s_tokens, t_tokens,
   u_tokens, v_tokens, w_tokens, x_tokens, y_tokens,
   z_tokens
};
