
#include "newton.h"
#include<stdio.h>
#include<math.h>
#define g 0.00000001

double f(double x)
{
  return x*x*x -x -2; //F(x)
}

double df(double x)
{
  return 3*x*x-1;    //F'(x)
}

double newton ( double x )
{
	printf("n:\tx:\n");
	  double x1;
	  int i=1;
	  do{
		x1 = x;

	    if(fabs(df(x))>=0.0001)
	    {
	      x = x1 - (f(x)/df(x));
	      printf("%d.\t%lf\n",i,x);
	      i++;
	    }
	  }while(fabs(x- x1) >= g );
	  printf("root: %lf\n\n", x);
	  return 0;
}
