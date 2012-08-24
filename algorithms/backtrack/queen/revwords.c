#include<stdio.h>
int main()
{
	void reverse(char *sptr,char *eptr)
	{
		char ch;
		while(sptr < eptr){
			ch = *eptr;
			*eptr = *sptr;
			*sptr = ch;
			sptr++;
			eptr--;
		}
	}
	char *data=0;
	size_t sz;
	getline(&data, &sz, stdin);
	sz = strlen(data);
	sz--;
	data[sz] = '\0';
//	printf(" ret sz = %d the slen = %d\n", sz, strlen(data));
//	puts(data);
	reverse(data, data+sz-1);
	puts(data);
	char *sptr, *eptr;
	char *ptr = data;
	while(1){
		sptr = ptr;
		while( *ptr != '\0' &&	*ptr != ' ' )
			ptr++;
		eptr = ptr-1;	
		reverse(sptr,eptr);
		if( *ptr == '\0' )
			break;
		ptr++;
	}
	puts(data);
	free(data);
	
}
