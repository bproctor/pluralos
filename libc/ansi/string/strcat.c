
#include <string.h>

char *(strcat)(char *dest, const char *src)
{
   char *ptr = dest;
   while (*src != 0)
      *ptr++ = *src++;
   return (dest);
}
