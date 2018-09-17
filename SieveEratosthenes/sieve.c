
#include "sieve.h"
#include<stdbool.h>

void Sieve(bool p[], int N)
{
	for(int i = 2; i < N; i++)
	{
		if(p[i])
		{   //i*2, i*3, i*4...
			for(int j = 2; i*j < N; j++)
			{
				p[i*j] = false;
			}
		}
	}

}
