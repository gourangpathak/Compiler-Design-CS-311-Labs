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
// A temprory string to store the operator
char operator[200];
// A temprory string to store the variable name
char vblname[200];
// An array to store all the jump target labels
int jumptargets[3];
// A 2D Character matrix to store the lines read from the file 
char alllines[500][500];
// A string buffer
char str[100];
// A variable for line count
int lc = 0;

// A variable to store the size of the table
int size_of_table = 0;
// A variable to store count of the number of initialized variables
int count = 1;

// An Array of type entry of size 200
struct entry symbol_table[200];

// Signature for the method to add an element to the table
void ADD(char *name, char *type);

// Signature for the method to get an element to the table
int GET(char *name);

char* check_type(char* a,char* b);
FILE *fp;
%}

%union {
	char *intval;
    char *floatval;
    char stringval[200];
    int newintval;
    float newfloatval;
};

// Currently I am considering BOOL as an integer token
%token <intval> ID INT BOOL
%token <floatval> FLOAT
%left AND OR NOT
%type <stringval> EXP TERM FACTOR type
%token FLOAT_CONST SEMICOLON COMMA IF ELIF ELSE AND OR NOT WHILE FOR SGT SLT LTE GTE EQ NQ  
%token <newintval> INT_CONST

%%

// GRAMMAR
prog : funcDef {printf("Accepted\n"); fp = fopen("output.ll", "a");fprintf(fp, "ret i32 0\n"); fclose(fp);} ;

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
varList : ID {ADD($1, temp); fp = fopen("output.ll", "a");fprintf(fp,"%%%d = alloca i32, align 4\n", count); count++; fclose(fp);} COMMA varList  | ID {ADD($1, temp);fp = fopen("output.ll", "a"); fprintf(fp,"%%%d = alloca i32, align 4\n", count); count++; fclose(fp);};

stmtList : stmtList stmt | stmt;

stmt : assignStmt | ifStmt | whileStmt | elseIfStmt | elseStmt | forStmt ;

assignStmt : ID  {
    strcpy(vblname, $1);
}'=' EXP SEMICOLON 
            {
                // First Check if there is an entry in the table
                /*if (GET($1) >= 0){
                    // If the type of the ID is int while that of Exp is bool or vice-versa, raise a warning
                    if (!strcmp(symbol_table[GET($1)].var_type, "int") && !strcmp($3, "boolean")) printf("WARNING, Boolean assigned to Int\n");
                    else if(!strcmp(symbol_table[GET($1)].var_type, "boolean") && !strcmp($3, "int")) printf("WARNING, Boolean assigned to Int\n");
                }*/
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
FACTOR : ID  {int idx = GET($1); if (idx != -1) {strcpy($$, symbol_table[idx].var_type);
    fp = fopen("output.ll", "a");
    fprintf(fp,"%%%d = load i32, i32* %%%d, align 4\n", count, GET($1));
    count++;
    fclose(fp);
} else {strcpy($$, "Not Declared");}}
       | INT_CONST {strcpy($$, "int");
         fp = fopen("output.ll", "a");
        fprintf(fp,"store i32 %d, i32* %%%d, align 4\n", $1, GET(vblname));
        fclose(fp);
        };
       | FLOAT_CONST {strcpy($$, "float"); }
       ;

ifStmt : IF  '(' bExp {
    fp = fopen("output.ll", "a");
    fprintf(fp, "br i1 %%%d, label %%%d, label ##\n\n", count, count+1);
    fprintf(fp, "%d:\n", count+1);
    count+=2;
    fclose(fp);
} ')' '{' stmtList '}' {
    fp = fopen("output.ll", "a");
    fprintf(fp, "br label __\n\n");
    jumptargets[0] = count;
    fclose(fp);
};

RELOP : SLT | SGT {strcpy(operator, "sgt");} | LTE | GTE | EQ | NQ

bExp : EXP RELOP EXP {
    fp = fopen("output.ll", "a");
    fprintf(fp, "%%%d = icmp %s i32 %%%d , %%%d\n", count, operator, count-2, count-1);
    fclose(fp);
    

}| bExp AND bExp |  bExp {
    fp = fopen("output.ll", "a");
    fprintf(fp, "br i1 %%%d, label $$ , label %%%d\n\n", count, count+1);
    fprintf(fp, "%d:\n", count+1);
    count+=2;
    fclose(fp);
} OR  bExp  |  NOT '(' bExp ')' | ID;

whileStmt : WHILE '(' bExp ')' '{' stmtList '}';

elseIfStmt : ifStmt ELIF '(' bExp ')' '{' stmtList '}' | ifStmt ELIF '(' bExp ')' '{' stmtList '}' ELSE '{' stmtList '}';

elseStmt : ifStmt ELSE '{' {
    fp = fopen("output.ll", "a");
    fprintf(fp, "%d:\n", count);
    jumptargets[1] = count;
    count++;
    fclose(fp);
} stmtList '}' {
   
    fp = fopen("output.ll", "a");
    fprintf(fp, "br label __\n\n");
    fprintf(fp, "%d:\n", count);
    jumptargets[2] = count;
    count++;
    fclose(fp);
}; 

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
    // Read the file again
    FILE *nfp = fopen("output.ll", "r");
    // Read each line from the file into the 2D char matrix initialized above
    while(fgets(alllines[lc], 500, nfp)) {
        // Add null terminator after each string is read
        alllines[lc][strlen(alllines[lc])-1]='\0';
        // increment the line count
        lc++;
    } 
    fclose(nfp);

    // Loop over all the lines in the file
    for(int j=0; j<lc; j++)
    {
        // loop over each individual line
        for(int k=0; k<strlen(alllines[j]); k++)
        {
            // Check if you found ^^ This means you have matched an 
            // if statement and therefore you replace @@ by jump target 
            // for if which is stored in jumptargets[0]
            if(alllines[j][k] == '^') {
                sprintf(str, "%%%d", jumptargets[0]);
                alllines[j][k] = str[0];
                alllines[j][k+1] = str[1];
                 if(strlen(str)>1)
                    alllines[j][k+2]=str[2];
            }
           // Check if you found ## This means you have matched an 
            // else and therefore you replace $$ by jump target 
            // for else which is stored in jumptargets[1]
            else if(alllines[j][k]=='#') {
                sprintf(str, "%%%d", jumptargets[1]);
                alllines[j][k]=str[0];
                alllines[j][k+1]=str[1];
                if(strlen(str)>1)
                    alllines[j][k+2]=str[2];
            }
            // Check if you found __ This means you have matched an 
            // else and therefore you replace __ by jump target 
            // for else which is stored in jumptargets[2]
            else if(alllines[j][k]=='_') {
                int t = jumptargets[2];
                sprintf(str, "%%%d", t);
                alllines[j][k]=str[0];
                alllines[j][k+1]=str[1];
                if(strlen(str)>1)
                    alllines[j][k+2]=str[2];
            }
            else if(alllines[j][k]=='$') {
                int t = jumptargets[1] ;
                sprintf(str, "%%%d", t);
                alllines[j][k]=str[0];
                alllines[j][k+1]=str[1];
                if(strlen(str)>1)
                    alllines[j][k+2]=str[2];
            }
        }
        strcpy(str, "");
    }
    fp = fopen("finaloutput.ll", "w");
    for(int j=0; j<lc; j++) {
        fprintf(fp, "%s\n", alllines[j]);
    }
    fclose(fp);
    
    // Print the symbol Table
    printf("\n================================  SYMBOL TABLE   ================================\n");
    for (int i=0; i<size_of_table; i++){
		printf("Symbol Name: %s, Symbol Type: %s, INDEX %d\n", symbol_table[i].var_name, symbol_table[i].var_type, i);
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