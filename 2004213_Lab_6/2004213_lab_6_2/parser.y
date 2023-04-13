%{
// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

// Maximum
#define MAXIMUM 1000


typedef struct Symbol {
char name[MAXIMUM];
char type[MAXIMUM];
}Symbol;

typedef struct ST {
    Symbol symbol_table[MAXIMUM];
    int num_symbols;
    struct ST* parent; 
}ST;


ST* cur_sym_tab; 
ST* intmainSYmbolTable;


typedef struct getTable{
    int index;
    ST* indexTable;
}getTable;


char* check_type(char* , char* );
void setup();
void add_table();
getTable* fetch_table(char* name);
getTable* fetch_table_parent(char*, ST* );
void remove_table();
void add_symbol_table(char* name, char* type);

int yylex(void);
int yyerror(char *);

char decl_type[100];

%}

%union{
char* sval;
}

%token INT_CONST FLOAT_CONST ELIF SEMICOLON COMMA ASSIGN IF ELSE RELOP AND OR NOT EQ GE LE LT GT NE WHILE RETURN FOR
%token <sval> ID INT FLOAT BOOL
%type <sval> EXP TERM FACTOR type

%%

prog     : funcDef{ printf("Accepted\n"); }; 
funcDef  : type ID {  add_symbol_table($2, $1); add_table(); } '(' argList ')' '{' declList stmtList '}' { if(!strcmp($2,"main")){

    intmainSYmbolTable = cur_sym_tab;
 }
 
 remove_table(); };
 
argList  : arg COMMA arg | ;
arg      : type ID { add_symbol_table($2, $1); };
type     : BOOL {strcpy($$, $1);} | INT {strcpy($$, $1);} | FLOAT {strcpy($$, $1);} ;
declList : decl SEMICOLON declList | ;
decl     : type { strcpy(decl_type, $1); } varList;
varList  : ID COMMA varList { add_symbol_table($1, decl_type); } | ID { add_symbol_table($1, decl_type); };


stmtList : stmtList stmt | stmt;

stmt : assignStmt | ifStmt | whileStmt | elseIfStmt | elseStmt | forStmt | newAssignment ;

newAssignment : type ID '=' EXP SEMICOLON{
        check_new_assign($1,$2,$4);
        
};
assignStmt : ID '=' EXP SEMICOLON 

            {
            
                getTable* rl= fetch_table($1);;
                int flag = rl->index;
                
                
                // First Check if there is an entry in the table
                if ((rl->index) >= 0){
                    // If the type of the ID is int while that of Exp is bool or vice-versa, raise a warning
                    if(strcmp(rl->indexTable->symbol_table[flag].type,$3)!=0){
                        printf("Type Error---- Type of LHS is not equal to RHS");
                    
                    }
                }
            }
            ;

EXP : EXP '+' TERM  {strcpy($$, check_type($1, $3));}
    | EXP '-' TERM  {strcpy($$, check_type($1, $3));}
    | TERM {strcpy($$, $1);}
    ;

TERM : TERM '*' FACTOR {strcpy($$, check_type($1, $3));}
     | TERM '/' FACTOR {strcpy($$, check_type($1, $3));}
     | FACTOR {strcpy($$, $1);}
     ;

FACTOR   : ID {
            check_factor($$,$1);
            } | INT_CONST {strcpy($$, "int");} | FLOAT_CONST{strcpy($$, "float");};
   
    
ifStmt : IF '(' bExp ')' '{' { add_table();} stmtList '}' { remove_table(); };

bExp : EXP RELOP EXP | bExp AND bExp |  bExp OR bExp |  NOT '(' bExp ')' | ID;

whileStmt : WHILE '(' bExp ')' { add_table(); } '{' stmtList '}'{ remove_table(); };

elseIfStmt : ifStmt ELIF '(' bExp ')' '{' { add_table();} stmtList '}' { remove_table(); } | ifStmt ELIF '(' bExp ')' '{'{ add_table();} stmtList '}' { remove_table(); }  ELSE '{' { add_table();} stmtList '}' { remove_table(); } ;

elseStmt : ifStmt ELSE '{' { add_table();} stmtList '}' { remove_table(); };

forStmt : FOR '(' assignStmt bExp SEMICOLON ID '=' EXP ')' { add_table(); }  '{' stmtList '}' { remove_table(); };

%%

int main(int argc, char **argv) {
    cur_sym_tab = (ST*)malloc(sizeof(ST));
    cur_sym_tab->num_symbols = 0;
    cur_sym_tab->parent = NULL;
    yyparse();
    
    printf("\nUniversal Symbol Table\n");
	for(int i=0; i< cur_sym_tab->num_symbols; i++){
	    printf("Identifier:  %s  Type: %s\n", cur_sym_tab->symbol_table[i].name, cur_sym_tab->symbol_table[i].type);
	}	
    
    return 0;
}


int yyerror(char *s)
{
    fprintf(stderr, "An error in the parser : %s\n", s);
}


void add_table() {

    ST* new_table = (ST*)malloc(sizeof(ST));
    new_table->num_symbols = 0;
    new_table->parent = cur_sym_tab;
    cur_sym_tab = new_table;
}

void remove_table() {
    ST* old_table = cur_sym_tab;
    cur_sym_tab = cur_sym_tab->parent;
    free(old_table);
}

getTable* fetch_table(char* name) {
     int i;
     for (i = 0; i < cur_sym_tab->num_symbols; i++) {
         if (!strcmp(cur_sym_tab->symbol_table[i].name, name)) {
             getTable* rl= (getTable*)malloc(sizeof(getTable));
             rl->index=i;
             rl->indexTable = cur_sym_tab;
             return rl;
         }
     }
  
     if (cur_sym_tab->parent != NULL) {

         return fetch_table_parent(name, cur_sym_tab->parent);
     }
  
     getTable* rl= (getTable*)malloc(sizeof(getTable));
     rl->index=-1;
     rl->indexTable = cur_sym_tab;
     return rl;
    
 }

getTable* fetch_table_parent(char* name, ST* table) {

     int i;
     for (i = 0; i < table->num_symbols; i++) {
         if (!strcmp(table->symbol_table[i].name, name)) {
             getTable* rl= (getTable*)malloc(sizeof(getTable));
             rl->index=i;
             rl->indexTable = table;
             return rl;
         }
     }
    
     if (table->parent != NULL) {
         return fetch_table_parent(name, table->parent);
     }
   
     getTable* rl= (getTable*)malloc(sizeof(getTable));
     rl->index=-1;
     rl->indexTable = cur_sym_tab;
     return rl;
 }
 
 
 // Ensure type checking 
char* check_type(char* a, char* b)
{
    if(!strcmp(a, b)) {
        return a;
    }
    else if(!strcmp(a, "Not Declared") || !strcmp(b, "Not Declared")) {
        return "Not Declared";
    }
    else {
        return "int";
    }

}

void check_new_assign(char *a, char *b, char *c)
{
    getTable* rl= fetch_table(b);;

    int flag = rl->index; 
    if(flag>=0){
        printf("\nWarning: The identifier %s is already declared above.\n\n", b);
    }
    else{
        add_symbol_table(b, a);
    }
    
    getTable* rl2= fetch_table(b);
    int flag2 = rl2->index; 

    if(strcmp(a,c)!=0){
        printf("Type Error---- Type of LHS is not equal to RHS");
    }
}

void check_factor(char *a, char *b) {
    getTable* rl= fetch_table(b);;
            int flag = rl->index;           
            if (flag == -1) {strcpy(a, "Not Declared");} 
            else {strcpy(a, rl->indexTable->symbol_table[flag].type);}
}


void add_symbol_table(char* name, char* type) {

    getTable* rl= fetch_table(name);
    int flag = rl->index;

    if (flag >= 0) {
        printf("Error: The Identifier/Function %s is already declared above\n", name);
    }    
    else{
        ST* table = cur_sym_tab;
        
        strcpy(table->symbol_table[table->num_symbols].name, name);
        strcpy(table->symbol_table[table->num_symbols].type, type);
        table->num_symbols++;
    
    }

}