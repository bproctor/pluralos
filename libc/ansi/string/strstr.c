
#include <string.h>

char *(strstr)(const char *s1, const char *s2)
{
   char c1, c2;
   size_t n;
   
   c1 = *s2++;
   if (c1 != 0)
   {
      n = strlen (s2);
      do {
         do {
            c2 = *s1++;
            if (c2 == 0)
               return (0);
         } while (c2 != c1);
      } while (strncmp (s1, s2, n) != 0);
      --s1;
   }
   return (*(unsigned char *)s1);
}
