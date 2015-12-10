
#include <aio.h>

ssize_t (aio_return)(struct aiocb *a)
{
   return (a->__return_value);
}
