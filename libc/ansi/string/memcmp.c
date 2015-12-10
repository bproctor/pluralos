
#include <string.h>

int (memcmp)(const void *s1, const void *s2, size_t n)
{
   if (n)
   {
      const unsigned char *t1 = s1, *t2 = s2;
      do {
         if (*t1++ != *t2++)
            return (*--t1 - *--t2);
      } while (--n);
   }
   return (0);
}
