#include<stdlib.h>
#include<stdio.h>
int read(int **arr)
{
        int INITIAL_SZ = 10;
        int i=0;
        int ch = 0;
        int CURSZ=0;
	*arr = 0;
        while(1) {
                if ( scanf("%d", &ch) == -1 )
			break;
//		printf(" data read : =%d\n", ch);
                if( i == CURSZ) {
                        *arr = (int *) realloc(*arr, (CURSZ + INITIAL_SZ)* sizeof(int));
                        CURSZ = CURSZ  + INITIAL_SZ;
                }
                (*arr)[i++] = ch;
        }
/*	int j;
	for( j = 0; j < i ; j++ )
		printf(" %d\t", (*arr)[j]);
	printf("\n");*/
        return(i);
}

