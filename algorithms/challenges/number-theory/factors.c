#include<stdio.h>

typedef int uint32_t;

int find_factors(uint32_t n)
{
	uint32_t i=2;
	uint32_t i2;
	uint32_t cc=0;
	while(n%i==0){
			printf(" %d ", i);
			n = n / i;
			cc++;
	}

	i=3;
	i2=9;
	while(i2 <= n){
			if( n % i == 0 ){
				printf(" %d ", i);
				cc++;
				n = n / i;
			}
			else	
				i = i + 2;
	}
	printf(" %d\n", n);
}

int main()
{
		uint32_t n=1;
		while(n){
				scanf("%d",&n);
				find_factors(n);

		}
}
