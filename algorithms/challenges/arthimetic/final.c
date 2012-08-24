#include<stdio.h>
#include<math.h>
#include<stdlib.h>

FILE *in, *out, *err;

int i_can_win(unsigned int num, unsigned int *marks, int *sz, int first_throw)
{
	int i = 0;
	int k = 0;
	int arr[] = {9,2};
	unsigned int win_num = num;
	while (num > 1) {
		//fprintf(err, "%u:arr[%d]= %d\n", num, k, arr[k]);
		num = (unsigned int) ceil((num*1.0)/arr[k]);
		marks[i++] = num;
		k = ((k == 0)?1:0);
		
	}

	// this is work-around for playing both winning and losing
	if ( ceil ((win_num * 1.0) / (9*2)) >= 2 )
		marks[0]--;
	*sz = i;

/*We win if
1. we throw first  and number of iterations above (i) comes odd
2. we throw second and number of iternation above (i) comes even
*/

	if (((i+1) % 2	== 0 && first_throw) || ((i%2 == 0) && !first_throw))
		return 1;

	return 0;
		
		
}

unsigned int tmarks[64];
unsigned int marks[64];

unsigned int get_value(void)
{
	unsigned int value;
	fprintf(err, "Enter the multiple: ");
	scanf("%u", &value);
	return value;

}

unsigned int get_rand(unsigned int low, unsigned high)
{
/*  this formula  (1.0 + 10.0 * (rand() / (RAND_MAX + 1.0))) return values between 1-10,
	then scale this value between low to high
*/

    return low + (1.0 + (unsigned int) (10.0 * ((rand() / (RAND_MAX + 1.0))))) * ((high-low) * 1.0 /(10-1));

}


int win(unsigned int mul, unsigned int num, unsigned int win_num)
{
	
	unsigned int max = ~0;
	unsigned int temp;

	temp = (unsigned int) floor ((max*1.0)/mul);
	
	
/* if the mulitple overflows max value(max interger) then game over */
	if ( num > temp )	
		return 1;
/* if the multipe overflows the target value then game over*/	
	if ( mul * num >= win_num ) 
		return 1;	
	
	return 0;
}



void play(unsigned int *marks, unsigned int win_num, int first_throw, char *name)
{

	int i = 0;
	unsigned int  mul = 1;
	unsigned int lower, upper;
	unsigned int opp_result, my_result =1;

	lower = marks[i];
	upper = marks[i+1];
	fprintf (err, "initial result %-30d\n", my_result);

	if (first_throw) {
		if (win_num >=2 && win_num <= 9) {
			fprintf(err, "%u", win_num);
			fprintf(err, " i win \n");
			exit(0);
		}

		if ((mul = lower) > 9) {
				mul = get_rand(2, 9);
		}
		my_result *= mul;
		fprintf (err, "%-15s: multiply with %d: result: %-30u\n", name, mul, my_result);
		fprintf (out, "%d", mul);
	}

	while (1) {

		mul = get_value();
		opp_result = mul * my_result;

		fprintf(err, "%-15s: multiply with %d: result : %-30u\n", "opp", mul, opp_result);
		
		if (win(mul, my_result, win_num)) {
			return;
		}

		if ( opp_result >= upper )		// this is required if the opposition has chance to win but screws it up
			i += 2;
	
		lower = marks[i];
		upper = marks[i+1];
	
		mul =  (unsigned int) ceil ((lower * 1.0) / opp_result);
		if ( mul > 9 || mul < 2)		// opposition is winning 
			mul = get_rand(2, 9);

		my_result    =   mul * opp_result;
		fprintf (err, "%-15s: multiply with %d: result: %-30u\n", name, mul, my_result);
		fprintf (out, "%d", mul);

		if (win(mul, opp_result, win_num)) {
			fprintf(err, " %s  won \n", name);
			return;
		}
	}	
		

}


int main(int argc, char *argv[])
{
	unsigned int n;
	int first_throw;
	int pos = 0;
	int sz;
	
	int i = 0;
	
	in = stdin;
	out = stdout;
	err = stderr;
	fprintf(stderr, "args = %d\n", argc);
	if (argc == 4) {
		in = fopen(argv[1],"rw");	
		out = fopen(argv[2],"rw");	
		err = fopen(argv[3],"rw");	
		if ( in == NULL || out == NULL || err == NULL ) {
			printf(" the files are invalid \n");
			exit(EXIT_FAILURE);
		}
	}
	if ( argc == 2 ){
		if (!(in = fopen(argv[1],"r"))) {
			printf("invalid input file\n");
			exit(0);
		}
		fscanf (in, "%u", &n);
		fscanf (in, "%d", &first_throw);	
		fclose(in);
		in = stdin;
	}	
	else {
		fscanf (in, "%u\n", &n);
		fscanf (in, "%d\n", &first_throw);	

	}

	fprintf(err, " number is %u : throw is %d %s \n", n, first_throw, (first_throw == 0 )?"opp":"mine");
	
	if ( n < 2  ) { exit(0); }

	tmarks[0] = n;

	
	if (i_can_win(n, tmarks+1, &sz, first_throw)) {
		if (first_throw) 
			pos =  1;
		else	
			pos = 2;
		fprintf(err, " i win \n");
	}
	else {
		if (first_throw)
			pos = 2;
		else
			pos = 1;
		fprintf(err, " i lose \n");
	}
	for ( i = sz; i >= 0; i--){
			fprintf (err, "%u ", tmarks[i]);
			marks[sz - i] = tmarks[i];
	}
	fprintf(err, "\n");
	play(marks+pos, n, first_throw, argv[0]);
//	main();
	return 0;
}
