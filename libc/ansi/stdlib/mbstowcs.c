
#include <stdlib.h>

size_t (mbstowcs)(wchar_t *ws, const char *s, size_t n)
{
   int i;
   for (i = 0; s[i] && (i < n-1); ++i)
      ws[i] = s[i];
   ws[i] = 0;
   return (i);
}
