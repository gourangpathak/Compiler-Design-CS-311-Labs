%{
    #include <string.h>
    #define MAX 100
    int  count = 0;
    char sym_tab[MAX][MAX];
    void add_sym_tab(char *name, int len);
%}

digit [0-9]
letter [a-zA-Z]
letter_or_digit {digit}|{letter}|[_]    

%%

[ \t]+                                                                   { printf("Removing the white spaces\n"); }

\/\*.*\*\/                                                               { printf("Ignoring the text within comments\n"); }    

"short"|"float"|"double"|"bool"|"char"|"signed"|"unsigned"|"for"|"while"|"do"|"return"|"void"|"switch"|"break"|"case"|"continue"|"goto"|"long"|"static"|"union"|"default"|"int"|"float"|"if"|"else"|"return"     { printf("Keyword : %s is encountered\n", yytext); }            

[_]*{letter}{letter_or_digit}*                                           { printf("Identifier : %s is encountered\n", yytext); add_sym_tab(yytext, yyleng); }

[-]?{digit}+                                                             { printf("An integer constant: %s is encountered\n", yytext); }

[-]?{digit}*"."{digit}+                                                  { printf("A floating point constant: %s is encountered\n", yytext); } 

"="|"+="|"−="|"∗="|"/="|"+"|"-"|"*"|"/"                                  { printf("Arithmetic operator : %s is encountered\n", yytext); }

"<"|">"|"<="|">="|"=="                                                   { printf("An Relational operator : %s is encountered\n", yytext); }

";"|"("|")"|","|"["|"]"|"{"|"}"                                          { printf("Special symbol : %s is encountered\n", yytext); }

%%


void add_sym_tab(char *name, int len){

    // Check if the current Identifier is already inserted in the symbol table.
    for(int i = 0; i <= count; i++){
        if( strcmp(sym_tab[i], name) == 0) 
            return;
    }

    strcpy(sym_tab[count], name);
    count = count + 1;
}

int main(){
    yylex();

    // Printing the symbol table to the console.
    printf("\nSymbol Table :- \n");
    for(int i = 0; i < count; i++)
        printf("%s\n", sym_tab[i]);
}
