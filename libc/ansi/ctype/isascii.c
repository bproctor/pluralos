
#include <ctype.h>

int (isascii)(int c)
{
   return ((c & ~0x7F) == 0);
}
