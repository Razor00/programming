#include<stdio.h>
int *arr=0;
void compute_phi(char* str)
{
	static int j = 3;
	int i, k=0, l;
	int matched;
	int slen = strlen(str);
	arr[0] = 0;
	arr[1] = 0;
	if( str[1] == str[2] )
		arr[2] = 1;
	else
		arr[2] = 0;
	while(j < slen) {
		matched = -1;
		l =  arr[j-1]; i = l + 1;
		if( str[l] == str[j] )
			matched = l;		
		if( str[i] == str[j] )
			arr[j] = i;
		else
		if( matched != -1 )
			arr[j] = matched;
		else
			arr[j] = 0;
		j++;
	}	


	for( i = 1; i < slen; i++ )
		printf("%2c ",	str[i]);
	printf("\n");
	for( i = 1; i <=slen; i++ )
		printf("%2d ",	arr[i]);
	printf("\n");
	
}

void match(char * text, char * pattern)
{
	int i = 1;
	int j = 1;
	int s = 1;
	int lenpattern = strlen(pattern) - 1;
	while(1) {
		j = arr[j]+1;
		if( i  > strlen(text) )
			break;
		while( j <= lenpattern ) {
			if( text[i] != pattern[j] )
				break;
			i++; j++;
		}	
		if( j == (lenpattern+1) ) {
			j--;
			printf("pattern matched at %d up to %d\n", s, i-1);
			sleep(3);
			getc(stdin);
		}
		else {
			if( j == 1 )
				i++;
			else
				j--;
		}
		
		s = s + j - arr[j];
	//	printf("The value of i = %d  j = %d arr[j] = %d  s = %d \n", i, j, arr[j]+1, s );
	}
}		
	
	
int main()
{
	char pattern[30];
	char text[200];
	int i;
	int ch;
	pattern[0] = '0';
	printf("Pattern = ");
	scanf("%s\n", &pattern[1]); 
	arr = (int *)malloc(sizeof(char) *  (strlen(pattern) + 1) );
	compute_phi(pattern);
	text[0] = '0';
	scanf("%s", &text[1]);
	for( i = 1; i<=strlen(&text[1]); i++)
		printf("%2d ",i);
	printf("\n");
	for( i = 1; i<=strlen(&text[1]); i++)
		printf("%2c ", text[i]);
	printf("\n");
	for( i = 1; i<=strlen(&pattern[1]); i++)
		printf("%2c ", pattern[i]);
	printf("\n");
	while(1) {
		match(text, pattern);
		printf("\n\n\n ");
		int retval;
		int i=1;
		int ch;
		ch = getc(stdin);
		if( ch == EOF)
			break;
		while(ch!='\n' && ch != EOF ){
			text[i++] = ch;
			ch = getc(stdin);
		}
			
		text[i]='\0';
		printf("%s\n", &text[1]);
		if( retval < 0 ){
			printf("finished\n");
			break;
		}
	}
}
