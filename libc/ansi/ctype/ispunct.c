
#include <ctype.h>

int (ispunct)(int c)
{
   return (__ctype[c] & (_PU));
}
