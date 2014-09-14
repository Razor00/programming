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


/*max prime <= 32000; as max is 1000,000,000*/

int num[32000];
int min_st_pos  = 0;
int max_end_pos = 0;

#define GET_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
static inline int isprime(int n)
{
    int i, c;
    c = sqrt(n);
    for (i = 2; i <= c; i++){
        if ((n%i) == 0) 
            return 0;
    }
    return 1;
}


void generate_primes()
{
    int i, l;
    for (i = 2, l = 0; i < GET_SIZE(num); i++) {
        if (isprime(i))
            num[l++] = i;
    }
    max_end_pos = l-1;
}

int static inline aprime(n)
{
    int l;
    int last = sqrt(n);
    for (l = min_st_pos; num[l] <= last && l <= max_end_pos; l++) {
        if ((n%num[l]) == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int tn;
    int a, b;
    int i;
    scanf("%d", &tn);
    generate_primes();
    while (tn--) {
        scanf("%d %d", &a, &b);
        if (a == 1)
            a = 2;

        for (i = a; i <= b; i++){
            if (aprime(i))
                printf("%d\n", i);
        }
        printf("\n");
    }
}
