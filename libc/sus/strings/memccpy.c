
#include <string.h>

void *(memccpy)(void *s1, const void *s2, int c, size_t n)
{
   c &= 0xFF;
   if(n)
   {
      unsigned char *p1 = s1;
      const unsigned char *p2 = s2;
      do {
         if((*p1++ = *p2++) == c)
            return (p1);
      } while(--n);
   }
   return (0);
}
