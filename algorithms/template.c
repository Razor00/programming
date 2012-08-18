#include <stdlib.h>
#include <stdio.h>

int main()
{
    int count;
    int *arr;
    int i;
    scanf("%d", &count);
    arr = malloc(sizeof(*arr) * (count+1));

    for (i = 1; i <= count; i++)
        scanf("%d", arr+i);
    
    heap(arr, count);
}
