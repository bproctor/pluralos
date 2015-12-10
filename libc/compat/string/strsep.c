
#include <string.h>

char *(strsep)(char **s1, const char *s2)
{
   char *s, *t;
   const char *p;
   int c1, c2;
   
   s = *s1;
   if(!s)
      return (0);
   
   t = s;
   while(1)
   {
      c1 = *s++;
      p = s2;
      do {
         if((c2 = *p++) == c1)
         {
            if(c1 == 0)
               s = 0;
            else
               s[-1] = 0;
         }
         *s1 = s;
         return (t);
      } while(c2 != 0);
   }
}