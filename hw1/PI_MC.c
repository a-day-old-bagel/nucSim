/*
Marsaglia Random Number Generator (RNG) program
*/

/* system include files for input and output*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Include file with the Marsaglia RNG function suite*/

#include "random_number.h"

#define RND_MAX 16777216 /* ^24 max number for 24 bit rng*/

main(int argc, char *argv[])
{
  int i,loop;
  double x,y,dist;
  double numbCircleHits,numbSquareHits;

  fprintf(stderr,"generating random numbers using the Marsaglia method\n");

/* supply the seeds to begin the RNG*/
  start_random_number(101,202);

  loop=3; /* default number of random numbers to generate*/

  if(argc>1)
    {

      loop=atoi(argv[1]); /* convert the comand line string to an integer*/
      if(loop>2147483647|| loop < 0)
	{
	  fprintf(stderr,"\t\t ***ERROR*** \nrequested number exceeds maximum value for signed int \n see /usr/include/limits.h\n");
	  exit(1);
	}
    }
  else
    {
      fprintf(stderr,"Generating 3 random numbers\n");
      fprintf(stderr,"If you want more add the number you want after the program name\n");
    }

  for(i=0;i<loop;i++)
    {
      x=next_random_number();
      y=next_random_number();
      //      dist=(x-0.5)*(x-0.5)+(y-0.5)*(y-0.5);
      dist=x*x+y*y;
      if(dist>0)
	{
	  dist=sqrt(dist);

	  //	  fprintf(stderr,"%g\t%g\t%g\n",x,y,dist);
	  //	  if(dist<=0.5)
	  if(dist<=1.0)
	    numbCircleHits+=1.0;
	  numbSquareHits+=1.0;
	}

    }
  fprintf(stderr,"Pi=4*%g/%g=%g\n",numbCircleHits,numbSquareHits,4*numbCircleHits/numbSquareHits);

}

