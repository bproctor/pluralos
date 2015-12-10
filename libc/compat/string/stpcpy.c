
#include <string.h>

char *(stpcpy)(char *s1, const char *s2)
{
   if(!s1 || !s2)
      return (NULL);
   
   while((*s1++ = *s2++) != 0);

   return (--s1);
}
