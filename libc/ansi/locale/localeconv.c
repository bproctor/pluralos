
#include <locale.h>
#include <limits.h>

static struct lconv __lconv =
{
   "",
   ".",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   "",
   CHAR_MAX,
   CHAR_MAX,
   CHAR_MAX,
   CHAR_MAX,
   CHAR_MAX,
   CHAR_MAX,
   CHAR_MAX,
   CHAR_MAX
};

struct lconv *(localeconv)(void)
{
   return (&__lconv);
}
