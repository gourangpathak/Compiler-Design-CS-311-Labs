%{
#include <stdio.h>
#include "parser.tab.h"
int yylex(void);
int yyerror(char *);
%}

%token ID INT FLOAT COMMA SEMICOLON

%%
prog : funcDef { printf("Rule used is prog -> funcdef\nAccepted\n"); } ;
funcDef : type ID '(' argList ')' '{' declList stmtList '}' {printf("Rule used is funcDef → type id '(' argList ')' '{' declList stmtList '}'\n"); };
argList : arg COMMA arg | {printf("Rule used is argList → arg COMMA arg | epsilon;\n");};
arg : type ID {printf("Rule used is arg → type ID;\n");};
declList :  decl SEMICOLON declList | {printf("Rule used is declList → decl SEMICOLON declList|epsilon;\n");};
decl : type varList {printf("Rule used is decl → type varList;\n");};
varList : ID COMMA varList | ID {printf("Rule used is varList → ID COMMA varList|ID;\n");}; 
type : INT|FLOAT {printf("Rule used is type → INT|FLOAT;\n");};
stmtList :  {printf("Rule used is stmtList → epsilon;\n");};
%%

int main()
{
    yyparse();
}

int yyerror(char *s){
    fprintf(stderr,"Error encountered is %s", s);
}
