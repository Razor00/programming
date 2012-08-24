#include<stdlib.h>
#include<stdio.h>
#include<string.h>


int read(int **);


int compare(const char *str1, const char *str2 )
{
	return(strcmp(str1, str2));
}

int main()
{
	char arr[100];
	int i;
	int n;
	char word[100];
	printf("before sorting\n");
	/*for(i = 0; i < n; i++) 
		printf(" %d \t ", arr[i]);*/
	n = scanf("%s\n",arr);
	strcpy(word, arr);
	while( n> 0 ){
		qsort(arr, strlen(arr), sizeof(char), (int (*)(const void*, const void *))compare);
		printf("%s %s\n", arr, word);
		n =scanf("%s\n",arr);
		strcpy(word, arr);
	}
	printf("\n");
}
