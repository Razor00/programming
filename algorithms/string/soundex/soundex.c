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
	int k;
	int pos;
	int ch;
	char str[30];
	char tstr[30];
	while(1) {
		if( scanf("%s",str) == -1)
			break;
		tstr[0] = tolower(str[0]);
		k = 1;
		for( i = 1 ;i < strlen(str); i++ ) {
			pos = str[i] - 'A';
			ch  =  alphabet[pos].val;
			if( (ch != '0') && (ch != tstr[k-1]) ) 
				tstr[k++] = ch;
		}
		for(i=k;i<=3;i++)
			tstr[i] = '0';

		tstr[4]='\0';	
		printf("%s\t%s\n", tstr, str);	
	}
	
}
