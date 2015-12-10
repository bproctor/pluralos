
#include <ctype.h>

int (isupper)(int c)
{
   return (__ctype[c] & (_UP));
}
