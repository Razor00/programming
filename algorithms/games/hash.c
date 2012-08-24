#include<stdio.h>
#include<limits.h>
#define LARGE 30000000
unsigned int n;
unsigned int c;

 unsigned int hash_perfect( unsigned int *,  unsigned int );
/* hash function*/
 int hash_func( unsigned int val)
{
	return( ( c/val ) % n );
}


/* compare function for qsort*/
int cmp(const void *a, const void *b)
{
	 unsigned int i = *(( unsigned int *)a);
	 unsigned int j = *(( unsigned int *)b);
	if(i < j)
	 	return -1;
	else
		return 1;
	return 0;
}

int main()
{
	
	 short i;
//	 unsigned int data[] = { 26548, 28596, 31668, 26292, 28340, 34996, 25780, 65204, 280841, 27828, 27316, 34228};
	 unsigned int data[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};//26548, 28596, 31668, 26292, 28340, 34996, 25780, 65204, 280841, 27828, 27316, 34228};
	short size = 12;
	hash_perfect(&data[0], sizeof(data)/sizeof(data[0]));

	for( i = 0; i < size; i++ ) {
		printf("%d = %d\n", data[i], hash_func(data[i]));
	}
}	


/* hash parameter computation*/
 unsigned int hash_perfect( unsigned int *k,  unsigned int size)
{
	
	
	 
	int bi, bj;
	int i, j, x, y;
	unsigned int vi;
	unsigned int *index;
	n =  size;
	index = ( unsigned int *)malloc( sizeof( unsigned int) * n );
	
	if( index == NULL ) {
		printf("Unable to allocate memory\n");
		exit(1);
	}
	
	qsort( &k[0], n, sizeof( unsigned int), cmp);
/*	for( i = 0; i < n; i++ ) {
		printf("%u\n", k[i]);
	}*/
//	getc(stdin);

	c = ((n-2) *k[0] * k[n-1]) / (k[n-1] - k[0]);
	
	while(c < UINT_MAX){
		bi = -1;
		bj = -1;
		for( i = 0; i < n ; i++ ) {
			index[i] = hash_func(k[i]);
		}

		/*find the indexes are unique or not*/	
		for( i = n-1 ; bi<0 && i>=0 ; i--) {
			vi = index[i];
			j = i-1;
			while( bi < 0 && j >= 0 ) 
				if( vi == index[j]) {
					bi = i;
					bj = j;
				}
				else
					j--;
			
		}
		if( bi < 0 ) {
			printf("The value of c is %d\n", c);	
			free(index);
			return ;
		}
		x = k[bj] - (c % k[bj]);
		y = k[bi] - (c % k[bi]);
		if (x<y)
			c += x;
		else
			c += y;
	}
}

	
