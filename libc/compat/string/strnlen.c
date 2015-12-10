
#include <string.h>

size_t (strnlen) (const char *s, size_t count)
{
   const char *t = s;
   
   while (*t && count--) 
      ++t;
      
   return (s-t);
}
