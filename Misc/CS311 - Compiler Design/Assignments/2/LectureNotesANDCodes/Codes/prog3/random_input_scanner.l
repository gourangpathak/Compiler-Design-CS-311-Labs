%{
    /* Definition */
%}
digit    [0-9]
letter   [a-zA-Z0-9]
%%
"pencil"   { printf("%s : A pencil is found\n", yytext); }
"pen"      { printf("%s : A pen is found\n", yytext); }
123        { printf("%s : This is an integer\n", yytext); }
{digit}+   { printf("%s : Digits are encountered\n", yytext);}
{letter}+  { printf("%s : A sequence of letters is encountered\n", yytext);}
[ \t]+     { printf("%s : spaces are ignored\n", yytext);}
%%
int main()
{
    yylex();
}

