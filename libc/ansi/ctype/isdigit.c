
#include <ctype.h>

int (isdigit)(int c)
{
   return (__ctype[c] & (_DI));
}
