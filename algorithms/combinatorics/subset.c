#include<stdio.h>
#include<stdlib.h>

int LIMIT;
int NOVAR;
char* pch = 0;
char* arr = 0;
void per(int i);
int main(int argc, char **argv)
{
	int ch;
	int i,j;
	if( argc != 3){
		printf("Usage: list limit numberofvairations\n"
			" list 20 4 \n");
		exit(0);
	}
	LIMIT = atoi(argv[1]);
	NOVAR = atoi(argv[2]);
//	printf(" Limit = %d\t NOVAR = %d\n", LIMIT, NOVAR);
	arr = (char *)malloc(sizeof(NOVAR));
	if( arr == 0 ){
		perror("Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	
	for( i = 0; i < NOVAR; i++ ) {
		arr[i] = '0' + i;
	}
			
	pch = (char *)malloc(sizeof(LIMIT));
	if( pch == 0 ){ 
		perror("Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	per(0);
	free(pch);
	free(arr);
}

void per(int i)
{
	int j;
	if( i == LIMIT ){
		printf("%s\n",pch);
		return;
	}
	for(j=0;j<NOVAR;j++){
		pch[i] = arr[j];
		per(i+1);
	}
}
