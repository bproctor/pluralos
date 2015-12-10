
#include <string.h>

void *(memchr)(const void *s, int c, size_t n)
{
   if (n)
   {
      const char *p = s;
      char c1 = c;
      do {
         if (*p == c1)
            return (p);
         p++;
      } while (--n != 0);
   }
   return (0);
}
