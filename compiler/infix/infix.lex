%{
#include "y.tab.h"
%}
digit [0-9] 
%%
{digit}+        { yylval = atoi(yytext); return (NUMBER); }
\+|-|\*|\n      { return (yytext[0]); } 
%%
int yywrap()
{
    return 1;
}

