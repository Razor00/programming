#include<stdio.h>

int *arr;

void swap(int ,int);
void reverse(int ,int);
int main()
{
	int i=0, j=0, finish=0;
	int n= 4;
	printf("Enter the number 0-9\n");
	scanf("%d", &n);
	arr = (int *)malloc(n * sizeof(int));
	if( !arr )
		exit(0);
	for(i=0;i<n;i++)
		arr[i]=i+1;
	while(1){
		finish = 1;
		for(i = 0 ; i < n-1; i++ ) { 
			if( arr[i] < arr[i+1] )
				finish = 0;	
			printf("%d ", arr[i]); 
		}
		
		printf("%d\n",arr[i]); 
		if( finish )
			break;
		i = n-1;
	        while(arr[i-1] > arr[i]) i--;		// go on until u find order 3>4 like 1342 now i = 1
		i = i-1;		
		j = n-1;		
		while(arr[j] < arr[i]) j--;
		swap(i, j);
		reverse(i+1, n-1);
	}
	free(arr);
	
}	

void swap(int i, int j)
{
	int temp;
	temp = arr[j];
	arr[j] = arr[i];
	arr[i] = temp;
}

void reverse(int start, int end)
{
	while(start < end )  
		swap(start++, end--);
	
}
		

