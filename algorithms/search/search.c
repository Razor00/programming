#include <stdio.h>
#include <stdlib.h>

int find_elem(int *arr, int st, int end, int value)
{
	int mid;

	while (st < end){
		mid = (st + end)/2;
		if (value > arr[mid]){
			st = mid + 1;
		}
		else if (value < arr[mid]){
			end = mid - 1;
		}
		else
			return mid;
	}	
	return end;	
	

}


void  search(int *arr, int nelem, int x)
{
	int st = 0, end = nelem - 1, y;
	if (x < arr[st] || x > (arr[end] + arr[end-1])){
		printf("nothing\n");
		return;
	}
	while (st < end){
		y = x - arr[st];
		if ( y > arr[end]) {
			st++;
			continue;
		}
		end = find_elem(arr, st, end, y);	
		if (arr[end] == y){
			printf("found %d-%d, %d-%d \n", st, arr[st], end, arr[end]);
			return;
		}
	}
}

int main(int argc, char **argv)
{

	int sum = atoi(argv[1]);
	int nelem = atoi(argv[2]);
	int *arr = malloc(sizeof(*arr) * nelem);
	
	int i = 0;
	for (i = 0; i < nelem; i++) {
		scanf("%d", arr+i);
	}
	search(arr, nelem, sum);
}
