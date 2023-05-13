%{
%}
digit [0-9]
letter [a-zA-Z]
letter_or_digit {digit}|{letter}
us     [_]

%%
[ \t]+                         { printf("White space is encountered\n"); }
{digit}+                       { printf("An integer : %s is encountered\n", yytext); }
{digit}+"."{digit}+             { printf("A float : %s is encountered\n", yytext); }             
{us}{letter}{letter_or_digit}* { printf("Identifier : %s is encountered\n", yytext); }
"+"|"-"|"*"|"/"                { printf("An operator : %s is encountered\n", yytext); }
"int"|"float"|"if"|"else"|"return"|"void" { printf("Reserved words : %s is encountered\n", yytext); }
\/\*.*\*\/                     { printf("Comments are ignored\n"); }
.|\n                           { printf("Other characters\n"); }
%%

int main()
{
    yylex();
}
