
#include <string.h>
#include <ctype.h>

char *(strupr)(char *s)
{
   char *p = s;
   while(*p)
   {
      *p = toupper(*p);
      ++p;
   }
   return (s);
}