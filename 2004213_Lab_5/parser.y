%{
#include <stdio.h>
#include "parser.tab.h"
int yylex(void);
int yyerror(char *);
%}


%token ID INT FLOAT INT_CONST FLOAT_CONST SEMICOLON COMMA IF ELIF ELSE AND OR NOT WHILE FOR RELOP  
%left AND OR

%%
prog : funcDef {printf("Accepted\n");} ;
funcDef : type ID '(' argList ')' '{' declList stmtList '}' ;
argList : arg COMMA arg | ;
arg : type ID;
type : INT | FLOAT;
declList : decl SEMICOLON declList | ;
decl : type varList;
varList : ID COMMA varList | ID;
stmtList : stmtList stmt | stmt;
stmt : assignStmt | ifStmt | whileStmt | elseIfStmt | elseStmt | forStmt ;
assignStmt : ID '=' EXP SEMICOLON { printf("Assignment Parsed\n");};
EXP : EXP '+' TERM | EXP '-' TERM | TERM;
TERM : TERM '*' FACTOR | TERM '/' FACTOR | FACTOR;
FACTOR : ID | INT_CONST | FLOAT_CONST;
ifStmt : IF '(' bExp ')' '{' stmtList '}';
bExp : EXP RELOP EXP | bExp AND bExp |  bExp OR bExp |  NOT '(' bExp ')' | ID;
whileStmt : WHILE '(' bExp ')' '{' stmtList '}';
elseIfStmt : ifStmt ELIF '(' bExp ')' '{' stmtList '}' | ifStmt ELIF '(' bExp ')' '{' stmtList '}' ELSE '{' stmtList '}';
elseStmt : ifStmt ELSE '{' stmtList '}'; 
forStmt : FOR '(' assignStmt bExp SEMICOLON ID '=' EXP ')' '{' stmtList '}' ;
%%

int main(int argc, char **argv) {
	yyparse();
}

int yyerror(char *s){
    fprintf(stderr, "Error Encountered is %s\n", s);
}