
#include <stdlib.h>

int (mblen)(const char *s, size_t n)
{
   if (s)
      return ((*s == '\0' || n == 0) ? 0 : 1);
   return (1);
}
