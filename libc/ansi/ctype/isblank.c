
#include <ctype.h>

int (isblank)(int c)
{
   return (__ctype[c] & (_SP));
}
