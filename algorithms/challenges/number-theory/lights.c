#include<stdio.h>

int issquare(unsigned int n)
{
		unsigned int k = (unsigned int)sqrt((double)n);
		if( k * k  == n )
				return 1;
		return 0;
}

int main()
{
		unsigned int n=1;
		printf("enter a no :  ");
		scanf("%d", &n);
		printf("%s", issquare(n)?" yes\n":" no\n");
		
}
