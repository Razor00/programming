#include<stdio.h>
#include<stdlib.h>

int selection(int arr[], int n)
{
	int i, q;
	int *ptr;
	for( i = 0; i < n; i++ ){
		q = n - i;
		ptr = arr + i;
		do {
			q = partition(ptr, q);
		}while( q != 0);
	}
}

int main()
{
	int *arr;
	int i;
	int n;
	n = read(&arr);
	printf("Before sorting\n");
	for( i = 0; i < n  ; i++ )
		printf("%d\t", arr[i]);
	selection(arr, n);
	printf("\n After sorting\n");
	for( i = 0; i < n  ; i++ )
		printf("%d\t", arr[i]);
	printf("\n");

}
