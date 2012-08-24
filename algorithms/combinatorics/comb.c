#include<stdio.h>
void comb();
int main()
{
	int i,k,r,n;
	int* x;
	printf("Give the values of r and n \n");
	printf("r:\t");
	scanf("%d", &r);
	printf("n:\t");
	scanf("%d", &n);
	x = (int *) calloc((r+1), sizeof(int));	
	k = 1;
	x[k] = 1;

	while(x[1] != (n - r + 2)) {
		
		if( k == r ) {
			for( i = 1 ; i <= k ; i++ ) printf("%d ", x[i]);
			printf("\n");
	//		getc(stdin);
			if( x[k] == n )
				k--;
			x[k]++;
		}
		else {
			if( x[k] == n ){
				k--;
				x[k]++;
			}
			else {
				k++;
				x[k] = x[k-1] + 1;
			}
		}
	}
		
	free(x);
}


		
