#include<stdio.h>
int rEnd, cEnd;
int **arr;
int **cost;
int sx,sy;
int ex,ey;
struct {
	int i;
	int j;
}dir[]= {
	{ 0, 1 },
	{-1, 0 },
	{ 0,-1 },
	{ 1, 0 }
	};
	
	
		
void print()
{
	int i, j;
	for( i = 1; i < rEnd+1; i++) {
		for( j = 1; j < cEnd+1; j++)	
			printf("%2d ", cost[i][j]);
		printf("\n");
	}
	printf("---------------------------\n");
	for( i = 1; i <= rEnd; i++){
		for( j = 1; j <= cEnd; j++){
/*			if( arr[i][j] = -1 )
				printf("X ");
			else
				printf("1 ");*/
			//printf("%2d ", arr[i][j]);
			switch(arr[i][j]) {
				
				case -1:
					printf("I  ");
					break;
				case 0:
					printf("X  ");
					break;
				case 1:
					printf("v  ");
					break;
				case 2:
					printf("^  ");
					break;
				case 3:
					printf("-> ");
					break;
				case 4:
					printf("<- ");
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
}


int mmove(int r, int c, int d)
{
	int i;
	int dr, dc;
	int mcost = rEnd * cEnd + 1;
	if( (r == ex) && (c == ey) ){
		return 0;
	if( (cost[r][c] != -1) && (cost[r][c] != mcost) )
		return(cost[r][c]);
	d = (d+2)%4;
	for( i = 1; i <= 3; i++ ) {
		d = (d+1)%4;
		dr = dir[d].i;
		dc = dir[d].j;
		if( arr[r+dr][c+dc] == 0 ) {
			arr[r+dr][c+dc] = d;
			temp1 = move(r+dr, c+dc) + 1;
			arr[r+dr][c+dc] = 0;
			if( temp1 == 1);
		}
	}
			
	
}	
int move(int r, int c)
{
	int mcost= rEnd * cEnd + 1;
	int temp1 = mcost;
	
	if((r == ex) && (c == ey)){
//		print();
		printf("\n-------------------\n");
		return 0;
	}
	if( (cost[r][c] != -1) && (cost[r][c] != mcost) )
		return(cost[r][c]);

	if( arr[r+1][c] == 0 ) {
			arr[r+1][c] = 1;
			temp1 = move(r+1, c) + 1;
			arr[r+1][c] = 0;
			if( temp1 == 1)
				return(cost[r][c] = temp1);
			if( temp1 < mcost)
				mcost = temp1;
	}
	if( arr[r][c+1] == 0  ){
			arr[r][c+1] = 3;
			temp1 = move(r, c+1)+1;
			arr[r][c+1] = 0;
			if( temp1 == 1)
				return(cost[r][c] = temp1);
			if( temp1 < mcost)
				mcost = temp1;
	}
	if( arr[r-1][c] == 0 ){
			arr[r-1][c] = 2;
			temp1 = move(r-1, c)+1;
			arr[r-1][c] = 0;
			if( temp1 == 1)
				return(cost[r][c] = temp1);
			if( temp1 < mcost)
				mcost = temp1;
	}
	if( arr[r][c-1] == 0 ){
			arr[r][c-1] = 4;
			temp1 = move(r, c-1)+1;
			arr[r][c-1] = 0;
			if( temp1 == 1)
				return(cost[r][c] = temp1);
			if( temp1 < mcost)
				mcost = temp1;
	}
	return(cost[r][c]=mcost);	
}




int main()
{
	int i, j;
	int temp;
	scanf("%d %d",&rEnd, &cEnd);
	scanf("%d %d",&sx, &sy);
	scanf("%d %d",&ex, &ey);
	temp = rEnd * cEnd;

	arr  = (int **) malloc( sizeof(int *) * (rEnd+2) );
	cost = (int **) malloc( sizeof(int *) * (rEnd+2) );

	for( i = 0; i <=rEnd+1; i++){
		arr[i]  = (int *)malloc(sizeof(int) * (cEnd+2));
		cost[i] = (int *)malloc(sizeof(int) * (cEnd+2));
	}

	for( i = 1; i <=rEnd; i++) {
		for(j=1;j<=cEnd; j++)	
			scanf("%d", &arr[i][j]);
	}

	for(i = 0; i <=cEnd+1 ; i++){
 			arr[0][i]  = arr[rEnd+1][i]  = -1;
			cost[0][i] = cost[rEnd+1][i] = temp;
	}
	
	for(j = 0; j <=rEnd+1 ; j++){
			arr[j][0]  = arr[j][cEnd+1]  = -1;
			cost[j][0] = cost[j][cEnd+1] = temp;
	}
	
	for( i = 1; i < rEnd+1; i++) {
		for(j = 1; j < cEnd+1; j++){
			if( arr[i][j]==-1)
				cost[i][j] = temp;	
			else
				cost[i][j] = -1;
		}
	}
//	ex = rEnd;
//	ey = cEnd;
	cost[ex][ey] = 0;
//	sx = 1;
//	sy = 1;
	arr[sx][sy]=1;
	print();	
	printf("--------------------------\n");
	printf("cost = %d\n",move(sx, sy));
	for( i = 1; i < rEnd+1; i++) {
		for(j=1;j< cEnd+1; j++)	
			printf("%2d ", cost[i][j]);
		printf("\n");
	}
	
}
