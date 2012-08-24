/*
 * =====================================================================================
 *
 *       Filename:  robot.c
 *
 *    Description:  nxn grid right and down only
 *
 *        Version:  1.0
 *        Created:  11/30/2010 03:40:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan , madanpandiri@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *arr;
int *dir;
int size;
int row, col;

void print()
{
	int i, j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (arr[i * col + j])
				printf("%c ", arr[i * col + j]);
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("\n\n\n");

}
int robot(int x, int y, int px, int py, int pos)
{
	if ((x == (row)) || (y == (col))) {
		return;
	}

	int val = px * col + py ;
	if (!arr[val]){
			arr[val] = pos;
			if ((x == (row-1)) && (y == (col-1))){
				print();
			}
			else {
				robot(x,   y+1, x, y, 'F');
				robot(x+1,   y, x, y, 'D');
				robot(x+1, y+1, x, y, 'C');
			}	
			arr[val] = 0;
	}
}



int main(int argc, char **argv)
{
		row = col  = atoi(argv[1]);
		arr = malloc(row * col * sizeof(int));
		if (!arr)
			exit(0);
		memset(arr, 0, (row * col) * sizeof(int));
		robot(0, 1, 0, 0, 'F');
		memset(arr, 0, (row * col) * sizeof(int));
		robot(1, 0, 0, 0, 'D');
		memset(arr, 0, (row * col) * sizeof(int));
		robot(1, 1, 0, 0, 'C');
}
