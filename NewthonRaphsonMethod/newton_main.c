
#include "newton.h"
#include<stdio.h>

int main(void)
{
	double x;
	printf("\nWelcome! we are going to calculate the root of an equation\n");
	printf("with the Newton-Raphson Method: Xn+1 = Xn - F(x)/F'(x)\n");
	printf("The equation is : x^3-x-2\n");
	printf("Enter the Xo Value:");
	scanf("%lf", &x);

	newton(x);

return 0;
}
