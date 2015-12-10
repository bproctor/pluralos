
#include <string.h>

char *(strncpy)(char *s1, const char *s2, size_t n)
{
   if (n)
   {
      char *p1 = s1;
      const char *p2 = s2;
      do {
         if ((*p1++ = *p2++) == 0)
         {
            while (--n)
               *p1++ = 0;
            break;
         }
      } while (--n);
   }
   return (s1);
}
