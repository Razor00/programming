#include<stdio.h>
#include<math.h>

int main()
{
	unsigned int num;
	scanf("%d", &num);
	num = num;
	
	while (1) {
		
		if ( num > 1 ) {
			num = (unsigned int) ceil ((num*1.0)/9);
		}
		else {
			printf(" oley wins \n");
			break;
		}

		
		if ( num > 1 ) {	
			num = (unsigned int) ceil ((num*1.0)/2);
		}
		else {
			printf(" jack wins \n");
			break;	
		}
	}
}
