
#include <ctype.h>

int (isalnum)(int c)
{
   return (__ctype[c] & (_DI|_LO|_UP));
}
