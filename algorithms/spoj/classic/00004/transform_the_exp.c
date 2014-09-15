/* Transform the algebraic expression with brackets into RPN form (Reverse Polish Notation). 
 * Two-argument operators: +, -, *, /, ^ (priority from the lowest to the highest), brackets ( ). 
 * Operands: only letters: a,b,...,z. Assume that there is only one RPN form (no expressions like a*b*c).

 Input

t [the number of expressions <= 100]
expression [length <= 400]
[other expressions]

Text grouped in [ ] does not appear in the input file.
Output

The expressions in RPN form, one per line.

Example

Input:
3
(a+(b*c))
((a+b)*(z+x))
((a+t)*((b+(a+c))^(c+d)))

Output:
abc*+
ab+zx+*
at+bac++cd+^*
*/

#include <stdio.h>
char stack[500];
char op[500];

int isletter(int ch)
{
    return (ch >= 'a' && ch <= 'z');
}

int op_value(int op)
{
    switch (op) {
        case '$':
            return 1;
        case '+':
            return 2;
        case '-':
            return 3;
        case '*':
            return 4;
        case '/':
            return 5;
        case '^':
            return 6;
       // default:
      //      printf("error");
    }
    return 0;
}

int isoperator(int ch)
{
    return (op_value(ch) != 0);
}

int operator_preceeds(int op1, int op2)
{
    return (op_value(op1) > op_value(op2));
}

char *get_postfix(char *str)
{
    int stop, otop, ch;
    stop = -1;
    otop = -1;
    stack[++stop] = '$';

    while(*str) {
        if (isletter(*str)) {
            op[++otop] = *str++;
        }
        else if (*str == '(') {
                stack[++stop] = *str++;
        }
        else if (*str == ')') {
            /*pop off all elements until ( is seen */
                while (stack[stop] != '(')
                    op[++otop] = stack[stop--];
                stop--; //remove the top (
                str++;  //no need to store str
        }
        else if (isoperator(*str)) {
                if (operator_preceeds(stack[stop], *str))
                    op[++otop] = stack[stop--];
                else
                    stack[++stop] = *str++;
        }
    }
    while (stack[stop] != '$')
        op[++otop] = stack[stop--];
    op[++otop] = '\0';
    return op;
}

int main()
{
    char str[500];

    int tn;

    scanf("%d", &tn);
    while (tn--) {
        scanf("%s", str);
        printf("%s\n", get_postfix(str));
    }
    return 0;
}
