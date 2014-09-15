/*2. Prime Generator Problem code: PRIME1

Peter wants to generate some prime numbers for his cryptosystem. Help him! Your
task is to generate all prime numbers between two given numbers!  Input

The input begins with the number t of test cases in a single line (t<=10). In
each of the next t lines there are two numbers m and n (1 <= m <= n <=
1000000000, n-m<=100000) separated by a space.  Output

For every test case print all prime numbers p such that m <= p <= n, one
number per line, test cases separated by an empty line.  Example

Input: 2 1 10 3 5

Output: 2 3 5 7

3 5 */

#include <stdio.h>
#include <string.h>
#include <math.h>

static inline int isprime(int n, int *div)
{
    int i, c;
    c = sqrt(n)+1;
    for (i = 2; i <= c; i++)
        if (n%i == 0) {
            *div  = i;
            return 0;
        }
    return 1;
}

#define GET_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
int main()
{
    int tn;
    int a, b, c;
    int i, j, l;
    char arr[100000+5];
    scanf("%d", &tn);

    int num[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    while (tn--) {
        scanf("%d %d", &a, &b);
        if (a == 1)
            a = 2;

        memset(arr, 1, b-a+1);
#if 0
        for (l = 0; l < GET_SIZE(num); l++) {
            for (i = a; i <= b; i++){
                if (i > num[l] && i%num[l] == 0)
                    for (j = i-a; j <= b-a; j += num[l]) 
                        arr[j] = 0;
                if (i == num[l])
                    arr[i-a] = 2;
            }
        }
#endif
        int div;
        int start = 0;
        int incr  = 0;
        for (i = 0; i <= (b-a); i++){
            if (!arr[i])
                continue;
            if (arr[i] == 1) {
                start = a + i;
                if (isprime(i+a, &div)){
                    //printf("%d\n", a+i);
                    incr = a+i;
                    start = (a+i)<<1;
                }
                else 
                    incr = div;

                for (j = start; j <= b; j += incr) 
                    arr[j-a] = 0;
            }
     //       else {
       //         printf("%d\n", a+i);
         //   }
        }
        for (i = 0; i <= (b-a); i++)
            if (arr[i])
                printf("%d\n", a+i);
        printf("\n");
    }
}
