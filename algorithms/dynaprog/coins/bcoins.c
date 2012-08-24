#include<stdio.h>
int *arr;
int **cost;
int *s;
int n;
int Total;

void print()
{
	int j;
	for( j=0; j<n;j++ )
		printf("%d ", s[j]);
	printf("\n");
}

int coin(int total,int i)
{
	if( cost[total][i] != Total+1 )
		return cost[total][i];

	if( total == 0  ) {
//		print();
		return 0;
	}
/*	if( i < 0 ){
		printf("called\n");
		return(Total+1);//cost[total][i]);
		
	}*/
	int val = total/arr[i];
	if( i == 0 ) {
		if( total%arr[i] == 0 ) {
			s[i] = val;
			//print();
			s[i] = 0;
			cost[total][i] = val;		
		}
		return(cost[total][i]);
	}
			
	int j, index = val, tcost, min = Total + 1;
	for( j = 0; j <=index; j++) {
		s[i] = j;
		val = total - (j * arr[i]);
		tcost = coin(val, i-1)+j;
		if( tcost < min )
			min = tcost;
		s[i] = 0;
	}
	return (cost[total][i]=min);	
}

int main()
{
	int i, j;
	scanf("%d %d", &n, &Total);
	arr = (int *) malloc(sizeof(int) * n);
	s   = (int *) calloc(n, sizeof(int));

	printf("Total = %d\n", Total);

	for(i=0;i<n;i++){
		scanf("%d", &arr[i]);
		printf("%d ", arr[i]);
	}

	cost = (int **)malloc(sizeof(int *) * (Total+1));

	for(i=0;i<=Total;i++) {
		cost[i] = (int *)malloc(sizeof(int) * n);
		for(j=0;j<n;j++)
			cost[i][j] = Total+1;
	}
	

	printf("\n");
	printf("min coins = %d\n", coin( Total, n-1));
	printf("coin table\n");
/*	for(i=0;i<=Total;i++) {
		for(j=0;j<n;j++)
			printf("%d ",cost[i][j]);
		printf("\n");
	}*/
	free(arr);
	free(s);
	for(i=0;i<=Total;i++) 
		free(cost[i]);
	free(cost);
}
