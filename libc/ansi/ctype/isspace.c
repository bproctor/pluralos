
#include <ctype.h>

int (isspace)(int c)
{
   return (__ctype[c] & (_SP));
}
