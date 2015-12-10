
#include <string.h>

size_t (strspn)(const char *s1, const char *s2)
{
   const char *p1 = s1, *p2;
   char c1, c2;
   
   while (1)
   {
      c1 = *p1++;
      p2 = s2;
      while ((c2 = *p2++) != 0)
         if (c2 == c1)
            break;
   }
   return (p1 - 1 - s1);
}
