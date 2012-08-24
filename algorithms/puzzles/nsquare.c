#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int startpos(int n)
{
	float l  = log(n)/log(2);
	if( (int)ceil(l) - (int)floor(l) == 0 )
		return n;
	else
		return( pow(2, (int)floor(l)) - n );
}

int calpos(int n)
{
	int lend, rend;
	int val;
	int pos;
//	static int e
	float r = ((sqrt( 8*n + 1 ) - 1)*1.0)/4;
	lend = (int)floorf(r);
	rend = (int)ceilf(r);
	val = startpos(lend);
	pos = (val + n - (2 * lend * lend + lend)) % rend;
	if( pos == 0 )
		pos = 1+(int) (3.0*rand()/(RAND_MAX+1.0));
	return pos;
}

int main()
{
	int count = 40;
//	int remcount = count;
//	while(remcount){
	while(scanf("%d",&count) != - 1)
		printf("%d\n",	calpos(count));
		
}
