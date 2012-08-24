#include<stdlib.h>
#include<stdio.h>
#include<math.h>

unsigned int get_rand(unsigned int low, unsigned high)
{
    return low + (1.0 + (unsigned int) (10.0 * ((rand() / (RAND_MAX + 1.0))))) * ((high-low) * 1.0 /(10-1));
//    return (1.0 + 10.0 * (rand() / (RAND_MAX + 1.0)));
}

int main()
{
	int a ;
	int j=100;
	while(--j)
		printf ("%u \n", get_rand(2, 9));
}

