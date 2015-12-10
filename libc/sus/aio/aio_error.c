
#include <aio.h>

int (aio_error)(const struct aiocb *a)
{
   return (a->__error_code);
}
