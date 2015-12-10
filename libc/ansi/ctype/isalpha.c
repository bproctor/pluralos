
#include <ctype.h>

int (isalpha)(int c)
{
   return (__ctype[c] & (_LO|_UP));
}
