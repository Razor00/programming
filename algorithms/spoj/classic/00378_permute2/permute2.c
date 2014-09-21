#include <stdio.h>
int ambiguous(int *arr, int n)
{
    int i;
    /*we do not use 0 and n+1 */
    arr[0]   = 0;
    arr[n+1] = 0; 
    i = 1;
    while (arr[arr[i]] == i)
        i++;
    return (i == n+1);

}
int main()
{
    int t, i;
    int arr[100000 + 100];
    
    scanf("%d", &t);
    while (t) {

        for (i = 1; i <= t; i++)
           scanf("%d", &arr[i]); 

        if (ambiguous(arr, t)) 
            printf("ambiguous\n");
        else
            printf("not ambiguous\n");

        scanf("%d", &t);
    }
    return 0;
}

