%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int yylex(void);
int yyerror(char *);
void write_init_lines();
void write_closing_lines();

// A structure for the entry in the symbol table which stores the name of the variable along with its type
struct entry {
    char var_name[50];
    char var_type[10];
    int num;
};

// A temprory string to copy type
char temp[200];

// A variable to store the size of the table
int size_of_table = 0;
int count = 0;

// An Array of type entry of size 200
struct entry symbol_table[200];

// Signature for the method to add an element to the table
void ADD(char *name, char *type);


// Signature for the method to get an element to the table
int GET(char *name);

char* check_type(char* a,char* b);
FILE * fptr;
%}

%union {
	char *intval;
    char *floatval;
    char stringval[200];
    struct expStruct {
        double expVal;
        char expType[100];
        int irName; 
    }eval;
};


%token <intval> ID INT BOOL
%token <floatval> FLOAT
%left AND OR NOT
%type <stringval> EXP TERM FACTOR type
%token INT_CONST FLOAT_CONST SEMICOLON COMMA IF ELIF ELSE AND OR NOT WHILE FOR RELOP   
%%

// GRAMMAR

prog : { write_init_lines(); } funcDef { write_closing_lines(); printf("Accepted\n");} ;

// Add the entry (Id, type) into the table
funcDef : type ID {fprintf(fptr, "define i32 @main() #0 {\n"); ADD($2, $1);} '(' argList ')' '{' declList stmtList '}' {fprintf(fptr, "ret i32 0\n}\n");};

argList : arg COMMA arg | ;

// Add the entry (Id, type) into the table
arg : type ID { ADD($2, $1); };

// Copy INT/FLOAT/BOOL into type
type : BOOL {strcpy($$, $1);} | INT {strcpy($$, $1);} | FLOAT {strcpy($$, $1);} ;

declList : decl SEMICOLON declList | ;

// Copy the type into the temprory string
decl : type {strcpy(temp, $1);} varList;

// Add the entry (Id, temp) the type you got from the declaration to the table
varList : ID {
    if (!strcmp(temp, "int")) {
        fprintf(fptr, "%%%d = alloca i32, align 4\n", size_of_table);
    }
    else {
        fprintf(fptr, "%%%d = alloca double, align 8\n", size_of_table);
    }
} COMMA varList {ADD($1, temp);} | ID {
    ADD($1, temp);
    if (!strcmp(temp, "int")) {
        fprintf(fptr, "%%%d = alloca i32, align 4\n", size_of_table);
    }
    else {
        fprintf(fptr, "%%%d = alloca double, align 8\n", size_of_table);
    }
    };

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

                if (!strcmp($3.expType, "int_const")) {
                    int temp = $3.expVal;
                    fprintf(fptr, "store i32 %d, i32* %%%d, align 4\n", temp, symbol_table[GET($1)].num);
                } 
                else if (!strcmp($3.expType, "int")) {
                    fprintf(fptr, "store i32 %%%d, i32* %%%d, align 4\n", $3.irName, symbol_table[GET($1)].num);
                }
                 else if (!strcmp($3.expType, "double_const")) {
                    fprintf(fptr, "store double %.6e, double* %%%d, align 8\n", $3.expVal, symbol_table[GET($1)].num);
                } 
                else {
                    fprintf(fptr, "store double %%%d, double* %%%d, align 8\n", $3.irName, symbol_table[GET($1)].num);
                }
            }
            ;


EXP : EXP '+' TERM  {strcpy($$, check_type($1, $3));}
    | EXP '-' TERM  {strcpy($$, check_type($1, $3));
                if (!strcmp($1.expType, "int_const") && !strcmp($3.expType, "int_const")) {
                    strcpy($$.expType, $1.expType);
                    $$.irName = $1.irName;
                    $$.expVal = $1.expVal - $3.expVal;
                }
                else if (!strcmp($1.expType, "double_const") && !strcmp($3.expType, "double_const")) {
                    strcpy($$.expType, $1.expType);
                    $$.irName = $1.irName;
                    $$.expVal = $1.expVal - $3.expVal;
                }
                else if (!strcmp($1.expType, "int") && !strcmp($3.expType, "int_const")) {
                    strcpy($$.expType, $1.expType);
                    count++;
                    $$.irName = count;
                    int tempval = $3.expVal;
                    int tempir = $1.irName;
                    fprintf(fptr, "%%%d = sub nsw i32 %%%d, %d\n", count, tempir, tempval);
                }
                else if (!strcmp($1.expType, "double") && !strcmp($3.expType, "double_const")) {
                    strcpy($$.expType, $1.expType);
                    count++;
                    $$.irName = count;
                    double tempval = $3.expVal;
                    int tempir = $1.irName;
                    fprintf(fptr, "%%%d = fsub double %%%d, %.6e\n", count, tempir, tempval);
                }
                else if (!strcmp($1.expType, "int_const") && !strcmp($3.expType, "int")) {
                    strcpy($$.expType, $3.expType);
                    count++;
                    $$.irName = count;
                    int tempval = $1.expVal;
                    int tempir = $3.irName;
                    fprintf(fptr, "%%%d = sub nsw i32 %d, %%%d\n", count, tempval, tempir);
                }
                else if (!strcmp($1.expType, "double_const") && !strcmp($3.expType, "double")) {
                    strcpy($$.expType, $3.expType);
                    count++;
                    $$.irName = count;
                    double tempval = $1.expVal;
                    int tempir = $3.irName;
                    fprintf(fptr, "%%%d = fsub double %.6e, %%%d\n", count, tempval, tempir);
                }
                else if (!strcmp($1.expType, "int") && !strcmp($3.expType, "int")) {
                    strcpy($$.expType, $1.expType);
                    count++;
                    $$.irName = count;
                    int tempir1 = $1.irName;
                    int tempir2 = $3.irName;
                    fprintf(fptr, "%%%d = sub nsw i32 %%%d, %%%d\n", count, tempir1, tempir2);
                }
                else if (!strcmp($1.expType, "double") && !strcmp($3.expType, "double")) {
                    strcpy($$.expType, $1.expType);
                    count++;
                    $$.irName = count;
                    int tempir1 = $1.irName;
                    int tempir2 = $3.irName;
                    fprintf(fptr, "%%%d = fsub double %%%d, %%%d\n", count, tempir1, tempir2);
                }
    }
    | TERM {strcpy($$, $1);
    strcpy($$.expType, $1.expType); 
    $$.expVal = $1.expVal;
    $$.irName = $1.irName;
    }
    ;

TERM : TERM '*' FACTOR {strcpy($$, check_type($1, $3));}
     | TERM '/' FACTOR {strcpy($$, check_type($1, $3));}
     | FACTOR {strcpy($$, $1);
      strcpy($$.expType, $1.expType);
      $$.expVal = $1.expVal;
      $$.irName = $1.irName;
     }
     ;

// for ID, Check if ID is in table if not return not declared
// for INT/FLOAT Const copy int/float to factor 
FACTOR : ID  {int idx = GET($1); if (idx != -1) {strcpy($$, symbol_table[idx].var_type);} else {strcpy($$, "Not Declared");}
strcpy($$.expType, symbol_table[symbol_table_lookup($1)].type);
    if (!strcmp($$.expType, "int")) {
        count++;
        $$.irName = count;
        fprintf(fptr, "%%%d = load i32, i32* %%%d, align 4\n", count, symbol_table[GET($1)].num);
    } 
    else {
        count++;
        $$.irName = count;
        fprintf(fptr, "%%%d = load double, double* %%%d, align 8\n", count, symbol_table[GET($1)].num);
    }
}
       | INT_CONST {strcpy($$, "int");
       strcpy($$.expType, "int_const");
       }
       | FLOAT_CONST {strcpy($$, "float");
       strcpy($$.expType, "double_const"); 
       }
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

void write_init_lines() {
    fprintf(fptr, "; ModuleID = 'out.ll'\nsource_filename = \"out.ll\"\ntarget datalayout = \"e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-pc-linux-gnu\"\n\n; Function Attrs: noinline nounwind optnone uwtable\n");
}

void write_closing_lines() {
    fprintf(fptr, "\nattributes #0 = { noinline nounwind optnone uwtable \"correctly-rounded-divide-sqrt-fp-math\"=\"false\" \"disable-tail-calls\"=\"false\" \"frame-pointer\"=\"all\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n\n");
    fprintf(fptr, "!llvm.module.flags = !{!0}\n!llvm.ident = !{!1}\n\n");
    fprintf(fptr, "!0 = !{i32 1, !\"wchar_size\", i32 4}\n!1 = !{!\"Debian clang version 11.0.1-2\"}");
    fclose(fptr);
}

int main(int argc, char **argv) {
    fptr = fopen("out.ll", "w");
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