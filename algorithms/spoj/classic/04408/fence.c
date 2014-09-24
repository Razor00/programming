#include <stdio.h>
#define PI 3.14159265358979323846
int main()
{
    double l;
    while (1){
        scanf("%lf", &l);
        if (l == 0)
            break;
        printf("%0.2lf\n", (l*l)/(2*PI));
    }
    return 0;
}

