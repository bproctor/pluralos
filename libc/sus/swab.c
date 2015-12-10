
void (swab)(const void *src, void *dest, ssize_t n)
{
   const char *a = (const char *)src;
   char *b = (char *)dest;
   char t1, t2;
   
   n = n & ~((ssize_t)1);
   while (n > 1)
   {
      t1 = a[--n];
      t2 = a[--n];
      b[n] = t1;
      b[n + 1] = t2;
   }
}
