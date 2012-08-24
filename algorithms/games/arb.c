#include<stdio.h>
#define COMPUTERWIN  4
#define HUMANWIN     5	

int findCompMove(int , int *pos , int *value);
int findHumanMove(int , int *pos , int *value);

int findCompMove(int Total, int *taken, int *value)
{
	int i, dc, response;
	int  max = (int)((sqrt(1 + 8 * (*taken))-1)*1.0/2);	

	if( max >= Total ) {
		*value = COMPUTERWIN;
		*taken = Total;
		return 1;
	}
	else {
		*value = HUMANWIN;
		
		for( i = 1; i <= max; i++){
				dc = i;
				findHumanMove(Total-i, &dc, &response);
				if( response == COMPUTERWIN) {
					*value = response;
					*taken = i;
					return 2;
				}
		}
		
	} 
	*taken = 1;
	return 3;
}

int findHumanMove(int Total, int *taken, int *value)
{
	int i, dc, response;
	int  max = (int)((sqrt(1 + 8 * (*taken))-1)*1.0/2);	
	if( max >= Total ) {
		*value = HUMANWIN;
		*taken = Total;
		return 1;
	}
	else {
		*value = COMPUTERWIN;
		
		for( i = 1; i <= max; i++){
				dc = i;
				findCompMove(Total-i, &dc, &response);
				if( response == HUMANWIN) {
					*value = response;
					*taken = i;
					return 2;
				}
		}
				
	} 
	*taken = 1;
	return 3;
}




int main()
{
	int hmove;
	int input;
	int pos, value;
	int result ;
	int Total;
	printf("Total = ");
	scanf("%d", &Total);
	while(1) {	
		printf("Total remaining = %d***Your turn\n", Total);
		scanf("%d", &pos);
		Total = Total - pos;
		if( Total == 0 )
			printf("You won\n");
		result = findCompMove(Total, &pos, &value);
		Total = Total - pos;		
		if( Total == 0 )
			printf(" Computer won\n");
			printf("computer taken = %d and the value %d\n", pos, value);
		}
}
/*		if( result == 1) {
			printf("**********Computer Won**************\n");
			break;
		}
		else
		if( result == 2 ) {
			printf("**********future***************\n");
		}
		if( result == 3 && value == HUMANWIN ) {
			printf("***********You Won*************\n");
	//		break;
		}
	}
}*/
