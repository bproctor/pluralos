
#include <ctype.h>

int (isxdigit)(int c)
{
   return (__ctype[c] & (_DI|_XD));
}
