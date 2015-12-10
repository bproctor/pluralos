
#include <string.h>

size_t (strcspn)(const char *s1, const char *s2)
{
   const char *p1, *p2;
   char c1, c2;
   
   p1 = s1;
   while (1)
   {
      c1 = *p1++;
      p2 = s2;
      do {
         if ((c2 = *p2++) == c1)
            return (p1 - 1 - s1);
      } while (c2);
   }
}
