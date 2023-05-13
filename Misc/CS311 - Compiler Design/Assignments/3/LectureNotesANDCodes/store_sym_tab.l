%{
    #include <string.h>
    #define MAX 30
    char sym_tab[MAX][MAX];
    int  count = 0;
    void add_sym_tab(char name[], int len);
%}
digit [0-9]
letter [a-zA-Z]
letter_or_digit {digit}|{letter}
us     [_]
%s id_contd
%%
"_"                            { BEGIN(id_contd); }
{digit}+                       { printf("An integer : %s is encountered\n", yytext); }
{digit}+"."{digit}+             { printf("A float : %s is encountered\n", yytext); }             
<id_contd>{letter}{letter_or_digit}* { printf("Identifier : %s is encountered\n", yytext); add_sym_tab(yytext, yyleng); BEGIN(INITIAL); }
"+"|"-"|"*"|"/"                { printf("An operator : %s is encountered\n", yytext); }
"int"|"float"|"if"|"else"|"return"|"void" { printf("Reserved words : %s is encountered\n", yytext); }
\/\*.*\*\/                     { printf("Comments are ignored\n"); }
["{""}"]$                      { printf("Start or end of a function\n"); }     
\\                             { printf("A special character\n"); }
.|\n                           { printf("Other characters : %s \n", yytext); }
%%


void add_sym_tab(char *name, int len)
{
    strcpy(sym_tab[count], name);
    count++;
}
int main()
{
    yylex();
    printf("Number of entries in symbol table is %d\n", count);
}
