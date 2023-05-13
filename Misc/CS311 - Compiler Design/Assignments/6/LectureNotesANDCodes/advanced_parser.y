%{
#include "advanced_parser.tab.h"
#include "head.h"
int yylex(void);
int yyerror(char *);
int count = 0;
char type[10];
%}
%union{
    int    ival;
    double dval;
    char   sval[10];
};


%token COMMA INT_CONST SEMICOLON RELOP LOGOP OR AND NOT IF WHILE
%token <ival> ID
%type <sval> EXP TERM FACTOR bExp 
%start prog
%%
prog : funcDef { printf("Accepted\n"); }
funcDef : INT_CONST ID '(' argList ')' '{' declList stmtList '}'
argList : arg ',' arg | ;
arg : INT_CONST ID;
declList : declList  decl | decl ;
decl : INT_CONST { strcpy(type, "int"); }  varList SEMICOLON;
varList : ID  COMMA varList 
	| ID ;
stmtList : stmtList stmt | stmt;
stmt : assignStmt | ifStmt | whileStmt;
assignStmt : ID '=' EXP SEMICOLON 
	   { if(!strcmp(symbol_table[$1].type, "int") && !strcmp($3, "float")) 
             { 
                 printf("Error\n"); 
             }
	   }
EXP : EXP '+' TERM { }
    | EXP '-' TERM { }
    | TERM { } ;
TERM : TERM '*' FACTOR { }
     | TERM '/' FACTOR { }
     | FACTOR { strcpy($$, $1); }
FACTOR : ID { strcpy($$, symbol_table[$1].type); }
ifStmt : IF'('bExp')''{'stmtList '}' { }
bExp : EXP RELOP EXP { strcpy($$, $1); };
whileStmt : WHILE'('bExp')''{'stmtList'}'; 
%%

int main()
{
    yyparse();
}
