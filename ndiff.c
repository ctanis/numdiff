#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char** argv)
{
     FILE *A, *B;
     double af, bf;
     double rms=0;

     double rms_relB=0;
     double rms_relA=0;

     double avgA=0;
     double avgB=0;

     double normA=0;
     double normB=0;


     int count=0;
     double max=0;
     int max_loc=-1;
     double max_rel;

     if (argc != 3)
     {
	  fprintf(stderr, "usage error\n");
	  exit(-1);
     }

     A = fopen(argv[1], "r");
     if (A == NULL)
     {
	  fprintf(stderr, "open %s failed -- %s\n", argv[1], strerror(errno));
	  exit(-1);
     }

     B = fopen(argv[2], "r");
     if (B == NULL)
     {
	  fprintf(stderr, "open %s failed -- %s\n", argv[2], strerror(errno));
	  exit(-1);
     }

     while (fscanf(A, "%lf", &af) > 0)
     {
	  if (fscanf(B, "%lf", &bf) <= 0)
	  {
	       fprintf(stderr, "size mismatch (B)\n");
	       exit(-1);
	  }

	  avgA += af;
	  avgB += bf;

          normA += af*af;
          normB += bf*bf;

	  if (fabs(af - bf) > max)
	  {
	       max = fabs(af-bf);
               max_rel = max/(fabs(af) < fabs(bf) ? fabs(af) : fabs(bf));
	       max_loc = count;
	  }


	  rms += (af-bf)*(af-bf);

	  // this is not right
	  if ((af != 0.0) || (bf != 0))
	  {

	       double relA_error = fabs((af-bf) / af);
	       double relB_error = fabs((af-bf) / bf);

	       rms_relA += relA_error * relA_error;
	       rms_relB += relB_error * relB_error;
	  }

	  count++;
     }

     if (fscanf(B, "%lf", &bf) > 0)
     {
	  fprintf(stderr, "size mismatch (A)\n");
	  exit(-1);
     }


     printf("count: %d values\n", count);
     printf("rms: %.15g\n", sqrt(rms)/count);
     printf("max: %.15g @ %d\n", max, max_loc);

     printf("\n");
     
     printf("L2-norm of A: %.15g\n", sqrt(normA));
     printf("L2-norm of B: %.15g\n", sqrt(normB));

     printf("\n");

     printf("average A value: %.15g\n", avgA/count);
     printf("average B value: %.15g\n", avgB/count);

     /* printf("rms, relative to A: %.15g\n", sqrt(rms_relA)/count); */
     /* printf("rms, relative to B: %.15g\n", sqrt(rms_relB)/count); */
     printf("relative error at location : %.15g\n", max_rel);
     printf("max, relative to A: %.15g\n", max/(sqrt(normA/count)));
     printf("max, relative to B: %.15g\n", max/(sqrt(normB/count)));


     return 0;
}

/* Local Variables: */
/* compile-command: "gcc -Wall -O3 ndiff.c -o numdiff -lm" */
/* End: */
