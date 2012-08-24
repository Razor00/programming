#include<stdio.h>

int selElement(int *ptr, int pos, int n)
{
	int q = 0;
	while( 1 ) {
		
		//printf( " before partition q = %d pos = %d ptr = %p num of elements = %d\n", q, pos, ptr, n);
		q = partition( ptr, n);
		if ( q > pos ) {
			n = q;
		}
		else	
		if( q < pos ) {
			n = n - (q+1);
			ptr = ptr+(q+1);
			pos = pos - (q+1);
		}
		else {
			break;
		}
		//printf( "  after partition q = %d pos = %d ptr = %p num of elements = %d\n\n\n", q, pos, ptr, n);
	}
	return( ptr[q] );
	
}

int main()
{
	int *arr;
	int n,i;
	n = read(&arr);
//	for( i = 0; i < n ;i++)
//		printf(" %d\t", selElement(arr, i, n));
		printf(" %d\t", selElement(arr, n/2, n));
	
	printf("\n");
	free(arr);
}	
