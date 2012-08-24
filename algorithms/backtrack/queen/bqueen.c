#define n 8 
int x[n+1];

void print()
{
	int i;
	int j;
	static int times=0;
	printf(" the order is = %d\n", times++);
	for(i=n; i>= 1; i-- ){
		printf("\n");
		for( j = 1; j <=n; j++)
			printf("----");
		printf("\n");
		printf("|");
		for(j=1;j<x[i];j++)
			printf("   |");
		printf(" Q |");
		for(j=x[i]+1; j <=n; j++)
			printf("   |");
	}  
	printf("\n");
	for( j = 1; j <=n; j++)
		printf("----");
	printf("\n");
	for(i=1;i<=n;i++)
		printf(" %d\t", x[i]);
	printf("\n");
}

int valid(int r, int val)
{
	int ri;
	int ci;
	for(ri = 1; ri < r; ri++){
		if( x[ri] == val )
			return 0;
	}
	ri = r;
	ci = val;
	while(--ri >= 1 && --ci >=1 ){
		if( x[ri] == ci )
			return 0;
	}
	ri = r;
	ci = val;
	while(--ri >=1 && ++ci <=n ){
		if( x[ri] == ci )
			return 0;
	}
	return 1;
}
	
int main()
{
	int val = 1;
	int k = 1;
	while(k){

		if( valid(k, val) ) {
			x[k] = val;
			k++;
			val = 1;
		}
		else{
			val++;
		}

		if( k == (n+1) ) {
			print();
			k--;
			val = x[k]+1;
		}		
		while(val == (n+1)){
			k--;
			val = x[k]+1;
		}
	}
}
