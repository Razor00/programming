#include <stdio.h>
#include <math.h>
#include <string.h>

int primes[100];
int max_end_pos;

struct factors {
    int num;
    int count;
};
struct factors dfact[30];
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
    int arr_len = GET_SIZE(primes);
    for (i = 2, l = 0; i <= arr_len; i++) {
        if (isprime(i))
            primes[l++] = i;
    }
    max_end_pos = l-1;
}



int get_max_denum(char *num)
{
    int i;
    double nd;
    long long int nl;
    int denum;

    nl = 0;
    for (i = 0; num[i] != '.' && num[i]; i++)
        nl = nl * 10 + num[i] -  '0'; 

    denum = 1;
    if (num[i] == '.')
        i++;
    for (; num[i]; i++) {
        nl = nl * 10 + num[i] - '0';
        denum = denum * 10;
    }
  
    memset(dfact, 0, sizeof(dfact)); 
    int k = 0;
    int p;
    for (i = 0; i <= max_end_pos; i++) {
        p = primes[i];
        if (denum % p == 0)
            dfact[k++].num = primes[i];
        while (denum % p == 0) {
            dfact[k-1].count++;
            denum = denum / p;
        }
    }
    
    int redenum = 1;
    int factor;
    int j;
    for (i = 0; i < k; i++) {
        for (j = 0; j < dfact[i].count; j++) {
            factor = dfact[i].num;
            if (nl % factor == 0)             
                nl = nl/factor;
            else
                redenum = factor * redenum;
        }
    }
//    printf("%d\n", redenum);
    return redenum;

}
int main()
{
    int t;
    char num[20];
    scanf("%d", &t);
    generate_primes();
    while (t--){
        scanf("%s", num);
        printf("%d\n", get_max_denum(num));
    }
    return 0;
}

