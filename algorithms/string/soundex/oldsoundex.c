struct Alphabet {
	char ch;
	char val;
};


static struct Alphabet alphabet[58] = {
'A','0','B','1','C','2','D','3','E','0','F','1','G','2','H','0','I','0','J','2','K','2','L','4','M','5','N','5','O','0',
'P','1','Q','2','R','6','S','2','T','3','U','0','V','1','W','0','X','2','Y','0','Z','2',
'[','0','\\','0',']','0','^','0','_','0','`','0',
'a','0','b','1','c','2','d','3','e','0','f','1','g','2','h','0','i','0','j','2','k','2','l','4','m','5','n','5','o','0',
'p','1','q','2','r','6','s','2','t','3','u','0','v','1','w','0','x','2','y','0','z','2',};

int main()
{
	int i;
	int k =1;
	int pos;
	char str[20];
	char tstr[20];
/*	for( i = 0; i < sizeof(alphabet)/sizeof(struct Alphabet); i++)
		printf("%c - %c\n", alphabet[i].ch,alphabet[i].val);*/
	scanf("%s",str);
	tstr[0] = str[0];
	for( i = 1 ;i < strlen(str); i++ ) {
		pos = str[i] - 'A';
		str[i] =  alphabet[pos].val;
		if( (str[i] != '0') && (str[i] != tstr[k-1]) ) 
			tstr[k++] = str[i];
	}
//	tstr[k] = '9'; 
//	tstr[k]='\0';
	/*puts(tstr);
	i = 1;
	int p = 1;
	str[0] = tstr[0];
	while( i < k ) {
		str[p++] = tstr[i];
		while( (tstr[i] == tstr[i+1]) && ( i < k ))
			i++;
		i++;
	}
	printf("After processing\n");
	puts(str);*/
	for(i=k;i<=3;i++)
			tstr[i] = '0';

	tstr[4]='\0';	
//		printf("pos = %d -- %c\n", pos, pos+'A');
//		printf("%c-%c\n", alphabet[pos].ch, alphabet[pos].val);
	puts(tstr);	
	
	puts(str);
}
