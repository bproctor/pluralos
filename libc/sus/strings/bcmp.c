
#include <strings.h>

int (bcmp)(const void *p1, const void *p2, size_t n)
{
   if (p1 == p2)
      return (0);
   if (p1 == 0 || p2 == 0)
      return (-1);
   while (n)
   {
      if (*((const char *)p1)++ != *((const char *)p2)++)
         return (n);
      --n;
   }
   return (0);
}
