#include <stdio.h>
int last_digit(int a, int b)
{
    int t = 1;
    while (b > 1) {
        a = a % 10;
        if (b%2 != 0)
            t = (t*a)%10;
        b = b/2;
        a = (a*a)%10;
        if (a == 1 || a == 5){
            return (a * t)%10;
        }
    }
    return (a*t)%10;
}
int main()
{
    int t;
    int a, b;
    scanf("%d", &t);
    while (t--){
        scanf("%d %d", &a, &b);
        if (b == 0 || a == 1)
            printf("1\n");
        else
        if (a == 0)
               printf("0\n");
        else
            printf("%d\n", last_digit(a, b));
    }
    return 0;
}

