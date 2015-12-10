
#include <string.h>

char *(strncat)(char *s1, const char *s2, size_t n)
{
   if (n)
   {
      char *t1 = s1;
      const char *t2 = s2;
      
      while (*t1)
         ++t1;
      do {
         if ((*t1 = *t2++) == 0)
            break;
         ++t1;
      } while (--n);
      *t1 = 0;
   }
   return (s1);
}
