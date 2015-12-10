
#include <string.h>
#include <ctype.h>

int (memicmp)(const void *s1, const void *s2, size_t n)
{
   const unsigned char *p1 = s1, *p2 = s2;

   while(n > 0)
   {
      if(tolower(*p1) != tolower(*p2))
         return ((tolower(*p1) < tolower(*p2)) ? -1 : 1);
      ++p1, ++p2, --n;
   }
   return (0);
}