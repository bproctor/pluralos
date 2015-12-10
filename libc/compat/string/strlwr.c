
#include <string.h>
#include <ctype.h>

char *(strlwr)(char *s)
{
   char *p = s;
   while(*p)
   {
      *p = tolower(*p);
      ++p;
   }
   return (s);
}