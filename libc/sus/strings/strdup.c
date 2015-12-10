
#include <string.h>
#include <stdlib.h>

char *(strdup)(const char *s)
{
   char *p;
   if(*s == '\0')
      return (NULL);
   p = (char *)malloc(strlen(s) + 1);   
   if(p == NULL)
      return (NULL);
   strcpy(p, s);
   return (p);
}
