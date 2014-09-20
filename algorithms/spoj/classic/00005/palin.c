#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
    return a > b?a:b;
}

int incr_string(char *s, int l)
{
   /*do it from the end */ 
    char *ch = s + l - 1;

    int tn, n;
    int c = 1;
    while (ch >= s) {
        tn = (*ch - '0') + c;
        n = tn % 10;
        c = tn / 10;
        *ch = n + '0';
        ch--;
    }
    return c;
}

int next_p(int n)
{
    if (n < 9)
        return n+1;
    if (n == 99)
        return 101;

    return ((n/11+1) * 11);
}

int palindrome(char *s1, char *s2, int l)
{
    s2 = s2 + l - 1;
    while (l-- && (*s1++ == *s2--));
    return (l == -1);
}
char *next_palindrome(char *str)
{
    int len = strlen(str);
    int m1, m2;

    m1 = (len-1)/2;    
    m2 = m1;
    if (len % 2 == 0) {
        m2 = m1+1;
    }
    char *s1 = str;
    char *s2 = str+m2+1;
    int r, c, l, np;
  
    l = m1;
    if (l <= 0) {
        int i = 4;
        np = next_p(atoi(str));
        str[i] = '\0';
        while (np) {
            str[--i] = np%10 + '0';
            np = np/10;
        } 
        return &str[i];
    }
    if ((str[m1] < str[m2]) || 
            ((str[m1] == str[m2]) && 
             (((r = strncmp(s1, s2, l)) < 0) || palindrome(s1, s2, l))
            )) {
        /* add 1 to the median */
        str[m1] = str[m1] + 1;
        if (str[m1] == 58) {
            str[m1] = '0';
            c = incr_string(s1, l);
            if (c == 1) {
                /*got a carry at the end, find the prev palindrome*/
                /*len has now increased, palindrome will be of form
                 * 100001, 101 etc */
                str--; 
                len++;
                memset(str, '0', len);
                str[0] = str[len-1] = '1';
                str[len] = '\0';
                return str;
            }
        }
    }
    str[m2] = str[m1];
    int i;
    for (i = 0; i < l; i++)
        s2[i] = s1[l-i-1];
    return str;
}


int main()
{
    int t, r;
    char str[1000000 + 100];
    char *ch;
    scanf("%d", &t);
    while (t--){
        scanf("%s", str+1);
        ch = next_palindrome(str+1);
        printf("%s\n", ch);
    }
    return 0;
}

