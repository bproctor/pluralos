
#include <ctype.h>

int (isgraph)(int c)
{
   return (__ctype[c] & (_DI|_LO|_PU|_UP));
}
