#include<stdio.h>
#include<stdlib.h>

int **cost;
int *s;
int N;

int max(int, int);
int partition(int, int, int);

void *mymalloc(int sz)
{

	void *ptr = malloc(sz);
	printf("memory %p\n", ptr);
	return(ptr);
}
void myfree(void *ptr)
{
	printf("free %p\n", ptr);
	free(ptr);
}
int maximum(int i, int j)
{
	if (i >= j)
		return i;
	return j;
}

int main()
{
	int i,j;
	int K;
	int val;
	scanf("%d %d", &N, &K);
	cost = (int **) mymalloc (sizeof(int *) * (N+1));
	if (cost == 0)
		exit(0);

	for (i = 0; i < N+1; i++){
		cost[i] = (int *)mymalloc(sizeof(int) * (K+1));
		if (cost[i] == 0)
			exit(0);
	}

	
	for (i = 0; i < N+1; i++)
		for (j=0; j< K+1; j++)
			cost[i][j] = -1;

	s = (int *) mymalloc(sizeof(int) * (N+1));
	if (s == 0)
		exit(0);

	for (i = 1; i < N+1; i++)
		scanf("%d", &s[i]);

	s[0] = 0;
	cost[0][0] = 0;
	cost[0][1] = 0;

	for (i = 0; i < N+1; i++)
		cost[1][i] = s[N];

	for (i = 1; i < N+1; i++)
		cost[i][1] =  s[N-i+1] + cost[i-1][1]; 

	val = partition(N, K, 1);
	printf("The final matrix\n");

	for (i = 0; i < N+1; i++){
		for(j=0; j< K+1; j++)
			printf("%2d ",cost[i][j]);
		printf("\n");
	}
	
	printf("the value of partition is %d\n", val);

	myfree(s);

	for (i = 0; i < N+1 ; i++)
		myfree(cost[i]);
	
	myfree(cost);
	
}

int partition(int n, int k, int p)
{
	int i,j;
	int max=10000000, val;
	int sum=0;
	if( n == 0 ) return 0;
	if( n == 1 ) return s[p];
	if( k == 1 ){
		sum = 0;
		for(i = p; i <= N; i++)
			sum += s[i];
		return(sum);
	}
	if (cost[n][k] != -1)
		return(cost[n][k]);
	for (i = p; i <= N; i++) {
		sum = 0;
		for (j=p;j<=i;j++)
			sum += s[j];
		val = maximum(partition(N-i, k-1, i+1), sum);
		if( max	> val )
			max = val;
	}
	cost[n][k] = max;
	return (cost[n][k]);
}

