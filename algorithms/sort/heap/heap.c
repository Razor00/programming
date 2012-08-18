/*
 * =====================================================================================
 *
 *       Filename:  heap.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 13 August 2012 07:42:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madan (), madanpandiri@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#define swap(a, b) { typeof(a) t = a; a = b; b = t;}

int heapify(int arr[], int p, int len)
{
    
    int l, r, min, t;
    while (p <= len) {
        min = p;
        l = 2 * p ;
        r = 2 * p + 1;
        if (l <= len && arr[l] < arr[p])
            min = l;
    
        if (r <= len && arr[r] < arr[min])
            min = r;

        if (min != p) {
            swap(arr[min], arr[p]);
        }
        else
            break;
        p = min;
    }
}


void print(int arr[], int len);

void sort(int arr[], int n)
{
    int i;
    for (i = 1; i <= n; i++) {
        printf("%d\n", arr[1]);
        swap(arr[1], arr[n-i+1]);
        heapify(arr, 1, n-i);
    }
}

void heap(int arr[], int n)
{
    int i;
    for (i = n/2; i >= 1; i--) {
        heapify(arr, i, n);
        print(arr, n);
    }
    sort(arr, n);
}


void print(int arr[], int len)
{
    int i;
    for (i = 1; i <= len; i++) {
        printf("%d - %d \n", i, arr[i]);
    }
    printf("\n===============\n");
}

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
