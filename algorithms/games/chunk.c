#include<stdio.h>
#include<string.h>
int  MIN = 1;
int  MAX = 4; 
#define COMPUTERWIN  4
#define HUMANWIN     5	

void findCompMove(int , int *pos , int *value);
void findHumanMove(int , int *pos , int *value);

void findCompMove(int Total, int *taken, int *value)
{
	int i, dc, response;
	int tmax, max;

	if(  Total <= MAX ) {
		*value = COMPUTERWIN;
		*taken = Total;
		return;
	}
	else {
		*value = HUMANWIN;
	
		for( i = MAX; i >=MIN; i--){
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
	if( Total <= MAX ) {
		*value = HUMANWIN;
		*taken = Total;
		return;
	}
	else {
		*value = COMPUTERWIN;
		
		for( i = MAX; i >=MIN; i--){
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
	int  ch;
	printf("Select Initial Total = \t");
	scanf("%d", &Total);
	
	printf("Do u want to select max value : ");
	/*scanf("%d", &ch);
	scanf("%d", &ch);
	printf("%d\n",ch);*/
	ch = 'y';
		
	if( ch == 'y' || ch == 'Y' ){
		printf("\n Select the max value:  ");
		scanf("%d", &MAX);
	}
	printf(" TOTAL = %d \t MAX VALUE: %d \t MIN VALUE = %d\t  \n", Total, MAX, MIN);
	printf("\n\n select 1:COMPUTER :2:HUMAN:\t");
	scanf("%d", &wmove);	

	if( wmove == 1 ) {
		findCompMove(Total, &pos, &value);
		Total -= pos;
		if( Total == 0 ){
			printf(" Computer won\n");
			exit(0);
		}
	}
	printf("Total remaining = %d***Your turn:", Total);
	do {
		scanf("%d", &pos);
		printf("You took: \t");
	}while( pos<MIN || pos>MAX );
	printf("\n");
	Total -= pos;
	while(1) {	
		if( Total == 0 ){
			printf("You won\n");
			break;
		}

		printf("Total remaining = %d***Computer Turn:\n", Total);
		findCompMove(Total, &pos, &value);
		printf("computer taken = %d \n", pos);

		Total -=  pos;		
		if( Total == 0 ){
			printf(" Computer won\n");
			break;
		}

		printf("Total remaining = %d***Your turn: ", Total);
		do {
			scanf("%d", &pos);
			printf("You took: \t");
		}while( pos<MIN || pos>MAX );
		printf("\n");
		
		Total -=  pos;
	}
}
