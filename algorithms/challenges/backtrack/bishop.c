#include<stdio.h>
#include<stdlib.h>

#define CHECK_PTR(PTR) { if(!PTR) { perror("Error in allocating memory ");\
				exit(EXIT_FAILURE); \
				} \
			}


inline int min(int a, int b)
{
	return(a>b?b:a);
}


int gsqr;
int lastpos;
int total=0;
int *LDARR, *RDARR, *LUARR, *RUARR;
	
int collision(int *arr, int curpos)
{
	
	int i;
	int cpos;
	int LD, RD, LU, RU;	
	int row, col;

	
	/* left down  */
	cpos = curpos;
	i =  gsqr + 1;	
	LD =  LDARR[cpos];
	while( LD-- ){
		if( arr[cpos-i] == 1 )
			return 1;
		cpos -= i;
	}
		

	/* right down 
	   remaining columns to the right */
	cpos = curpos;
	i =  gsqr - 1;
	RD =  RDARR[cpos];
	while( RD--  ) {
		if( arr[cpos-i] == 1 ) 
			return 1;
		cpos -= i;
	}
	
	
	/*  up left   */
	cpos = curpos;
	i =  gsqr - 1;	
	LU = LUARR[cpos];
	while( LU--){ 
		if( arr[cpos+i] == 1 ) 
			return 1;
		cpos += i;
	}

	/*  up right 	
	*/

	cpos = curpos;
	i =  gsqr + 1;	
	RU = RUARR[cpos];
	while(RU--){ 
		if( arr[cpos+i] == 1 ) 
			return 1;
		cpos += i;
	}
	
	return 0;
}	

void bishop(int *arr, int curpos, int nbsp)
{
	
	int i;
//	int j,k;
	
	if( nbsp == 0 ){
/*		if( curpos < lastpos){
			for(j=0;j<gsqr;j++){
				for(k=0;k<gsqr;k++)
						printf("%d ",arr[j*gsqr+k]);
				printf("\n");
			}
			printf("-------------\n");		
		}
*/
		total++;
		return;
	}	

	for(i = curpos; i < lastpos; i++){
		if( !collision(arr, i) ){
			arr[i] = 1;
			bishop(arr, i+1, nbsp-1);
		}
		arr[i] = 0;
	}	
}

int main()
{
	int *arr, bsp;
	int i;
	int tno;
	int row, col;
	printf(" Number of squares (order): ");
	scanf("%d", &gsqr);
	lastpos = tno  = gsqr * gsqr;
	arr  = calloc(tno, sizeof(*arr));
	LDARR = calloc(tno, sizeof(*LDARR));
	RDARR = calloc(tno, sizeof(*RDARR));
	LUARR = calloc(tno, sizeof(*LUARR));
	RUARR = calloc(tno, sizeof(*RUARR));
	CHECK_PTR(arr);
	CHECK_PTR(LDARR);
	CHECK_PTR(RDARR);
	CHECK_PTR(LUARR);
	CHECK_PTR(RUARR);

	for(i = 0; i < tno; i++){
		row =	i / gsqr; 
		col =	i % gsqr;	
		LDARR[i] = min(row, col);
		RDARR[i] = min(row, gsqr-col-1);
		LUARR[i] = min(gsqr-row-1 , col);
		RUARR[i] = min(gsqr-row-1 , gsqr-col-1);
	}

	printf(" Number of bishops : ");
	scanf("%d", &bsp);
	bishop(arr, 0,  bsp);
	printf(" bishops placed = %d \n", total);
}

