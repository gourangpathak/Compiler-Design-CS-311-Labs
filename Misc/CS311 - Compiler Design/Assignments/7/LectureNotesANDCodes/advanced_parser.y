%{
#include "advanced_parser.tab.h"
#include "head.h"
int  yylex(void);
int  yyerror(char* s);
void write_init_lines();
void write_closing_lines();
int  addToSymTab(char* t, char* s);
int  symTabLookUp(char* s);
char curType[MAX];
%}

%union{
    int    ival;
    double dval;
    char   sval[10];
    struct expStruct
    {
        double expVal;
        char   expType[30];
        int    irName; 
    }eval;
};


%token COMMA INT_CONST SEMICOLON RELOP LOGOP OR AND NOT IF WHILE
%token <sval> ID 
%type <eval> EXP TERM FACTOR bExp 
%token <ival> INT_CONST
%token <dval> DOUBLE_CONST
%token INT DOUBLE
%start prog
%%
prog : { 
           symbTabEntryCount = 0; 
           write_init_lines(); 
       } 
       funcDef 
       { 
           write_closing_lines(); 
       }
funcDef : TYPE_CONST ID '(' argList ')' '{' declList 
	{ } 
        stmtList '}' {}
argList : arg ',' arg {} | arg {} | ; 
arg	: TYPE_CONST ID {} 
declList : declList  decl {} | decl {}
decl : TYPE_CONST varList SEMICOLON 
        { 
            printf("Detected declaration\n"); 
        }
TYPE_CONST : INT 
	   { 
               strcpy(curType, "int"); 
               printf("Detected int\n"); 
           } 
	   | DOUBLE 
           { 
               strcpy(curType, "double"); 
               printf("Detected double\n");
           }
varList : ID 
	   { 
               int sym_tab_loc = addToSymTab(curType, $1); 
               /* Add allocation instruction */
           } 
           COMMA varList 
           { 
           }
	| ID 
           { 
               int sym_tab_loc = addToSymTab(curType, $1); 
               /* Add allocation instruction */
           }
stmtList : stmtList stmt | stmt;
stmt : assignStmt | ifStmt | whileStmt ;
assignStmt : ID '=' EXP SEMICOLON 
	   {    
               if(!strcmp($3.expType, "int_const") || !strcmp($3.expType, "int"))
               {
                   /* Write the store instruction */
               }
           }
EXP : EXP '+' TERM 
    { 
        strcpy($$.expType, $1.expType); 
        if(!strcmp($1.expType, "int"))
        {
            /* Write the add instruction */
        }
    }
    | EXP '-' TERM 
    { 
        strcpy($$.expType, $1.expType); 
    }
    | TERM 
     { 
         strcpy($$.expType, $1.expType); 
         $$.expVal = $1.expVal;
         $$.irName = $1.irName;
     } 
TERM : TERM '*' FACTOR 
     { 
         /* Determine the type */
         /* Write the mul instruction */
     }
     | TERM '/' FACTOR 
     { 
     }
     | FACTOR 
     { 
           strcpy($$.expType, $1.expType);
           $$.expVal = $1.expVal;
           $$.irName = $1.irName;
     }
FACTOR : ID 
       { 
           strcpy($$.expType, symbolTable[symTabLookUp($1)].type); 
           /* Write load instruction */
       } 
       | INT_CONST 
         { 
             strcpy($$.expType, "int_const"); 
             $$.expVal = $1; 
         }
       | DOUBLE_CONST 
         { 
             strcpy($$.expType, "double_const"); 
             $$.expVal = $1; 
         }
ifStmt : IF'('bExp')''{'stmtList '}' { }
bExp : EXP RELOP EXP { }
whileStmt : WHILE'('bExp')''{'stmtList'}' { } 
%%

void write_init_lines()
{
}

void write_closing_lines()
{
}

int addToSymTab(char *cur_type, char *s)
{
}

int symTabLookUp(char *s)
{
    return 0;
}

int main()
{
    yyparse();
}
