%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int yylex(void);
int yyerror(char *);

// A structure for the entry in the symbol table which stores the name of the variable along with its type
struct entry {
    char var_name[50];
    char var_type[10];
};

// A temprory string to copy type
char temp[200];

// A variable to store the size of the table
int size_of_table = 0;

// An Array of type entry of size 200
struct entry symbol_table[200];

// Signature for the method to add an element to the table
void ADD(char *name, char *type);

// Signature for the method to get an element to the table
int GET(char *name);

char* check_type(char* a,char* b);
%}

%union {
	char *intval;
    char *floatval;
    char stringval[200];
};

// Currently I am considering BOOL as an integer token
%token <intval> ID INT BOOL
%token <floatval> FLOAT
%left AND OR NOT
%type <stringval> EXP TERM FACTOR type
%token INT_CONST FLOAT_CONST SEMICOLON COMMA IF ELIF ELSE AND OR NOT WHILE FOR RELOP   


%%

// GRAMMAR

prog : funcDef {printf("Accepted\n");} ;

// Add the entry (Id, type) into the table
funcDef : type ID {ADD($2, $1);} '(' argList ')' '{' declList stmtList '}' ;

argList : arg COMMA arg | ;

// Add the entry (Id, type) into the table
arg : type ID { ADD($2, $1); };

// Copy INT/FLOAT/BOOL into type
type : BOOL {strcpy($$, $1);} | INT {strcpy($$, $1);} | FLOAT {strcpy($$, $1);} ;

declList : decl SEMICOLON declList | ;

// Copy the type into the temprory string
decl : type {strcpy(temp, $1);} varList;

// Add the entry (Id, temp) the type you got from the declaration to the table
varList : ID COMMA varList {ADD($1, temp);} | ID {ADD($1, temp);};

stmtList : stmtList stmt | stmt;

stmt : assignStmt | ifStmt | whileStmt | elseIfStmt | elseStmt | forStmt ;

assignStmt : ID '=' EXP SEMICOLON 
            {
                // First Check if there is an entry in the table
                if (GET($1) >= 0){
                    // If the type of the ID is int while that of Exp is bool or vice-versa, raise a warning
                    if (!strcmp(symbol_table[GET($1)].var_type, "int") && !strcmp($3, "boolean")) printf("WARNING, Boolean assigned to Int\n");
                    else if(!strcmp(symbol_table[GET($1)].var_type, "boolean") && !strcmp($3, "int")) printf("WARNING, Boolean assigned to Int\n");
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

// for ID, Check if ID is in table if not return not declared
// for INT/FLOAT Const copy int/float to factor 
FACTOR : ID  {int idx = GET($1); if (idx != -1) {strcpy($$, symbol_table[idx].var_type);} else {strcpy($$, "Not Declared");}}
       | INT_CONST {strcpy($$, "int");}
       | FLOAT_CONST {strcpy($$, "float");}
       ;

ifStmt : IF '(' bExp ')' '{' stmtList '}';

bExp : EXP RELOP EXP | bExp AND bExp |  bExp OR bExp |  NOT '(' bExp ')' | ID;

whileStmt : WHILE '(' bExp ')' '{' stmtList '}';

elseIfStmt : ifStmt ELIF '(' bExp ')' '{' stmtList '}' | ifStmt ELIF '(' bExp ')' '{' stmtList '}' ELSE '{' stmtList '}';

elseStmt : ifStmt ELSE '{' stmtList '}'; 

forStmt : FOR '(' assignStmt bExp SEMICOLON ID '=' EXP ')' '{' stmtList '}' ;
%%

// Method to Add an entry to the symbol table
void ADD(char *name, char *type) {
    // check if the symbol is alredy present
    int alredyPresent = 0;
    // Loop through the table
	for (int i=0; i<size_of_table; i++){
        // check If the variable is alredy present 
		if (strcmp(name, symbol_table[i].var_name) == 0) {
			alredyPresent = 1;
		}
	}
    // If variable not present
	if (alredyPresent == 0){
        // Add a new entry
		strcpy(symbol_table[size_of_table].var_name, name);
        strcpy(symbol_table[size_of_table].var_type, type);
        // Increment the size of the table
		size_of_table++;
	}
}

// Method to Get the index of an entry in the table
int GET(char *name) {
    // Iterate over the table
	for (int i=0; i<size_of_table; i++){
        // If found
		if (strcmp(name, symbol_table[i].var_name) == 0) {
            // return its index
			return i;
		}
	}
    printf("ERROR, Identifier %s not declared\n", name);
    // If not found return -1
    return -1;
}

int main(int argc, char **argv) {
	yyparse();
    // Print the symbol Table
    printf("\n================================  SYMBOL TABLE   ================================\n");
    for (int i=0; i<size_of_table; i++){
		printf("Symbol Name: %s, Symbol Type: %s\n", symbol_table[i].var_name, symbol_table[i].var_type);
}
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

int yyerror(char *s) {
    fprintf(stderr, "Error occured %s\n", s);
}