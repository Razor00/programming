#include<stdio.h>
int main()
{
	unsigned int n;
	while(scanf("%d", &n) != EOF){
		printf("%u\n", n);
		fscanf(stderr, "%u", &n);
		printf("%d\n", n);
	}
}
