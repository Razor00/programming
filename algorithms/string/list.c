#include<stdio.h>
int main()
{
	char word[100];
	char worder[100];
	char prevword[100];
	char prevorder[100];
	int cc=0;

	int n = scanf("%s %s\n",prevorder, prevword);
	while(n > 0 ) {
		n = scanf("%s %s\n",worder, word);
//		puts( worder);
//		puts(word);
		if( strcmp(worder, prevorder) == 0 ) {
			printf("%s %s ", prevword, word);
			cc = 0;
		}
		else{
			if( cc == 0 )
				printf("\n");	
			cc++;
			
		}
		strcpy(prevorder, worder);
		strcpy(prevword, word);	
			
	}
}
