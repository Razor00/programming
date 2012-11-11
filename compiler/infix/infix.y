%{
#include <stdio.h>
%}
%token NUMBER
%left '+' '-'
%left '*'
%left '/'
%left '(' ')'
%right '^'
%%
input   :
        | input expr '\n' { printf("result = %d\n", $2);}

;

expr    : NUMBER
        | '(' expr ')'  { $$ = $2; }
        | expr '+' expr { $$ = $1 + $3; }
        | expr '-' expr { $$ = $1 - $3; }
        | expr '*' expr { $$ = $1 * $3; }
        | expr '/' expr { $$ = $1 / $3; }
        | expr '^' expr { int i; for ($$ = 1, i = 0; i < $3; i++) { $$ = $$ * $1; }  }
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


