
#include <stdio.h>
#include <stdlib.h>
#include "ggt.h"


int ggtCalls;

int main(void) {	
	int a, b;
	printf("----Welcome to the GDC calculator----\n");
	printf("This Program allows a Maximun of %i Iterations\n", MAX_ITERATIONS);
	printf("Insert two Integers Numbers\n");
	scanf("%i", &a);
	scanf("%i", &b);
	printf ("Number of Iterations : %d\nGDC is : %d\n ", ggtCalls,ggt (a, b));

	return 0;
}
