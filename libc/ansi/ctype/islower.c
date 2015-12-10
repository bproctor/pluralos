
#include <ctype.h>

int (islower)(int c)
{
   return (__ctype[c] & (_LO));
}
