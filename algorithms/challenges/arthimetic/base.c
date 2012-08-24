#include<stdio.h>
#include<math.h>

int i_can_win(unsigned int num, unsigned int *marks, int *sz)
{
	int i = 0;

	while (1) {
		
		if ( num > 1 ) {
			num = (unsigned int) ceil ((num*1.0)/9);
			marks[i++] = num;
		}
		else{ 
			*sz = i;
			return 0;
		}
		
		
		if ( num > 1 ) 	{
			num = (unsigned int) ceil ((num*1.0)/2);
			marks[i++] = num;
		}
		else {
			*sz = i;
			return 1;
		}
	}
}

unsigned int marks[64];

int main()
{
	unsigned int n;
	int pos = 0;
	int sz;
	
	scanf ("%u", &n);
	marks[0] = n;
	if (i_can_win(n, (marks+1), &sz)) {
		pos = 1;

		printf(" : i win \n");
	}
	else
		printf(": other win \n");
	
	int i;
	for (i = sz; i >= 0; i--) {
		printf("%u  ", marks[i]);
	}
	printf("\n");
	return 0;
}
