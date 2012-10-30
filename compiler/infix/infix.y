%{
#include <stdio.h>
%}
%token NUMBER
%right '+' '-'
%left '*'
%%
input   :
        | input expr '\n' { printf("result = %d\n", $2);}

;

expr    : NUMBER
        | expr '+' expr { $$ = $1 + $3; }
        | expr '-' expr { $$ = $1 - $3; }
        | expr '*' expr { $$ = $1 * $3; }
;
%%

int yyerror(char *s)
{
    printf("%s\n", s);
}

int main()
{
    yyparse();
}


