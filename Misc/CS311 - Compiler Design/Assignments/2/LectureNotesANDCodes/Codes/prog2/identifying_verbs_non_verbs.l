%{
    #include <stdio.h>
%}

%%
[ \t]+                             ;
"is" | 
"am" | 
"are"                             { printf("%s : is a verb\n", yytext); }
[^\t ]+                           { printf("%s : is not a verb\n", yytext); }

%%

int main()
{
    yylex();
}
