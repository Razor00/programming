#include<stdio.h>
#include<stdlib.h>

int glimit=0;
void print(int *arr)
{
		int i;
		for(i=1;i<=glimit;i++){
				if( arr[i] == 1 ){
						printf("%d ",i);
				}
		}
		printf("\n");
}
void comb(int *arr, int n, int k)
{
		int i;
		if(k==0){
				print(arr);
		}
		for(i=n; i<=glimit; i++){
				arr[i]=1;
				comb(arr, i+1,k-1);
				arr[i]=0;
		}
}


int main()
{
		int *arr;
		int k;
		printf("enter the size of arr : = ");
		scanf("%d", &glimit);
		arr = calloc(sizeof(*arr), (glimit+1));
		if( arr == NULL ) {
				perror(" Unable to allocate memory ");
				exit(EXIT_FAILURE);
		}
		printf("enter the comb size = ");
		scanf("%d", &k);
		comb(arr, 1,k);
}
