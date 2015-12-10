
#include <ctype.h>

int (iscntrl)(int c)
{
   return (__ctype[c] & (_BB));
}
