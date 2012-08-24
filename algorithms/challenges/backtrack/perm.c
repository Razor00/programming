#include<stdio.h>
#include<stdlib.h>

int *garr;

void print(int *arr, int n)
{
		int i;
		for(i=0;i<n;i++){
				printf("%d ",arr[i]);
		}
		printf("\n");
}

void perm(int *arr, int pos, int maxlen)
{
		int i;
		int k;
		if( pos == maxlen){
				print(arr, maxlen);
		}
		k = 0;
		for(i=pos; i<maxlen; i++){
			while( garr[k] != 0 ){
					k = (k+1)%maxlen;
			} 
			arr[pos]= k+1;
			garr[k] = 1;
			perm(arr, pos+1, maxlen);
			garr[k] = 0;
			arr[pos]=0;		
			k = (k+1)%maxlen;
		}
}




int main()
{
	
	int *arr;
	int n;
	int i=0;
	printf(" enter the size :");
	scanf("%d", &n);
	arr = calloc(n, sizeof(*arr));
	garr = calloc(n, sizeof(*garr));
	if( !garr  ) {
			perror(" Error allocating memory \n");
			exit(EXIT_FAILURE);
	}
	perm(arr, 0, n);
}

