
#include <string.h>

void *(memcpy)(void *dest, const void *src, size_t count)
{
   char *d = (char *)dest, *s = (char *)src;   
   while (count--)
      *d++ = *s++;
   return (dest);
}
