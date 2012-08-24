#include<stdio.h>
#include<malloc.h>


int find_elem(int *arr, int *len, int elem)
{
	int mid;	
	int st = 0;
	int end = *len;
//	printf("searchin for %d, end = %d, end_elem = %d\n", elem , end, arr[end]);
	while (st <= end) {
		mid = (st + end)/2;
		if (arr[mid] == elem) {
			*len = mid;
			return 1;
		}
		else if (elem > arr[mid]) {
			st = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	
	*len = st;
//	printf("failed = %d\n", *len);
	return -1;
}


/************************************************** 
*	The magic function
**************************************************/
void find_pairs(int *arr, int len, int sum)
{
	int end = len-1;
	int i = 0;	
	while(end>0) {
		if (find_elem(arr+i, &end, sum - arr[i]) != -1) { //this is how one should not write code
			printf("%d, %d \n", arr[i], arr[end+i]);
		}
		end--;		//why this?
		i++;
	}
}


// assumption is data is sorted

int main(int argc, char **argv)
{
	int sz = atoi(argv[1]);
	int sum = atoi(argv[2]);
	
	int count = sz;
	
	int *arr = malloc(sizeof(int) * sz);	
	int i = 0;
	
	while (count--) { 
	//	arr[i++] = getc(stdin); 
		scanf("%d", arr+i);
		i++;
	}

	find_pairs(arr, sz, sum);
}
