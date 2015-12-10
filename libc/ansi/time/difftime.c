
#include <time.h>

double (difftime)(time_t t0, time_t t1)
{
   return ((double)t0 - (double)t1);
}
