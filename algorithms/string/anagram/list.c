#include<stdio.h>
#include<string.h>

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
		if (n < 0)
			break;
		if( strcmp(worder, prevorder) == 0 ) {
			printf("%s ", prevword);
			cc = 0;
		}
		else{
			if( cc == 0 )
				printf("%s\n", prevword);	
			cc++;
			
		}
		strcpy(prevorder, worder);
		strcpy(prevword, word);	
			
	}
}
