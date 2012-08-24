#include<stdio.h>
int *arr;
int **cost;
int *s;
int n;

void print()
{
	int j;
	for( j=0; j<n;j++ )
		printf("%d ", s[j]);
	printf("\n");
}

void coin(int total,int i)
{
	if( total == 0  ) {
		print();
		return;
	}
	if( i < 0 )
		return;
	int val = total/arr[i];
	if( i == 0 ) {
		if( total%arr[i] == 0 ) {
			s[i] = val;
			print();
			s[i] = 0;
		}
		return;
	}
			
	int j, index = val;
	for( j = 0; j <=index; j++) {
		s[i] = j;
		val = total - (j * arr[i]);
//		cost[total][i] = min( coin(val, i-1) , );
		s[i] = 0;
	}
//	return (cost[total][i]);	
}

int main()
{
	int i, j;
	int total;
	scanf("%d %d", &n, &total);
	arr = (int *) malloc(sizeof(int) * n);
	s   = (int *) calloc(n, sizeof(int));

	printf("Total = %d\n", total);

	for(i=0;i<n;i++){
		scanf("%d", &arr[i]);
		printf("%d ", arr[i]);
	}

	cost = (int **)malloc(sizeof(int *) * (total+1));

	for(i=0;i<=total;i++) {
		cost[i] = (int *)malloc(sizeof(int) * n);
		for(j=0;j<n;j++)
			cost[i][j] = -1;
	}
/*	cost[0] = (int *)malloc(sizeof(int) * n);
	for(j=0;j<n;j++)
		cost[0][j] = 0;*/
	

	printf("\n");
	coin( total, n-1);
	free(arr);
	free(s);
}
