#include<stdio.h>
#define COMPWIN 1
#define DRAW	0
#define HUMANWIN -1
#define EMPTY	  8 
#define HUMANMOVE 3
#define COMPMOVE  5
#define H  HUMANMOVE
#define C  COMPMOVE
#define E  EMPTY

int findCompMove(int BOARD[], int *pos , int *value);
int findHumanMove(int BOARD[], int *pos , int *value);

int Win(int BOARD[], int *pos, int val)
{
	int i;
	val = val * 2 + EMPTY;
	for( i = 0; i <=6; i=i+3) {
		if( (BOARD[i]+ BOARD[i+1] + BOARD[i+2]) == val){
			if( BOARD[i] == EMPTY )
				*pos= i;
			else
			if( BOARD[i+1] == EMPTY )
				*pos= i+1;
			else
			if( BOARD[i+2] == EMPTY )
				*pos= i+2;
		}
	}		
	for( i = 0; i <=2 ; i++) {
		if( (BOARD[i]+ BOARD[i+3] + BOARD[i+6]) == val){
			if( BOARD[i] == EMPTY )
				*pos= i;
			else
			if( BOARD[i+3] == EMPTY )
				*pos= i+3;
			else
			if( BOARD[i+6] == EMPTY )
				*pos= i+6;
		}
	}		
	if( (BOARD[0]+ BOARD[4] + BOARD[8]) == val){
			if( BOARD[0] == EMPTY )
				*pos= 0;
			else
			if( BOARD[4] == EMPTY )
				*pos= 4;
			else
			if( BOARD[8] == EMPTY )
				*pos= 8;
	}
	if( (BOARD[2]+ BOARD[4] + BOARD[6]) == val){
			if( BOARD[2] == EMPTY )
				*pos= 2;
			else
			if( BOARD[4] == EMPTY )
				*pos= 4;
			else
			if( BOARD[6] == EMPTY )
				*pos= 6;
	}
	if( *pos == -1 )
		return 0;
	else
		return 1;
}

int BOARDFULL(int BOARD[])
{
	int i;
	for(i = 0; i < 9; i++) {
		if( BOARD[i] == EMPTY )
			return 0;
	}
	return 1;
}


int findCompMove(int BOARD[], int *pos , int *value)
{
	int i, dc, response;
	*pos = -1;
	if( Win(BOARD, pos, COMPMOVE) ) {
		*value = COMPWIN;
		return 1;
	}
	else
	if( BOARDFULL(BOARD) ) {
		*value = DRAW;
		return 2;
	}
	else {
		*value = HUMANWIN;
		
		for( i = 0; i < 9 && *value != COMPWIN; i++){
			if( BOARD[i] == EMPTY ) {
				BOARD[i] = COMPMOVE;
				findHumanMove(BOARD, &dc, &response);
				BOARD[i] = EMPTY;
				if( response > *value ) {
					*value = response;
					 *pos = i;
				}
			}
		}
	} 
	return 3;
}


int findHumanMove(int BOARD[], int *pos , int *value)
{
	int i, dc, response;
	*pos = -1;
	if( Win(BOARD, pos, HUMANMOVE)){
		*value = HUMANWIN;
		return 1;
	}
	else
	if( BOARDFULL(BOARD) ) {
		*value = DRAW;
		return 2;
	}
	else {
		*value = COMPWIN;
		
		for( i = 0; i < 9 && *value !=  HUMANWIN; i++){
			if( BOARD[i] == EMPTY ) {
				BOARD[i] = HUMANMOVE;
				findCompMove(BOARD, &dc, &response);
				BOARD[i] = EMPTY;
				if( response < *value ) {
					*value = response;
					 *pos = i;
				}
			}
		}
	
	} 
	return 3;
}


void print(int arr[])
{
	int i = 0;
	char ch[3] = {'H',' ','C'};
	for(i = 0; i <=6 ; i=i+3){
		printf("\n __  __  __ \n");
		printf("| %c | %c | %c |", ch[(arr[i]-3)%4], ch[(arr[i+1]-3)%4], ch[(arr[i+2]-3)%4]);
	}		
	printf("\n __  __  __ \n\n");
}


int main()
{
	int BOARD[9]={E,E,E,E,E,E,E,E,E};
	int pos, value;
	int hmove;
	int input;
	printf("Select the turn \n");
	printf(" 1: computer\n");
	printf(" 2: Human\n");
	print(BOARD);
	scanf("%d", &input);;	
	if( input == 1 ){
//		int result = findCompMove(BOARD, &pos, &value);
		BOARD[4] = COMPMOVE;
		print(BOARD);
	}
	while(1){
		printf("Enter move no: \t");
		while(1){
			if( !BOARDFULL(BOARD) ) {
				scanf("%d", &hmove);
				hmove--;
			}
			else{
				printf(" Game draw \n");
				exit(0);
			}

			if( BOARD[hmove] != EMPTY )
				printf("Invalid entry Please enter again\n");
			else
				break;
		}
		BOARD[hmove] = HUMANMOVE;
		int result = findCompMove(BOARD, &pos, &value);
		printf("pos = %d\n", pos);
		BOARD[pos] = COMPMOVE;
		print(BOARD);

		if( result == 1) {
			printf("**********Computer Won**************\n");
			break;
		}
		else
		if( result == 2 ) {
			printf("**********Draw ***************\n");
			break;
		}
		if( result == 3 && value == HUMANWIN ) {
			printf("***********You Won*************\n");
			break;
		}
	}
}
