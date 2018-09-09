

#include <stdio.h>
#include "ggt.h"


int ggtCalls;

int ggt(int a, int b)
{
	ggtCalls++;
	if (ggtCalls >= MAX_ITERATIONS){
		printf("num of oterations not allowed");
		return 0;
	}

	while (a > 0 && b > 0){
		if (a == b){
			return a;
		}else if (a > b){
			return ggt(a-b, b);
		}else {
			return ggt (a, b-a);
		}

	}
	printf("invalid numbers!!!");
	return 0;
}
