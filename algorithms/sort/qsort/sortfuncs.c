#include<stdlib.h>
inline swap(int *a, int *b)
{
        int c;
        c = *a;
        *a = *b;
        *b = c;
}

int partition(int arr[], int n)
{
        if( n == 1 ) return 0;

        srand(n);
        int i= 1;
        int j= n - 1;
        int pivot =  (int) ((n-1)*1.0*rand()/(RAND_MAX+1.0));
        //printf("the pivot= %d is %d\n", pivot, arr[pivot]);
        swap(&arr[0], &arr[pivot]);

        while(j > i) {
                while((arr[i] < arr[0]) && ( j > i ))
                        i++;
                swap(&arr[i], &arr[j]);
                j--;
        }

        if( arr[i] >  arr[0] )
                i--;
        swap(&arr[0], &arr[i]);

        return(i);
                                                                                                                             
}

