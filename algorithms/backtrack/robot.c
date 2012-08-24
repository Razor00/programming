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
	int cc = 0;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (arr[i * col + j])
				printf("%c ", dir[cc++]);
			else
				printf("  ");
		}
		printf("\n");
	}
	printf("\n\n\n");

}
int robot(int x, int y, int slot, char pos)
{
	if ((x == (row+1)) || (y == (col+1))) {
		if ((px >= (row)) && (py >= (col)))
			print();
		return;
	}

	dir[slot] = pos;
	int val = x * col + y ;
	if (!arr[val]){
			arr[val] = 1;
			robot(x, y+1, slot+1, 'F');
			robot(x+1, y, slot+1, 'D');
			arr[val] = 0;
	}
}



int main(int argc, char **argv)
{
		row = col  = atoi(argv[1]);
		arr = malloc(row * col * sizeof(int));
		dir = malloc((row+1) * (col+1) * sizeof(int));
		if (!arr || !dir)
			exit(0);
		memset(arr, 0, (row * col) * sizeof(int));
		memset(dir, 0, (row + 1) * (col + 1) * sizeof(int));
		dir[0] = 'F';
		robot(0, 0, 0, 'F');
}
