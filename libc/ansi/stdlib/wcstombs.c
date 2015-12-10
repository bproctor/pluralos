
#include <stdlib.h>

size_t (wcstombs)(char *s, const wchar_t *ws, size_t n)
{
   int i;
   for (i = 0; ws[i] && (i < n-1); ++i)
      s[i] = ws[i];
   s[i] = '\0';
   return (i);
}
