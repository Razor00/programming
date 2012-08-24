#include<stdio.h>
int main()
{
			int a , b , c;
			int rem;
			scanf("%d %d", &a, &b);
			c = b;
			if( a < b ) {
					c = a;
					a = b;
			}
			while(c) {
					b = c;
					c  = a % b;		
					a = b;
			}
			printf("gcd %d  \n", b);
}
						
