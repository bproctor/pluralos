
#include <stdlib.h>

#define  STEP  tmp = *((const char *)from)++, *((char *)to)++ = tmp

void swab(const void *from, void *to, int n)
{
   unsigned long tmp;
   
   n >>= 1, ++n;
   while(--n & 7)
      STEP;
   n >>= 3;
   while(--n >= 0)
   {
      STEP; STEP; STEP; STEP;
      STEP; STEP; STEP; STEP;
   }
}
