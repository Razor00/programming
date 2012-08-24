#include<stdio.h>
#include<stdlib.h>

#define WIDTH 3
int **cost;
int lcs(int, int);
char x[1024];
char y[1024];

void print_matched_data()
{
	int i = strlen(x)-1;
	int j = strlen(y)-1;
	while( cost[i][j]){
		if( x[i] == y[j] ) {
			printf("%c ", x[i]);
			i = i - 1;
			j = j - 1;
			continue;
		}
		if( i == 0 || j == 0 )
			break;
			
		if( cost[i-1][j] >= cost[i][j-1] ) 
			i = i - 1;
		else
			j = j - 1;	
	}
}	

void print_matched_data_r(int i, int j)
{
	if( cost[i][j] == -1)
		return;
	if( x[i] == y[j] ) {
		print_matched_data_r(i-1, j-1);
		printf("%c ", x[i]);
	}
	else
	if( i == 0 || j == 0 )
		return;
	else
	if( cost[i-1][j] >= cost[i][j-1] )
		print_matched_data_r(i-1,j);
	else
		print_matched_data_r(i, j-1);

}		
	
int max(int a, int b)
{

	if( a >= b )
		return a;
	else
		return b;
} 
int main()
{
	int i, j;
	scanf("%s", x);
	scanf("%s", y);	
	
	cost = (int **)malloc(sizeof(int *) * (strlen(x)));
	for(i=0;i<strlen(x);i++)
		cost[i]=(int *)malloc(sizeof(int)*(strlen(y)));

	printf("%s\n", x);
	printf("%s\n", y);
	printf("length x = %d\n", strlen(x));
	printf("length y = %d\n", strlen(y));
	
	for(i=0;i<strlen(x);i++){
		for(j=0;j<strlen(y);j++)
			cost[i][j]=-1;
	}
	int len = lcs(strlen(x)-1, strlen(y)-1);
	printf("The lcs of x and y is = %d\n",len);
	printf("%3c",' ');
	for(i=0;i<strlen(y);i++)
		printf("%3c", y[i]);
	printf("\n");
	for(i=0;i<strlen(x);i++){
		printf("%3c", x[i]);
		for(j=0;j<strlen(y);j++)
			printf("%3d",cost[i][j]);
		printf("\n\n");
	}
	print_matched_data();
	printf("\nRecursive\n");
	print_matched_data_r(strlen(x)-1, strlen(y)-1);
	printf("\n");
	for(i=0;i<strlen(x);i++)
		free(cost[i]);
	free(cost);
}


int lcs(i, j)
{
	if( i==-1 || j==-1)
		return 0;	
	
	if( cost[i][j] != -1 )
		return cost[i][j];
	
	if(x[i] == y[j]){
		printf("i = %d j = %d %c\n ", i, j, x[i]);
		cost[i][j] = lcs(i-1, j-1) + 1;
	}
	else {
		cost[i][j] = max(lcs(i-1, j), lcs(i, j-1));
	}
	return cost[i][j];	
}	
	

