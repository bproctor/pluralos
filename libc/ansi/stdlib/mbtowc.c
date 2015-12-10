
#include <stdlib.h>

int (mbtowc)(wchar_t *ws, const char *s, size_t n)
{
   int i = 0;
   if (s == 0)
      return (0);
   if (*s)
      i = 1;
   if (ws)
      *ws = *s;
   return (i);
}
