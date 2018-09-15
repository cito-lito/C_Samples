
#include <stdio.h>
#include <stdbool.h>
#include"sieve.h"

int main(void) {

	int N;
    printf("Enter an Integer number: ");
    scanf("%i", &N);
    bool p[N];
    for (int i = 2; i < N; i++)
    {
    	p[i] = true;
    }
    Sieve(p, N);

    int count = 0;
	for (int i = 2; i < N; i++)
	{
		if (p[i])
		{
			printf("%i\n", i);
			count++;
		}

	}
	printf("There are %i Prime Numbers from 2 to %i\n”", count, N);
	return 0;
}