#include<stdio.h>
int *arr=0;
void compute_phi(char* str)
{
	static int  j=3;
	int i, l;
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
	for( i = 1; i <slen; i++ )
		printf("%2d ",	arr[i]);
	printf("\n");
	
}

	
	
int main()
{
	char pattern[30];
	char text[200];
	int i;
	char ch[2];
	pattern[0] = '0';
	printf("Pattern = ");
	scanf("%s", &pattern[1]); 
	while(ch[0] != EOF){
		arr = (int *) realloc( arr,  (sizeof(int) * (strlen(pattern)+1) ) );
		compute_phi(pattern);
		i = strlen(pattern);
		printf("\nA character: ");
		scanf("%s", ch);
		pattern[i] = ch[0];
		pattern[i+1] = '\0';
	}
}
