/*
 * =====================================================================================
 *
 *       Filename:  second_max.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/13/2012 11:44:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan (), madanpandiri@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int count;
    int *arr;

    scanf("%d", &count);
    arr = malloc(sizeof(int) * count);
    int i = 0;
    int first = -1, second = -1;
    while (count--) {
        scanf("%d", &arr[i]);
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        }
        else {
            if (arr[i] > second)
                second = arr[i];
        }
        i++;
    }
    printf("\n%d\n", first);
    printf("\n%d\n", second);
}

