
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TM_YEAR_BASE    1900

static size_t gsize;
static char *pt;

static const char *_a[] =
   {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

static const char *_A[] =
   {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", 
    "Friday", "Saturday"};

static const char *_b[] =
   {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep",
    "Oct", "Nov", "Dec"};

static const char *_B[] =
   {"January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"};

static int insert (const char *str, int upcase)
{
   while (1)
   {
      if (!gsize)
         return (0);
      if (!(*pt = *str++))
         return (1);
      if (upcase)
         *pt = toupper (*pt);
      ++pt, --gsize;
   }
}

static int _conv (int n, int d, char pad)
{
   static char buf[10];
   char *p = buf + sizeof (buf) - 2;
   
   do {
      *p-- = n % 10 + '0';
      n /= 10;
      --d;
   } while (n > 0 && p < buf);
   
   if (pad)
      while (p > buf && d-- > 0)
         *p-- = pad;
   return (insert (++p, 0));
}

static size_t _format (const char *fmt, const struct tm *t, int upcase)
{
   while (*fmt)
   {
      if (*fmt == '%')
      {
         int pad = 0, space = ' ';
         if (fmt[1] == '_')
            pad = space = ' ', fmt++;
         if (fmt[1] == '-')
            pad = space = '-', fmt++;
         if (fmt[1] == '0')
            pad = space = '0', fmt++;
         if (fmt[1] == '^')
            upcase = 1, fmt++;
         
         switch (*++fmt)
         {
            case '\0':
               --fmt; break;
            case 'A':
               if (t->tm_wday < 0 || t->tm_wday > 6)
                  return (0);
               if (insert (_A[t->tm_wday], upcase))
                  return (0);
               continue;
            case 'a':
               if (t->tm_wday < 0 || t->tm_wday > 6)
                  return (0);
               if (insert (_a[t->tm_wday], upcase))
                  return (0);
               continue;
            case 'B':
               if (t->tm_mon < 0 || t->tm_mon > 11)
                  return (0);
               if (insert (_B[t->tm_mon], upcase))
                  return (0);
               continue;
            case 'b':
            case 'h':
               if (t->tm_mon < 0 || t->tm_mon > 11)
                  return (0);
               if (insert (_b[t->tm_mon], upcase))
                  return (0);
               continue;
            case 'C':
               if (!_conv ((t->tm_year+TM_YEAR_BASE)/100, 2, pad))
                  return (0);
               continue;
            case 'c':
               if (!_format ("%a %b %e %H:%M:%S %Y", t, upcase))
                  return (0);
               continue;
            case 'e':
               if (!_conv (t->tm_mday, 2, ' '))
                  return (0);
               continue;
            case 'D':
               if (!_format ("%m/%d/%y", t, upcase))
                  return (0);
               continue;
            case 'd':
               if (!_conv (t->tm_mday, 2, pad))
                  return (0);
               continue;
            case 'H':
               if (!_conv (t->tm_hour, 2, pad))
                  return (0);
               continue;
            case 'I':
               if (!_conv (t->tm_hour % 12 ? t->tm_hour % 12 : 12, 2, pad))
                  return (0);
               continue;
            case 'j':
               if (!_conv (t->tm_yday + 1, 3, pad))
                  return (0);
               continue;
            case 'k':
               if (!_conv (t->tm_hour, 2, ' '))
                  return (0);
               continue;
            case 'l':
               if (!_conv (t->tm_hour % 12 ? t->tm_hour % 12 : 12, 2, ' '))
                  return (0);
               continue;
            case 'M':
               if (!_conv (t->tm_min, 2, pad))
                  return (0);
               continue;
            case 'm':
               if (!_conv (t->tm_mon + 1, 2, pad))
                  return (0);
               continue;
            case 'n':
               if (!insert ("\n", upcase))
                  return (0);
               continue;
            case 'p':
               if (!insert (t->tm_hour >= 12 ? "PM" : "AM", upcase))
                  return (0);
               continue;
            case 'R':
               if (!_format ("%H:%M", t, upcase))
                  return (0);
               continue;
            case 'r':
               if (!_format ("%I:%M:%S %p", t, upcase))
                  return (0);
               continue;
            case 'S':
               if (!_conv (t->tm_sec, 2, pad))
                  return (0);
               continue;
            case 'T':
            case 'X':
               if (!_format ("%H:%M:%S", t, upcase))
                  return (0);
               continue;
            case 't':
               if (!insert ("\t", upcase))
                  return (0);
               continue;
            case 'u':
               if (!_conv (t->tm_wday == 0 ? 7 : t->tm_wday, 1, pad))
                  return (0);
               continue;
            case 'U':
               if (!_conv ((t->tm_yday + 7 - t->tm_wday) / 7, 2, pad))
                  return (0);
               continue;
            case 'W':
               if (!_conv ((t->tm_yday + 7 -
                  (t->tm_wday ? (t->tm_wday - 1) : 6)) / 7, 2, pad))
                  return (0);
               continue;
            case 'w':
               if (!_conv (t->tm_wday, 1, pad))
                  return (0);
               continue;
            case 'x':
               if (!_format ("%m/%d/%y", t, upcase))
                  return (0);
               continue;
            case 'y':
            case 'g':
               if (!_conv ((t->tm_year + TM_YEAR_BASE) % 100, 2, pad))
                  return (0);
               continue;
            case 'Y':
            case 'G':
               if (!_conv (t->tm_year + TM_YEAR_BASE, 4, pad))
                  return (0);
               continue;
            case 'z':
               continue;
            case 'Z':
               if (!t->tm_zone || !insert (t->tm_zone, upcase))
                  return (0);
               continue;
            case '%':
            default:
               break;
         }
         ++fmt;
      }
      if (!gsize--)
         return (0);
      *pt++ = *fmt;
   }
   return (gsize);
}   

size_t (strftime)(char *s, size_t size, const char *fmt, const struct tm *t)
{
   pt = s;
   if ((gsize = size) < 1)
      return (0);
   if (_format (fmt, t, 0))
   {
      *pt = '\0';
      return (size - gsize);
   }
   return (0);
}
