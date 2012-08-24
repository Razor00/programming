#include<stdio.h>

typedef int uint32_t;

uint32_t find_sum(uint32_t n)
{
		uint32_t sum;

		while(n){
				sum += n%10;
				n = n/10;
		}
		return sum;
}

uint32_t find_smith_num(uint32_t n)
{
	uint32_t i=2;
	uint32_t i2;
	uint32_t cc=0;
	uint32_t sum=0;
	
	while(n%i==0){
			n = n / i;
			sum -= i;
			cc++;
	}

	i=3;
	i2=9;
	while(i2 <= n){
			if( n % i == 0 ){
				cc++;
				n = n / i;
				sum -= i;
			}
			else	
				i = i + 2;
	}
	if( !cc && (sum==0) ) 
		return 0;
	else
		return 1;
}

int main()
{
		uint32_t n=1;
		while(n){
				scanf("%d",&n);
				n++;
				while(!find_smith_num(n)){n++;}
				printf(" %d is smith_number \n",n);
			}
}
