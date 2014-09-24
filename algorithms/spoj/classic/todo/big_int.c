#include <stdio.h>
#include <string.h>

/* Assumption: each array cell occupy one element and  (not a char)
 LSB start first in the array
 Array is sufficiently large to accomodate a carry 
 return the length of the C array 
 Assumption A greater than B*/
int add(char *A, char *B, int alen, int blen, char *C)
{
    int i, s, c;
    c = 0;
    for (i = 0; i < blen; i++) {
        s = A[i] + B[i] + c; 
        c = s/10;
        C[i] = s%10;
    }
    for (; i < alen; i++) {
        s = A[i] + c; 
        c = s/10;
        C[i] = s%10;
    }
    
    if (c)
        C[i++] = c;
    
    i--;
    while (i >= 0 && C[i] == 0)
        i--;

    return i;
}
/*
void sub(char *A, char *B, int alen, int blen, char *C)
{
    char *s1, char *s2;
    int alen, blen; 
    int s1_len, s2_len;

    s1 = B;
    s1_len = blen;
    s2 = A;
    s2_len = alen;
    if (alen > blen) {
        s1 = A;
        s2 = B;
        s1_len = alen;
        s2_len = blen;
    }
    int i, j, c, s;
    c = 0;
    s = 0;
    for (i = 0; i < s1_len; i++) {
        s = s1[i] + s2[i] + c; 
        c = s/10;
        C[i] = s%10;
    }
    for (; i < s2_len; i++)
        s = s2[i] + c; 
        c = s/10;
        C[i] = s%10;
    }
    if (c)
        C[i++] = c;

    return i;
}
*/
/* A > B */
int sub(char *A, char *B, int alen, int blen, char *C)
{
    /* take 9's complement of B */
    int c, s;
    int i;
    
    c = 1;
    for (i = 0; i < blen; i++) {
        s = A[i] + (9 - B[i]) + c;
        c = s/10;
        C[i] = s%10;
    }
    for (; i < alen; i++) {
        s = A[i] + (9 - 0) + c;
        c = s/10;
        C[i] = s%10;
    }
    if (c)
        C[i++] = c;

    i--;
    while (i >= 0 && C[i] == 0)
        i--;

    return i+1;
}
/* Assumption A > B */
int mul(char *A, char *B, int alen, int blen, char *C)
{

    int i, j, s, c;
    memset(C, 0, alen + blen);
    for (i = 0; i < blen; i++) {
        c = 0;
        for (j = 0; j < alen; j++) {
            s = C[i+j] + A[j] * B[i] + c; 
            c = s/10;
            C[i+j] = s%10;
        }
        if (c) {
            C[i+j] = c;
        }
    }
    if (c)
        return i+j;
    else
        return i+j-1;
}
/* Assumption A > B 
 * Data to be stored from MSB onwards
 */
int div(char *A, char *B, int alen, int blen, char *C)
{
    int i, j, s, c;
    int r;

}
char * strrev(char *s)
{
    int st, end;
    int ch;
    st = 0;
    end = st + strlen(s) - 1;
    while (st <= end){
        ch = s[st] - '0';
        s[st] = s[end] - '0';
        s[end] = ch;
        st++;
        end--;
    }
    return s;
}
        
        
int main()
{
    char A[300];
    char B[300];
    char C[300];
    scanf("%s %s", A, B); 
    int i;
    i = mul(strrev(A), strrev(B), strlen(A), strlen(B), C);
    i--;
    for (; i >= 0; i--)
        printf("%d", C[i]);
}

