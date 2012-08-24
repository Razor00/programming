#include<stdio.h>

int isprime(unsigned int n)
{
	unsigned int i;
	unsigned int i2;
	if( n % 2 == 0 ){
		return 0;
	}
	i = 3;
	i2 = 9;
	while( i2 <= n ) {
		if( n % i == 0 ){
			return 0;
		}
		i2 += 4 * i + 4;
		i = i + 2;

	}
	return 1;
}

//(a power m)mod n

unsigned int mod(unsigned int a, unsigned int m, unsigned int n)
{
	unsigned int b = 1;

	while (m > 1){
		if (a > n) {
			a = a%n;
			if (a == 1) return b;
		}
		else {
			if (m % 2 != 0){
				b = (b * a) % n;
			}				
			a = a * a;
			a = a % n;
			m = m / 2;
		}
	}
	return ((a * b) % n);
}

#if 0

int main()
{
	unsigned int l;
	unsigned int a, m, n;
	printf(" Enter a = ");
	scanf("%d",&a);
	printf(" Enter m = ");
	scanf("%d",&m);
	printf("Enter n = ");
	scanf("%d",&n);
	l = mod(a, m, n);	
	printf(" the value of l = %u \n", l);
}
#endif


int main()
{
	unsigned int n=1;
	unsigned int i;
	while(n){
		scanf("%u", &n);
		if( isprime(n) ){
				printf(" %u is normal \n", n);
				continue;
		}
		for(i = 2; i < n; i++) {
			int ret =  mod(i, n, n);
#if 0
			printf(" %u, %u - %d\n", i, n, ret);
#endif
			if( ret != i){
				printf(" %u is normal \n", i);
				break;
			}	
		}	
		if( i == n ){
			printf("The number %u is a Carmichael number \n",n);
		}
	}	
}
