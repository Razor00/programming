#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int i_can_win(unsigned int num, unsigned int *marks, int *sz, int first_throw)
{
	int i = 0;
	int k = 0;
	int arr[] = {9,2};

	while (num > 1) {
	//	printf("%u:arr[%d]= %d\n", num, k, arr[k]);
		num = (unsigned int) ceil ((num*1.0)/arr[k]);
		marks[i++] = num;
		k = ((k == 0)?1:0);
	}
	*sz = i;

//  number of iterations above (i) comes odd if on first throw then win
// or number of iterations above (i) comes even and second throw
// either cases we win

	if (((i+1) % 2	== 0 && first_throw) || ((i%2 == 0) && !first_throw))
		return 1;

	return 0;
		
		
}

unsigned int tmarks[64];
unsigned int marks[64];

unsigned int get_value(void)
{
	unsigned int value;
	scanf("%u", &value);
	return value;

}

unsigned int get_rand(unsigned int low, unsigned high) 
{
	return (low + (unsigned int) ((high) *1.0* (rand() / (RAND_MAX + low))));
}
void play(unsigned int *marks, unsigned int win_num, int first_throw)
{

	int i = 0;
	unsigned int  mul = 1;
	unsigned int lower, upper;
	unsigned int opp_result, my_result =1;

	lower = marks[i]+1;
	upper = marks[i+1]-1;
	if ( first_throw ) {
		if( win_num >=2 && win_num <= 9 ) {
			printf("%u", win_num);
			printf(" i win \n");
			exit(0);
		}
		my_result = lower;
		if (lower > upper) {
			my_result = lower-1;
		}
		if (  my_result > 9 ) {
				my_result = 4;//get_rand(2, 9);
		}
		printf ("multiply with %u: result: %d\n", mul, my_result);
	}
	while (1) {
		mul = get_value();
		opp_result = mul * my_result;
		printf("opp multipled with %d: result : %u \n", mul, opp_result);
		if ( opp_result >= win_num ) {
			printf(" opponent win \n");
			return;
		}
		if ( opp_result > upper ) 	
			i += 2;
		lower = (marks[i]+1);
		upper = (marks[i+1]-1);
		if ( lower > upper ) 
			lower--;
	
		printf(" lower = %u higher= %u \n", lower, upper);	
		mul =  (unsigned int) ceil ((lower*1.0)/opp_result);
		if ( mul > 9 || mul < 2) 
			mul = 3;//get_rand(2, 9);

		my_result    =   mul * opp_result;
		printf ("multiply with %u: result: %u\n", mul, my_result);
		if ( my_result >= win_num ) {
			printf(" i won \n");
			return;
		}
	}	
		

}


int main()
{
	unsigned int n;
	int first_throw;
	int pos = 0;
	int sz;
	
	int i = 0;

	scanf ("%u", &n);
	scanf ("%u", &first_throw);	
	if ( n < 2  ) { exit(0); }
	tmarks[0] = n;
	if (i_can_win(n, tmarks+1, &sz, first_throw)) {
		if( first_throw) 
			pos =  1;
		else	
			pos = 2;
//		printf(" i win \n");
	}
	else {
		if ( first_throw)
			pos = 2;
		else
			pos = 1;
//		printf(" i lose \n");
	}
	for ( i = sz; i >= 0; i--){
			printf ("%u ", tmarks[i]);
			marks[sz - i] = tmarks[i];
	}
	printf("\n");
	play(marks+pos, n, first_throw);
	main();
	return 0;
}
