#include<stdio.h>

long fib(int);
long dyn_fib(int);
long *arr;
int main()
{
	int i;
	int n;
	long val ;
	printf("The value of n\n");
	scanf("%d", &n);
	arr = (long *)calloc(n+1, sizeof(long));
	for(i=0;i<=n;i++)
		arr[i] = -1;
	arr[0] = 0;
	arr[1] = 1;
	printf("enter the choice\n");
	scanf("%d",&val);
	if( val == 1)
		val = fib(n);
	else{
		val = dyn_fib(n);
		for(i=0;i<=n;i++) 
			printf("%ld ", arr[i]);
	}
	printf("%d\n", val);
	
	printf("\n");
	free(arr);
}


long fib(int n)
{
	if( (n == 0) || (n == 1) )
		return n;
	int val = fib(n-1) + fib(n-2);
	printf("%d ", val);
	return(val);
}

long dyn_fib(int n)
{
	if( arr[n] != -1 )
		return(arr[n]);
	arr[n] = dyn_fib(n-1) + dyn_fib(n-2);
	return(arr[n]);
}
