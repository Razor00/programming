 /*You are asked to calculate factorials of some small positive integers.
Input

An integer t, 1<=t<=100, denoting the number of testcases, followed by t
lines, each containing a single integer n, 1<=n<=100.  Output

For each integer n given at input, display a line with the value of n!
Example Sample input:

4 1 2 5 3

Sample output:

1 2 120 6 */

#include <stdio.h>
int main()
{
    int tn, n, t, p, i, l, s, j;
    int c[200];
   
    scanf("%d", &tn); 
    while (tn--) {
        scanf("%d", &n);
        l = 1;
        s = 0;
        c[0] = 1;
        for (p = 2; p <= n; p++) { 
            i = 0;
            while (i < l) {
                t = c[i] * p + s;
                c[i++] = t%10;
                s = t/10;
            }
            while (s) {
                c[i++] = s%10;
                s = s/10;
            }
            l = i;
#if 0
            printf("%d:", l);
            for (i = l-1; i >= 0; i--) {
                printf("%d", c[i]);
            }
            printf("\n");
#endif 
        }
        for (i = l-1; i >= 0; i--) {
            printf("%d", c[i]);
        }
        printf("\n");
    }
}

