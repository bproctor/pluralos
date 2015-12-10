
#include <stdlib.h>

lldiv_t (lldiv)(long long n, long long d)
{
   lldiv_t r;
   if (n > 0 && d < 0)
      n = -n,  d = -d;
   r.quot = n / d;
   r.rem = n % d;
   if (n < 0 && d > 0 && r.rem > 0)
      r.quot++, r.rem -= d;
   return (r);         
}
