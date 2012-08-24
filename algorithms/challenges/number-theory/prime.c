#include<stdio.h>


int isprime(unsigned int n)
{
	unsigned int i;
	unsigned int i2;
	if( n % 2 == 0 ){
			return 0;
	}
	i=3;
	i2 = 9;
	while( i2 <= n ) {
		if( n % i == 0 ){
//				printf(" %d divides n \n",i); 
				return 0;
		}
		i2 += 4 * i + 4;
		i = i + 2;
				
	}	
	return 1;
}

int main()
{
		unsigned int n=1;
		while(n){
				printf("enter a no :  ");
				scanf("%d", &n);
				printf("%d - %s", n, isprime(n)?" a prime \n":" not a prime\n");
		}
}
