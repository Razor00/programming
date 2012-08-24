#include<stdio.h>
//LIsts all the possible representations of the 
//r combinations 
//of n elements
//coded by Arrow
//algorithm: 
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
	x = (int *) calloc((n +1), sizeof(int));	
	k = n;
	printf("\n");
	while(k) {
		if( k == n ) {
			for( i = 1 ; i <= k ; i++ ) printf("%d ", x[i]);
			printf("\n");
			while( x[k] == (r-1) )
				k--;
			x[k] = (x[k]+1)%r;
		}
		else {
			k++;
			x[k] = (x[k]+1)%r;
		}
	}
	free(x);
}


		
