

#include <stdio.h>
#include "ggt.h"

int ggtCalls = 0;

int ggt(int a, int b)
{
	ggtCalls++;
	if (ggtCalls >= MAX_ITERATIONS)
	{
		printf("num of Iterations required not allowed > %i\n", MAX_ITERATIONS);
		return -1;
	}

	while (a > 0 && b > 0)
	{
		if (a == b)
		{
			return a;
		}
		else if (a > b)
		{
			return ggt(a-b, b);
		}
		else 
		{
			return ggt (a, b-a);
		}

	}
	printf("invalid numbers!!!\n");
	return -1;
}
