%{
    #include <stdio.h>
    int yylex(void);
    int yyerror(char*);
%}

%token ID 
%token INTEGER_CONSTANT FLOAT_CONSTANT 
%token INT FLOAT CHAR 
%token SEMICOLON COMMA 
%token ASSIGN 
%token IF ELIF ELSE 
%token AND OR NOT 
%token WHILE RETURN 
%token RELOP  

%left AND OR

%%

prog : funcDef ;

funcDef : type ID '(' argList ')' '{' declList stmtList '}'

argList : arg COMMA arg | %empty;

arg : type ID;

type      : INT | FLOAT | CHAR;

declList  : decl SEMICOLON declList | %empty ;

decl      : type varList;

varList : ID COMMA varList | ID;

stmtList : stmtList stmt | stmt;

stmt : assignStmt | ifStmt | whileStmt | elseIfStmt | elseStmt ;

assignStmt : ID ASSIGN EXP SEMICOLON;

EXP : EXP '+' TERM | EXP '-' TERM | TERM;

TERM : TERM '*' FACTOR | TERM '/' FACTOR | FACTOR;

FACTOR : ID;

ifStmt : IF '(' bExp ')' '{' stmtList '}';

bExp : EXP RELOP EXP;

bExp : bExp AND bExp |  bExp OR bExp |  NOT '(' bExp ')' ;

whileStmt : WHILE '(' bExp ')' '{' stmtList '}';

elseIfStmt : ELIF '(' bExp ')' '{' stmtList '}' ; 

elseStmt : ELSE '{' stmtList '}' ; 

%%

int main(int argc, char **argv) {
	yyparse();
}

int yyerror(char *s){
    fprintf(stderr, "error : %s\n", s);
}
