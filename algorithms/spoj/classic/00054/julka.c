#include <stdio.h>
#include <string.h>
/* arr order is lsb is in lsb
 * i.e given number 235
 * stored as 532 in array
 */
int add(char *arr, int n, int pos)
{
    int i, q, s, c;
    i = 0;
    c = 0;
    i = pos;
    while (n||c) {
        q = n % 10; 
        s = c + q + arr[i];
        arr[i] = s%10;
        c = s/10;
        n = n/10;
        i++;
    }
    return i;
}

int max(int a, int b)
{
    return a > b? a:b;
}

void print_number(char *arr, int n)
{
    int i;
    //printf("bits: %d\n", n);
    if (n == 0){
        printf("0\n");
        return;
    }
    i = n - 1;
    while (i >= 0 && arr[i] == 0)
        i--;
    if (i == -1) {
        printf("0\n");
        return;
    }
    for ( ;i >= 0; i--)
        printf("%d", arr[i]);
    printf("\n");
}

int process_n_add(char *arr, char *num, int total_valid_bits)
{
    int j, n, pos;
    n = total_valid_bits;
    for (j = strlen(num) - 1, pos = 0; j >= 0; j--, pos++)
        n = max(n, add(arr, num[j]-'0', pos));
    return n;
}
/* assumption arr>num */
int process_n_subtract(char *arr, char *sub, int total_valid_bits)
{
    int i, j, n, pos;
    n = total_valid_bits;
    /* nine's complement */
    /* eg: 670-300 =? 670 + (1000-300) - 1000 => (670+700)-1000 => 370
     * 1. get nine's complement of b
     * 2. add a to b
     * 3. remove the top 1
     * 4. add 1 to the sum
     * */
    //printf("num = %s\n", num);

    /* 1. nine's complement of num*/
    char num[200];
    memcpy(num, sub, sizeof(num));
    int len = strlen(num);
    num[n] = '\0';
    for (j = n - 1, i = 0; i < len; j--, i++)
        num[j] = '9' + '0' - num[len-1-i];
    for (; j >= 0; j--)
        num[j] = '9';

    //printf("num = %s\n", num);

    n = process_n_add(arr, num, n);    //2.add a to b
    n = n - 1;      //3.remove the top 1  
    add(arr, 1, 0); //4.add a one
    return n;
}
void swap(char *s, int k)
{
    int i = 0;
    char c;
    k--;
    while (i < k) {
        c = s[i];
        s[i] = s[k];
        s[k] = c;
        i++;k--;
    }

}
int division(char *arr, int b, char *div, int valid_bits)
{
    int n, i, r, q, k;
    n = valid_bits;
    k = 0;
    q = arr[n-1];
    for (i = n-2; i >= 0;) {
        if (q >= b) {
            div[k++] = q / b;
            q = q % b;          
        }
        else {
            q = q * 10 + arr[i--];
            if (q < b)
                div[k++] = 0;

        }
    }
    if (q >= b) 
       div[k++] = q/b;
      
    div[k] = '\0';
    swap(div, k);
    return k;
}
int main()
{
    int t, n, k;
    char arr[200];
    char num1[200];
    char num2[200];
    char div[200];

    t = 10;
    while (t--){
        memset(arr, 0, sizeof(arr));
        memset(div, 0, sizeof(div));
        n = 1;
        scanf("%s %s", num1, num2);
        n = process_n_add(arr, num1, n);
        //print_number(arr, n);
        n = process_n_subtract(arr, num2, n);
        //print_number(arr, n);
        n = division(arr, 2, div, n); 
        memcpy(num1, div, sizeof(num1));
        k = n;
        //print_number(div, n);
        n = process_n_add(div, num2, n); 
        print_number(div, n);
        print_number(num1, k);
    }
    return 0;
}
