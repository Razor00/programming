/*Starting from point (0,0) on a plane, we have written all non-negative integers 0, 1, 2,... 
 * as shown in the figure. For example, 1, 2, and 3 has been written at points (1,1), (2,0), 
 * and (3, 1) respectively and this pattern has continued.
 */

#include <stdio.h>

int main()
{
   
    int tn;
    int a, b, t, off, v;
    scanf("%d", &tn);
    while (tn--) {
        scanf("%d %d", &a, &b); 
        //printf("===got : %d %d\n", a, b);
        off = 0;
        if (a%2 != 0) 
            off = 1;

        t = a/2 - 1;
        if (a == b+2){
            v = 4*t+2+off;
            printf("%d\n", v);
        } 
        else if (a == b) {
            v = 4*t+2+2+off;
            printf("%d\n", v);
        }
        else {
            printf("No Number\n");
        }
    } 
    return 0;
}
