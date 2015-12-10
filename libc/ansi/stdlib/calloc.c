
#include <stdlib.h>
#include <string.h>

void *(calloc)(size_t size, size_t nelem)
{
   void *m = malloc (size * nelem);
   if (m)
      memset (m, 0, size * nelem);
   return (m);
}
