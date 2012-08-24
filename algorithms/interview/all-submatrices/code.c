/*
 * =====================================================================================
 *
 *       Filename:  code.c
 *
 *    Description:  matrix who knows
 *
 *        Version:  1.0
 *        Created:  12/14/2010 07:18:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <malloc.h>
int main(int argc, char **argv)
{


	int max_r = 4;
	int max_c = 4;
		
	max_r = max_c = atoi(argv[1]);

	int *arr = malloc(max_r * max_c);

	int k = 0;
	for (k = 0; k < (max_r * max_c); k++){
			arr[k] = getc(stdin) - 128;
	}
//	int arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	int nr, nc;
	int rst, rend;
	int cst, cend;
	int i, j;
	int count = 0;
	
	int max_sum = 0;
	int cur_sum = 0;
	int pi, pj, pr, pc;

	for (nr = 1; nr <= max_r; nr++) {
		for (nc = 1; nc <= max_c; nc++) {
			for (rst = 1; rst < (max_r - nr + 2); rst++) {
				for (cst = 1; cst < (max_c - nc +2); cst++) {
					for (i = rst; i < rst + nr; i++) {	
						for (j = cst; j < cst + nc; j++) {	
			 				printf("%d ", arr[(i-1)* max_r + (j-1)]);
							count++;
							cur_sum += arr[(i-1) * max_r + (j-1)];
						}
						printf("\n");
					}
					if (cur_sum > max_sum) { max_sum = cur_sum; pi = rst; pj = cst; pr = nr; pc = nc; }
					cur_sum = 0;
					printf("\n--\n");
				}
			}
		}
	}
//	printf("max = %d, count = %d \n", max_r, count);
	printf("sum = %d, i = %d, j = %d, r = %d, c = %d \n", max_sum, pi, pj, pr, pc);
	printf("%d %d \n", max_r, count);
}
		
