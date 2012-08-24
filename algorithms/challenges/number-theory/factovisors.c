#include<stdio.h>
int gcd(int a, int b)
{
			int c;
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
			return(b);
}

int main()
{
		int n, m;
		int i;
		int l;
		scanf("%d %d", &n, &m);
		printf(" %d ", m);
		for( i = 2; i <= n && m != 1 ; i++){
				m = m/gcd(i,m);
		}	
		if( m == 1) 
				printf(" divides %d! \n",n);			
		else
				printf(" does not divides %d! \n",n);			
}
