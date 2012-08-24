#include<stdio.h>
#include<stdlib.h>
#define N  9 
#define SN 3

#define MAX_VALUE  9
#define MIN_VALUE 3
//int arr[16][16]={0};

int arr[9][9] = {
		
	{ 3, 6, 5,  1, 8, 2,  7, 4, 9 },
	{ 7, 9, 2,  0, 0, 0,  0, 0, 0 },
	{ 4, 1, 8,  6, 0, 9,  5, 0, 0 },

	{ 6, 5, 0,  0, 4, 0,  0, 7, 1 },
	{ 0, 4, 0,  0, 0, 0,  0, 2, 0 },
	{ 1, 2, 0,  0, 6, 0,  0, 9, 8 },

	{ 0, 0, 6,  4, 0, 5,  8, 0, 0 },
	{ 0, 0, 0,  0, 0, 0,  0, 0, 0 },
	{ 9, 0, 0,  0, 1, 0,  0, 0, 7 },
		 		
		};

int fill(int);
void display();



int main()
{
	FILE *fp;
	int i, j;
//	fp = fopen("data", "r");
//	if( fp == NULL ) {
//		perror("Unable to open file data\n");
//		exit(EXIT_FAILURE);
//	}
#if 0
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++)
			scanf("%d",&arr[i][j]);
//		fscanf(fp,"\n");
	}
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++)
			printf("%d\t",arr[i][j]);
		printf("\n");
	}

#endif
	
	fill(0);
	return;
}

int fill(int NUM)
{
	int i, j, n;
	int row, col;
	int val;
	int retval;
	if( NUM == N * N ) {
		display();
		exit(0);
	}

	row = NUM / N;
	col = NUM % N;
	
	for (val = 1; val  <= N; val++) {
		retval =  put(row, col, val);
		if (retval == 1) {
			arr[row][col] = val;
			fill(NUM+1);
			arr[row][col] = 0;
		}
		else
		if (retval == 2) {
			fill(NUM + 1);
			return;
		}
		
	}	
	return;			
}


int put(int row, int col, int val)
{
	int i, j, k;
	int si, sj;


	if ((arr[row][col] >= MIN_VALUE) && (arr[row][col] <= MAX_VALUE))
		return 2;

	for (i = 0; i < N; i++){
		if (arr[row][i] == val || arr[i][col] == val)
			return 0;		
	}
	
	si = row/SN;
	si = si * SN;
	sj = col/SN;
	sj = sj * SN;
	
	for (i = si; i < si + SN; i++)
		for (j = sj; j < sj + SN; j++)
			if (arr[i][j] == val)
				return 0;
	
	return 1;
}	


void display()
{
	int i, j;
	static count = 0;
	printf(" count = %d\n", ++count);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf(" %d  ", arr[i][j]);
			if ((j+1)%SN == 0) 
				printf("\t");
		}		
		if ((i+1)%SN == 0) 
			printf("\n");	
		printf("\n\n");
	}
}
