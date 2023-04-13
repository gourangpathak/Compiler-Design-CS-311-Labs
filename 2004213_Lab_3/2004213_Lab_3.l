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

%%
"int"|"main"|"short"|"float"|"double"|"bool"|"char"|"signed"|"unsigned"|"for"|"while"|"do"|"return"|"void"|"switch"|"break"|"case"|"continue"|"goto"|"long"|"static"|"union"|"default"|"class"|"public"|"private"|"protected" { printf("Keywords : %s is encountered\n", yytext); }
{digit}+                       { printf("An integer constant: %s is encountered\n", yytext); }
{digit}+"."{digit}+             { printf("A floating point constant : %s is encountered\n", yytext); }             
({us}|{letter})({us}|{letter_or_digit})* { printf("Identifier : %s is encountered\n", yytext); add_sym_tab(yytext, yyleng); }
"+"|"-"|"*"|"/"|"="|"+="|"-="|"*="|"/="      { printf("An Arithmetic operator : %s is encountered\n", yytext); }
\/\*.*\*\/                     { printf("Comments are ignored\n"); }
"<"|">"|"<="|">="|"=="         { printf("A relational operator %s is encountered\n", yytext); }
["{""}"]$                      { printf("Start or end of a function\n"); }     
\\                             { printf("A special character\n"); }
";"|"("|")"|","|"["|"]"|"{"|"}"     { printf("A special Symbol %s is encountered\n", yytext); }
"\n"                           { printf("A new line character\n");}
[ \t]+                         { printf("White space encountered\n"); }
.                              { printf("Invalid pattern\n"); }
%%


void add_sym_tab(char *name, int len)
{
    // To handle the case when length of string is more than 31
    if(len > 31) {
        printf("The Length of the Identifier %s is more than 31\n", name);
        return;
    }
    // To handle duplicate identifiers
    for(int i=0; i<=MAX; i++) {
        if(strcmp(sym_tab[i], name) == 0) {
            return;
        }
    }
    strcpy(sym_tab[count], name);
    count++;
}
int main()
{
    yylex();
    printf("Number of entries in symbol table is %d\n", count);
}
