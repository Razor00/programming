#include<stdlib.h>
#include<stdio.h>
int read(int **);

void sort(int arr[], int n)
{
	int q;
	while( n > 1){
		q = partition(arr, n);
	//	printf(" position q = %d parition element= %d\n", q, arr[q]);
		sort(arr, q);
		arr = arr+(q+1);
		n   = n-(q+1);
	}
} 
static void mysort(int arr[], int n)
{
	int q;
	if( n > 1){
		q = partition(arr, n);
	//	printf(" position q = %d parition element= %d\n", q, arr[q]);
		mysort(arr, q);
		mysort(arr+(q+1), n-(q+1));
	}
}

int main()
{
	int *arr;
	int i;
	int n;
	n = read(&arr);
	printf("before sorting\n");
	for(i = 0; i < n; i++) 
		printf(" %d \t ", arr[i]);
	sort(arr, n);
	printf("\nAfter sorting\n");
	for(i = 0; i < n; i++) 
		printf(" %d \t ", arr[i]);
	printf("\n");
	free(arr);
}
