%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yylex(void);
    int yyerror(char*);
    int cnt = 0;
    char cur_type[10];
    char cur_exp[50] ="";
    struct st_entry{
        char variable[50];
        char type[10]; 
    };
    struct st_entry symbol_table[50];
    void insert(char* var);
    char* typeChecker(char* var1,char* var2);
    void deepTypeChecker(char* var1,char* var2);

%}

%union{
    int    ival;
    double fval;
    char   sval[10];
};

%left '+' '-'
%left '/' '*'
%left AND OR
%left NOT


%token <sval> ID INTEGER_CONSTANT FLOAT_CONSTANT INT FLOAT CHAR 
%token SEMICOLON COMMA 
%token ASSIGN 
%token IF ELIF ELSE 
%token AND OR NOT 
%token WHILE RETURN 
%token RELOP INVALID 
%type <sval> type EXP TERM FACTOR


%%

prog : funcDef; 

funcDef : type {strcpy(cur_type, $1);} ID { insert($3); } '(' argList ')' '{' declList stmtList '}'

argList : arg COMMA arg | %empty;

arg : type ID { strcpy(cur_type,$1); insert($2); }

type      : INT {strcpy($$,$1);} | FLOAT {strcpy($$,$1);} | CHAR {strcpy($$,$1);};

declList  : declList decl | decl ;

decl      : type { strcpy(cur_type,$1); } varList SEMICOLON;

varList : ID {insert($1);} COMMA varList | ID {insert($1);};

stmtList : stmtList stmt | stmt;

stmt : assignStmt | ifStmt | whileStmt | elseIfStmt | elseStmt ;

assignStmt : ID ASSIGN EXP { deepTypeChecker($1, $3);} SEMICOLON;

EXP : EXP '+' TERM {strcpy($$,typeChecker($1,$3));} | EXP '-' TERM {strcpy($$,typeChecker($1,$3));} | TERM {strcpy($$,$1);};

TERM : TERM '*' FACTOR {strcpy($$,typeChecker($1,$3));}  | TERM '/' FACTOR {strcpy($$,typeChecker($1,$3));} | FACTOR {strcpy($$,$1);};

FACTOR : ID {strcpy($$,$1);} | INTEGER_CONSTANT {strcpy($$,"int");} |  FLOAT_CONSTANT {strcpy($$,"float");};

ifStmt : IF '(' bExp ')' '{' stmtList '}';

bExp : EXP RELOP EXP;

bExp : bExp AND bExp |  bExp OR bExp |  NOT '(' bExp ')' ;

whileStmt : WHILE '(' bExp ')' '{' stmtList '}';

elseIfStmt : ELIF '(' bExp ')' '{' stmtList '}' ; 

elseStmt : ELSE '{' stmtList '}' ; 

%%


struct st_entry fetch_entry(char* var){
    struct st_entry ans, dummy;
    int flag = 0;
    for(int i=0;i<cnt;i++){
        if(strcmp(symbol_table[i].variable,var) == 0){
            ans=symbol_table[i];
            flag=1;
            break;
        }
    }
    if(!flag){
        printf("----------> ERROR : Undeclared variable %s is encountered.                       <----------\n",var);
        strcpy(dummy.variable,"NULL");
        strcpy(dummy.type,"NULL");
        return dummy;
    }
    return ans;
}


void insert(char* var){
    // Inserting the variable & its type into the symbol table.

    for(int i=0;i<cnt;i++){
        if(strcmp(symbol_table[i].variable,var) == 0){      // If the variable name matched.
            if(strcmp(cur_type,symbol_table[i].type) == 0){ // If the type also matched.  
    
                printf("----------> ERROR : Redeclaration of the variable %s .                         <----------\n",var);
                return;
            }
            else{
                printf("----------> ERROR : Redeclaration of the variable %s with diff. data types.     <----------\n",var);
                return;
            }
        }
    }

    // Inserting the variable name and type into the symbol table.
    strcpy(symbol_table[cnt].variable,var);
    strcpy(symbol_table[cnt].type,cur_type);
    cnt++;
    return;
}


// This function deeply analyses the reason for the error incase it occured & prints to the console.
void deepTypeChecker(char *var1,char *var2){
    char *type1,*type2;

    // If var1 is not int, not float & also not NULL, Then we fetch the data type from the symbol table.
    if(strcmp(var1,"int")!=0 && strcmp(var1,"float")!=0 && strcmp(var1,"NULL")!=0){
        struct st_entry tmp = fetch_entry(var1);
        type1 = tmp.type;
    }
    else{
        type1 = var1;
    }

    // If var2 is not int, not float & also not NULL, Then we fetch the data type from the symbol table.
    if(strcmp(var2,"int")!=0 && strcmp(var2,"float")!=0 && strcmp(var2,"NULL")!=0){
        struct st_entry tmp = fetch_entry(var2);
        type2 = tmp.type;
    }
    else{
        type2 = var2;
    }

    if(strcmp(type1,type2) == 0){
    }
    else if (strcmp(type1,"NULL") == 0 || strcmp( type2,"NULL") == 0){
        printf("----------> ERROR : Types of LHS & RHS didn't match due to undeclared variable! <----------\n");

    }
    else{
        printf("----------> ERROR : Types of LHS & RHS didn't match!                            <----------\n");
    }
}


char* typeChecker(char *var1,char *var2){

    char *type1,*type2;

    // If var1 is not int, not float & also not NULL, Then we fetch the data type from the symbol table.
    if(strcmp(var1,"int")!=0 && strcmp(var1,"float")!=0 && strcmp(var1,"NULL")!=0){
        struct st_entry tmp = fetch_entry(var1);
        type1 = tmp.type;
    }
    else{
        type1 = var1;
    }

    // If var2 is not int, not float & also not NULL, Then we fetch the data type from the symbol table.
    if(strcmp(var2,"int")!=0 && strcmp(var2,"float")!=0 && strcmp(var2,"NULL")!=0){
        struct st_entry tmp = fetch_entry(var2);
        type2 = tmp.type;
    }
    else{
        type2 = var2;
    }

    if(strcmp(type1,"NULL") == 0 || strcmp(type2,"NULL") == 0 ){
        return "NULL";
    }
    else if( strcmp(type1,type2) == 0 ){   // If both types are same, we return type as usual.
        if(strcmp(type1,"int") == 0){
            return "int";    
        }
        else{
            return "float";
        }
    }
    else{                                  // If both types are different, we return float as type.
        return "float";
    }

}

int main(int argc, char **argv) {
	yyparse();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("|   variable              type     | \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for(int i=0;i<cnt;i++){
        printf("| \t%s\t\t%s\t   |\n",symbol_table[i].variable,symbol_table[i].type);
    }
}

int yyerror(char *s){
    fprintf(stderr, "error : %s\n", s);
}
