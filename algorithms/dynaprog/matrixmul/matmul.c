/***************************************************************************************
	This program is for  finding the optimal way of multiplying matrices
	like
		order
	a	3 x 3 
	b	3 x 2
	c	2 x 2
	the best of multipliying matrices
	a * b * c 
	is
************************************************************************************************/
	
#include<stdio.h>
struct MCOST {
	int row;
	int col;
	int cost;
	int pos;
};
typedef struct MCOST MCOST; 
MCOST **mcost;
int n;


void findorder(int st, int end, int j)
{
	if( st == end){
		printf("%d", st);
		return;
	}
	if( end == st+1) {
		printf( "(%d %d)",st, end);
		return;
	}
	printf("(");
	findorder(st, j, mcost[st][j].pos);
	findorder(j+1, end, mcost[j+1][end].pos);
	printf(")");
}
		
MCOST mulcost(int start, int end)
{
	int i;
	MCOST tcost1, tcost2, tcost, maxcost;
	maxcost.cost = 100000000;

	if( mcost[start][end].cost != 0 )
		return (mcost[start][end]);
	if( start == end )
		return (mcost[start][end]);

	for( i = start; i < end; i++ ){
		tcost1 = mulcost(start, i);
		tcost2 = mulcost(i+1, end);
		tcost.cost = tcost1.cost + tcost2.cost + 
				tcost1.row * tcost1.col * tcost2.row * tcost2.col;
		tcost.row = tcost1.row;
		tcost.col = tcost2.col;	
		if( tcost.cost < maxcost.cost ){
			maxcost = tcost;
			maxcost.pos = i;
		}
	}	
	return(mcost[start][end] = maxcost);	
}
	
int main()
{
	int i;
	int r, c;
	MCOST mc;
	scanf("%d", &n);
	mcost = (MCOST **)malloc( sizeof(MCOST *) * (n+1) );
	for( i = 1; i <= n; i++ ){
		mcost[i] = (MCOST *) calloc( (n+1), sizeof(MCOST) );
		scanf("%d %d\n",&r, &c);
		mcost[i][i].row =  r;
		mcost[i][i].col = c;
		mcost[i][i].cost = 0;
	}
	mc = mulcost(1, n);
	printf("r = %d\t c = %d\t cost= %d\n",mc.row, mc.col, mc.cost);	
	int j;	
	for( i = 1; i<=n; i++){
		for( j = i; j <=n; j++)
			printf("%d\t%d\t r = %d\t c = %d\tcost =%2d\tpos = %2d\n", i, j, 
			mcost[i][j].row,mcost[i][j].col, 
			mcost[i][j].cost, mcost[i][j].pos);
		printf("\n");
	
	}
	findorder(1, n, mcost[1][n].pos);
}
