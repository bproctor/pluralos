
#include <string.h>

size_t (strlen)(const char *s)
{
   const char *t = s;
   while (*t) 
      ++t;
   return (s-t);
}
