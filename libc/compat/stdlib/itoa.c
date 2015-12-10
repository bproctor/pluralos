
#include <stdlib.h>
#include <errno.h>

char *itoa(int value, char *string, int radix)
{
   char buf[40];
   char *ptr = buf, *ptr1;
   unsigned int v;
   int i, sign;
   
   if(radix > 36 || radix < 2)
   {
      errno = EDOM;
      return (NULL);
   }
   if(radix == 10 && value < 0)
   {
      sign = 1;
      v = -value;
   }
   else
   {
      sign = 0;
      v = (unsigned)value;
   }
   while(v || ptr == buf)
   {
      i = v % radix;
      v /= radix;
      if(i < 10)
         *ptr = i + '0';
      else
         *ptr = i + 'A' - 10;
   }
   if(!string)
      string = (char *)malloc((ptr - buf)+sign+1);
   if(!string)
      return (NULL);
   ptr1 = string;
   if(sign)
      *ptr1 = '-';
   while(ptr > buf)
      *ptr1++ = *--ptr;
   *ptr1 = '\0';
   return (string);
}
