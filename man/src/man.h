
#ifndef __MAN_H__
#define __MAN_H__

#include <stdlib.h>

#define xBOLD        0x0001
#define xITALIC      0x0002
#define xUNDERLINE   0x0004
#define xCENTER      0x0008

void error (const char *, ...);
void warning (const char *, ...);
void fatal (const char *, ...);
int yylex (void);
int yyparse (void);

static inline void *xmalloc (size_t n)
{
   void *ptr = malloc (n);
   if (ptr == NULL)
      fatal ("could not allocate memory");
   return (ptr);
}

#endif /* __MAN_H__ */
