#include<stdio.h>
#include<math.h>

enum {
	MINE =1,
	OPPONENT
};
int main()
{
	unsigned int num;
	unsigned int nxt_margin;
	int turn = 0;
	
	scanf("%d", &num);
	
	nxt_margin = num;
	
	while (1) {
		
		if ( nxt_margin > 1 ) {
//			turn = MINE;
			nxt_margin = (unsigned int) ceil ((nxt_margin*1.0)/9);
#if defined(DEBUG)
			printf ("mine: %u \n", nxt_margin);
#endif
		}
		else {
			printf(" I win \n");
			break;
		}

		
		if ( nxt_margin > 1 ) {	
//			turn = OPPONENT;
			nxt_margin = (unsigned int) ceil ((nxt_margin*1.0)/2);
#if defined(DEBUG)
			printf ("opp:%u \n", nxt_margin);
#endif
		}
		else {
			printf(" Opponent win \n");
			break;	
		}
	}
}
/*
	if ( turn == MINE ) {
		if ( nxt_margin == 1 ) 
			printf(" I win \n");
		else
			printf(" Opponent win \n");

	}	
	else 
	if( turn == OPPONENT ) {
		if ( nxt_margin == 1 ) 
			printf(" Opponent win \n");
		else
			printf(" I win \n");
	}	
*/
}
