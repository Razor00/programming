#include<stdio.h>
#define COMPUTERWIN  4
#define HUMANWIN     5	

void findCompMove(int , int *pos , int *value);
void findHumanMove(int , int *pos , int *value);

void findCompMove(int Total, int *taken, int *value)
{
	int i, dc, response;
	int tmax, max;
	if( *taken == -1) {
		*taken = Total;	
		tmax = 0;
	}
	else{
		tmax = 2 * (*taken) * (*taken);
	}
	max = (int)((sqrt(1 + 8 * (*taken))-1)*1.0/2);	

	if( tmax >= Total ) {
		*value = COMPUTERWIN;
		*taken = Total;
		return;
	}
	else {
		*value = HUMANWIN;
	
		for( i = max; i >=1; i--){
			dc = i;
			findHumanMove(Total-i, &dc, &response);
			if( response == COMPUTERWIN) {
				*value = response;
				*taken = i;
				return;
			}
		}
		
	} 
	*taken = 1;
}

void findHumanMove(int Total, int *taken, int *value)
{
	int i, dc, response;
	int  max = (int)((sqrt(1 + 8 * (*taken))-1)*1.0/2);	
	int  tmax = 2 * (*taken) * (*taken);
	if( tmax >= Total ) {
		*value = HUMANWIN;
		*taken = Total;
		return;
	}
	else {
		*value = COMPUTERWIN;
		
		for( i = max; i >=1; i--){
				dc = i;
				findCompMove(Total-i, &dc, &response);
				if( response == HUMANWIN) {
					*value = response;
					*taken = i;
					return;
				}
		}
				
	} 
	*taken = 1;
}




int main()
{
	int pos, value;
	int Total;
	int wmove;
	printf(" select 1:COMPUTER :2:HUMAN:  ");
	scanf("%d", &wmove);	
	printf("Total = ");
	scanf("%d", &Total);
	pos = Total-1;
	if( wmove == 1 ) {
		pos = -1;
		findCompMove(Total, &pos, &value);
		Total -= pos;
	}
	printf("Total remaining = %d***Your turn: range: 1 - %d:\t", Total, pos);
	scanf("%d", &pos);
	Total = Total - pos;
	while(1) {	
		if( Total == 0 ){
			printf("You won\n");
			break;
		}

		findCompMove(Total, &pos, &value);
		printf("computer taken = %d and the value %d\n", pos, value);

		Total = Total - pos;		
		if( Total == 0 ){
			printf(" Computer won\n");
			break;
		}

		printf("Total remaining = %d***Your turn: range: 1 - %d:\t", Total, 2*pos*pos);
		scanf("%d", &pos);
		Total = Total - pos;
	}
}
