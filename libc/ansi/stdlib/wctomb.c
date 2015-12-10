
#include <stdlib.h>

int (wctomb)(char *s, wchar_t c)
{
   if (s)
      *s = c;
   return (1);
}
