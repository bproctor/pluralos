
#include <time.h>

time_t (time)(time_t *t)
{
   struct timeval t1;
   if (gettimeofday (&t1, 0) < 0)
      return (-1);
   if (t)
      *t = t1.tv_sec;
   return (t1.tv_sec);
}

