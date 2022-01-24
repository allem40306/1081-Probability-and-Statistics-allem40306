#include <stdio.h>
#include <string.h>
#include <stdlib.h>
main (int argc, char * argv[]) {
   int i, j;
   int n, m;
   FILE *foutptr;
   double *a;
   double *ptr;

   printf ("argv[1] is '%s'\n", argv[1]);
   printf ("argv[2] is '%s'\n", argv[2]);
   printf ("argv[3] is '%s'\n", argv[3]);
   
   m = atoi (argv[1]);
   n = atoi (argv[2]);
   a = (double *) malloc ((m * n + 1)* sizeof(double));
   ptr = a;
   for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) 
         *(ptr++) = (double) i * (double) j / ((double) m * (double) n) + 1;
   }

   foutptr = fopen (argv[3], "w");
   fwrite (&m, sizeof(int), 1, foutptr);
   if(n != 1)fwrite (&n, sizeof(int), 1, foutptr);
   fwrite (a, sizeof(double), m * n, foutptr);
   fclose (foutptr);
}
    