#include<stdio.h>
int rEnd, cEnd;
int **arr;
void print()
{
	int i, j;
	for( i = 1; i <= rEnd; i++){
		for( j = 1; j <= cEnd; j++){
/*			if( arr[i][j] = -1 )
				printf("X ");
			else
				printf("1 ");*/
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
}
	
void move(int r, int c)
{
	int k = 0;
	if((r == rEnd) && (c == cEnd)){
		print();
		printf("\n-------------------\n");
		return;
	}
//	print();
//	printf("\n-------------------\n");
	if( arr[r+1][c] == 0 ) {
			arr[r+1][c] = 1;
			move(r+1, c);
			arr[r+1][c] = 0;
	}
	if( arr[r-1][c] == 0 ){
			arr[r-1][c] = 1;
			move(r-1, c);
			arr[r-1][c] = 0;
	}
	if( arr[r][c+1] == 0 ){
			arr[r][c+1] = 1;
			move(r, c+1);
			arr[r][c+1] = 0;
	}
	if( arr[r][c-1] == 0 ){
			arr[r][c-1] = 1;
			move(r, c-1);
			arr[r][c-1] = 0;
	}
		
	return;	
}




int main()
{
	int i, j;
	scanf("%d %d",&rEnd, &cEnd);
	arr = (int **)malloc(sizeof(int *) * (rEnd+2));
	for( i = 0; i < rEnd+2; i++){
		arr[i] = (int *)malloc(sizeof(int) * (cEnd+2));
	}
	for( i = 1; i < rEnd+1; i++) {
		for(j=1;j< cEnd+1; j++)	
			scanf("%d", &arr[i][j]);
		
	}
	for(i = 0; i < rEnd+2 ; i++)
			arr[0][i]= -1;
	for(i = 0; i < rEnd+2 ; i++)
			arr[rEnd+1][i]= -1;
	for(j = 0; j < cEnd+2 ; j++)
			arr[j][0]= -1;
	for(j = 0; j < cEnd+2 ; j++)
			arr[j][cEnd+1]= -1;
	
	print();	
	printf("--------------------------\n");
	arr[1][1]=1;
	move(1, 1);
	
}
