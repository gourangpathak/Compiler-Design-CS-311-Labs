%{
    /*
        Author  : Balijapelly Pranav
        Roll No : 1903108
    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int yylex(void);
int yyerror(char*);
#define MAX 100
#define filename "1903108_output.ll"
double vbltable[26];
char currType[50];
char currexp[MAX] ="";
int count=0;
int funccount=0;
int error=0;
int symbTabEntryCount=0;
FILE *fp;
char  Function_names[MAX][MAX];

struct table_entry
{
    char variable[100];
    char type[50]; 
    double expval;
    int    irName; 
}; 
struct table_entry symbol_table[MAX];
char file_buffer[MAX*MAX][MAX*MAX]; 
int filep=0;

    /*Functions declaration*/
void backpatch(int list[], int count, int label);
void write_init_lines();
void write_final_lines();
void write_alloc_instruction();
void write_load_instruction(int name,struct table_entry var);
void write_add_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval1,double expval2);
void write_sub_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval1,double expval2);
void write_mul_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval1,double expval2);
void write_store_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval);
void add_table(char* var);
char* type_check(char* var1,char* var2);
int strict_type_check(char* var1,char* var2);
struct table_entry get_var(char* var);
int addConditionalExp(double expVal1, char *expType1, int irName1, double expVal2, char *expType2, int irName2, char op);

%}

%union{
    int    ival;
    double fval;
    char   sval[20];
    struct expStruct
    {
        char variable[100];
        char type[20]; 
        double expval;
        int    irName; 
        struct bList
        {
            int ele[50];
            int count;
        } trueList, falseList;
    }eval;
    struct statementStruct
    {
        struct slist
        {
            int ele[50];
            int count;
        } nextList;
    }stmtVal;
    
};

%token <sval> ID INT DOUBLE CHAR INTEGER_CONSTANT FLOAT_CONSTANT 
%type <eval> exp TERM FACTOR rexp bexp 
%type <sval> Type
%type <stmtVal> assignStmt ifStmt stmtLists stmt stmtList whileStmt
%type<ival> M
%token SEMICOLON COMMA IF ELSE ELSEIF AND OR NOT WHILE RETURN RELOP Invalid BEG END


%left '-' '+'
%left '*' '/'
%left OR AND
%left NOT

%%

prog : {write_init_lines();}funcDef {write_final_lines();} {if(error==0) printf("parsed successfully\n");else printf("Exited with errors\n")};
funcDef : Type {strcpy(currType,$1);} ID {strcpy(Function_names[funccount],$3);funccount++;add_table($3);} '(' argList ')' BEG declList stmtList END
argList : arg COMMA arg | ;
arg : Type  ID {strcpy(currType,$1);add_table($2)};
Type : INT {strcpy($$,$1);} | DOUBLE {strcpy($$,$1);}|CHAR {strcpy($$,$1);};
declList : declList decl | decl;
decl : Type {strcpy(currType,$1);} varList SEMICOLON;
varList : ID COMMA 
        { add_table($1); write_alloc_instruction();} varList 
        | ID {add_table($1); write_alloc_instruction(); };
stmtList : stmtLists;
stmtLists : stmt M stmtLists {backpatch($1.nextList.ele, $1.nextList.count, $2);}|{ };
stmt : assignStmt { $$ = $1; } | ifStmt { $$ = $1; } | whileStmt;
assignStmt : ID '=' exp SEMICOLON
            {   
                int check=strict_type_check($1,$3.type);  
                struct table_entry dummy= get_var($1);
                if(check==1)write_store_instruction(dummy.irName,$3.irName,dummy.type,$3.type,$3.expval);
                $$.nextList.count = 0;
            } ;
exp : exp '+' TERM 
      {   
          char inp1[50],inp2[50];
          if(strcmp($1.type,"int")!=0 || strcmp($1.type,"double")!=0 ) strcpy(inp1,$1.type);
          else strcpy(inp1,$1.variable);
          if(strcmp($3.type,"int")!=0 || strcmp($3.type,"double")!=0 ) strcpy(inp2,$3.type);
          else strcpy(inp1,$3.variable);
          if((strcmp($1.type,"int_const")==0 && strcmp($3.type,"int_const")==0) || (strcmp($1.type,"double_const")==0 && strcmp($3.type,"double_const")==0)  ) {
              $$.expval= $1.expval + $3.expval;
              strcpy($$.type,$1.type);
          }
          else if((strcmp($1.type,"int_const")==0 && strcmp($3.type,"double_const")==0)){
              $$.expval= $1.expval*1.0 + $3.expval;
              strcpy($$.type,$3.type);
          }
          else if((strcmp($1.type,"double_const")==0 && strcmp($3.type,"int_const")==0)){
              $$.expval= $1.expval + $3.expval*1.0;
              strcpy($$.type,$1.type);
          }
          else{
            strcpy($$.type,type_check(inp1,inp2)); 
            write_add_instruction($1.irName,$3.irName,$1.type,$3.type,$1.expval,$3.expval); 
            $$.irName=symbTabEntryCount-1;
          }
      } 
      | exp '-' TERM {
            /*strcpy($$.type,type_check($1.variable,$3.variable)); */
            char inp1[50],inp2[50];
            if(strcmp($1.type,"int")!=0 || strcmp($1.type,"double")!=0 ) strcpy(inp1,$1.type);
            else strcpy(inp1,$1.variable);
            if(strcmp($3.type,"int")!=0 || strcmp($3.type,"double")!=0 ) strcpy(inp2,$3.type);
            else strcpy(inp1,$3.variable);
            if((strcmp($1.type,"int_const")==0 && strcmp($3.type,"int_const")==0) || (strcmp($1.type,"double_const")==0 && strcmp($3.type,"double_const")==0)  ) {
              $$.expval= $1.expval - $3.expval;
              strcpy($$.type,$1.type);
          }
          else if((strcmp($1.type,"int_const")==0 && strcmp($3.type,"double_const")==0)){
              $$.expval= $1.expval*1.0 - $3.expval;
              strcpy($$.type,$3.type);
          }
          else if((strcmp($1.type,"double_const")==0 && strcmp($3.type,"int_const")==0)){
              $$.expval= $1.expval - $3.expval*1.0;
              strcpy($$.type,$1.type);
          }
          else{
            strcpy($$.type,type_check(inp1,inp2)); 
            write_sub_instruction($1.irName,$3.irName,$1.type,$3.type,$1.expval,$3.expval); 
            $$.irName=symbTabEntryCount-1;
          }
        } 
      | TERM {$$=$1;};
TERM : TERM '*' FACTOR 
        {   char inp1[50],inp2[50];
          if(strcmp($1.type,"int")!=0 || strcmp($1.type,"double")!=0 ) strcpy(inp1,$1.type);
          else strcpy(inp1,$1.variable);
          if(strcmp($3.type,"int")!=0 || strcmp($3.type,"double")!=0 ) strcpy(inp2,$3.type);
          else strcpy(inp1,$3.variable);
          if((strcmp($1.type,"int_const")==0 && strcmp($3.type,"int_const")==0) || (strcmp($1.type,"double_const")==0 && strcmp($3.type,"double_const")==0)  ) {
              $$.expval= $1.expval * $3.expval;
              strcpy($$.type,$1.type);
          }
          else if((strcmp($1.type,"int_const")==0 && strcmp($3.type,"double_const")==0)){
              $$.expval= $1.expval*1.0 * $3.expval;
              strcpy($$.type,$3.type);
          }
          else if((strcmp($1.type,"double_const")==0 && strcmp($3.type,"int_const")==0)){
              $$.expval= $1.expval * $3.expval*1.0;
              strcpy($$.type,$1.type);
          }
          else{
            strcpy($$.type,type_check(inp1,inp2)); 
            write_mul_instruction($1.irName,$3.irName,$1.type,$3.type,$1.expval,$3.expval); 
            $$.irName=symbTabEntryCount-1;
          }
        }; 
        | TERM '/' FACTOR 
        {   
            /*strcpy($$.type,type_check($1.variable,$3.variable));*/
            char inp1[50],inp2[50];
            if(strcmp($1.type,"int")!=0 || strcmp($1.type,"double")!=0 ) strcpy(inp1,$1.type);
            else strcpy(inp1,$1.variable);
            if(strcmp($3.type,"int")!=0 || strcmp($3.type,"double")!=0 ) strcpy(inp2,$3.type);
            else strcpy(inp1,$3.variable);
            strcpy($$.type,type_check(inp1,inp2)); 
        } 
        | FACTOR {$$=$1;};
FACTOR : ID { struct table_entry dummy = get_var($1); 
              strcpy($$.variable,dummy.variable); 
              strcpy($$.type,dummy.type); 
              $$.irName=symbTabEntryCount;
              symbTabEntryCount++;
              $$.expval=dummy.expval; 
              write_load_instruction($$.irName,dummy);
            } 
        | INTEGER_CONSTANT 
            {   strcpy($$.type,"int_const"); 
                $$.expval=atof($1); 
            } 
        | FLOAT_CONSTANT 
            {   strcpy($$.type,"double_const"); 
                $$.expval=atof($1); 
            };
ifStmt : IF '(' bexp ')' M BEG stmtList{
            printf("in nii in \n\n");
            sprintf(file_buffer[filep],"\n\tbr label %%%d",symbTabEntryCount);
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
            } END el
        {   
            
            for(int i=0;i<$3.falseList.count;i<i++){
                $$.nextList.ele[i]=$3.falseList.ele[i];
                $$.nextList.count++;
            }
            int temp=$$.nextList.count;
            for(int i=0;i<$7.nextList.count;i++){
                $$.nextList.ele[temp+i]=$7.nextList.ele[i];
                $$.nextList.count++;
            }

        } ;
el: elses | elseIf |;
elses  : ELSE BEG stmtList END;
elseIf : ELSEIF '(' bexp ')' '{'stmtList '}' el;
rexp :exp '>' exp
     { 
        printf("in bolllll %f \n",$3.expval);
        strcpy($$.type, "bool"); 

        addConditionalExp($1.expval, $1.type, $1.irName, $3.expval, $3.type, $3.irName, '>'); 
        $$.falseList.count=0;
        $$.falseList.ele[0]=filep-2;
        $$.falseList.count++;
     };
rexp : exp RELOP exp|exp;
M     : {$$=symbTabEntryCount;}
bexp  : '('bexp')' {$$=$2;}|rexp|bexp AND bexp|bexp OR bexp| NOT bexp {$$=$2;};
whileStmt : WHILE '('bexp ')' BEG stmtList END {$$=$6;};
%%

/*This functions adds variable and it's type to the symbol table*/
void add_table(char* var){
    printf("##### %s #######\n",var);
    /*Check if already the variable is there in the symbol if not then add*/
    for(int vars=0;vars<count;vars++){
        if(strcmp(symbol_table[vars].variable,var)==0){
            if(strcmp(currType,symbol_table[vars].type)==0){
                error=1;
                printf("--------------------------------------------------------------\n");
                printf("ERROR : Redeclared the same varaible %s \n",var);
                printf("--------------------------------------------------------------\n");
                return;
            }
            else{
                error=1;
                printf("--------------------------------------------------------------\n");
                printf("ERROR : Redeclared the same varaible %s with different data types\n",var);
                printf("--------------------------------------------------------------\n");
                return;
            }
        }
    }
    /*If variable is bot present then copy and adding into symbol table*/
    strcpy(symbol_table[count].variable,var);
    strcpy(symbol_table[count].type,currType);
    symbol_table[count].irName=symbTabEntryCount;
    symbTabEntryCount++;
    count++;
    return;
}

/*This functions takes variable name and returns its entry in symbol if no variable if found it returns NULL */
struct table_entry get_var(char* var){
    struct table_entry check_type,dummy_type;
    bool flag=false;
    for(int vars=0;vars<count;vars++){
        if(strcmp(symbol_table[vars].variable,var)==0){
            check_type=symbol_table[vars];
            flag=true;
            break;
        }
    }
    /*If varaible is not found throwing error as undeclared variable encountered*/
    if(!flag){
        error=1;
        printf("--------------------------------------------------------\n");
        printf("ERROR : Undeclared variable %s encountered\n",var);
        printf("--------------------------------------------------------\n");
        strcpy(dummy_type.variable,"NULL");
        strcpy(dummy_type.type,"NULL");
        return dummy_type;
    }
    return check_type;
}


/*This functions takes 2 variables as input and returns resultant type of both variables i.e if both are int then result is int else  floqt*/
char* type_check(char *var1,char *var2){

    /* checking symbol table entry of var1 and getting it's type. If the given var1 itself is a type then type is taken as itself*/
    char check_type1[50],check_type2[50];
    if(strcmp(var1,"int")!=0 && strcmp(var1,"int_const")!=0 && strcmp(var1,"double")!=0 && strcmp(var1,"double_const")!=0 && strcmp(var1,"NULL")!=0){
        struct table_entry temp= get_var(var1);
        strcpy(check_type1,temp.type);
    }
    else{
        strcpy(check_type1,var1);
    }
    /*checking symbol table entry of var2 and getting it's type.  If the given var1 itself is a type then type is taken as itself*/
    if(strcmp(var2,"int")!=0 && strcmp(var2,"int_const")!=0 &&  strcmp(var2,"double")!=0 &&  strcmp(var2,"double_const")!=0 && strcmp(var2,"NULL")!=0){
        struct table_entry temp= get_var(var2);
        strcpy(check_type2,temp.type);
    }
    else{
        strcpy(check_type2,var2);
    }

    /*If any of the given variable is not declared then type of the expression is cannot be defined so result is NULL*/
    if(strcmp(check_type1,"NULL")==0 || strcmp(check_type2,"NULL")==0 ){
        return "NULL";
    }
    else if(strcmp(check_type1,"int_const")==0 && strcmp(check_type2,"int_const")==0)
        return "int_const";
    else if(strcmp(check_type1,"double_const")==0 && strcmp(check_type2,"double_const")==0)
        return "double_const"; 
    else if(strcmp(check_type1,"int")==0 && strcmp(check_type2,"int_const")==0 || strcmp(check_type1,"int_const")==0 && strcmp(check_type2,"int")==0){
        return "int";
    }
    else if(strcmp(check_type1,"double")==0 && strcmp(check_type2,"double_const")==0 || strcmp(check_type1,"double_const")==0 && strcmp(check_type2,"double")==0) 
        return "double";
    else if(strcmp(check_type1,"double")==0 && strcmp(check_type2,"int_const")==0 || strcmp(check_type1,"int_const")==0 && strcmp(check_type2,"double")==0) 
        return "double";
    else if(strcmp(check_type1,"double_const")==0 && strcmp(check_type2,"int")==0 || strcmp(check_type1,"int")==0 && strcmp(check_type2,"double_const")==0){
        return "double";
    }
    else if(strcmp(check_type1,check_type2)==0){
        if(strcmp(check_type1,"int")==0 ){
            return "int";    
        }
        else{
            return "double";
        }
    }
    else{
        return "double";
    }
}

/*This functions takes the type of LHS and RHS variables and checks if both of them matches*/
int strict_type_check(char *var1,char *var2){

    char check_type1[50],check_type2[50];
    /*checking symbol table entry of LHS variable and getting it's type.*/
    if(strcmp(var1,"int")!=0 && strcmp(var1,"int_const")!=0 && strcmp(var1,"double")!=0 && strcmp(var1,"double_const")!=0 && strcmp(var1,"NULL")!=0 ){
        struct table_entry temp= get_var(var1);
        strcpy(check_type1,temp.type);
        if(strcmp(check_type1,"int_const")==0){
            strcpy(check_type1,"int");
        }
        else if(strcmp(check_type1,"double_const")==0){
            strcpy(check_type1,"double");
        }
    }
    else{
        strcpy(check_type1,var1);
        if(strcmp(check_type1,"int_const")==0){
            strcpy(check_type1,"int");
        }
        if(strcmp(check_type1,"double_const")==0){
            strcpy(check_type1,"double");
        }
    }
    /*checking symbol table entry of RHS variable and getting it's type.*/
    if(strcmp(var2,"int")!=0 &&  strcmp(var2,"int_const")!=0 && strcmp(var2,"double")!=0 && strcmp(var2,"double_const")!=0 && strcmp(var2,"NULL")!=0 ){
        struct table_entry temp= get_var(var2);
        strcpy(check_type2,temp.type);
        if(strcmp(check_type2,"int_const")==0){
            strcpy(check_type2,"int");
        }
        if(strcmp(check_type2,"double_const")==0){
            strcpy(check_type2,"double");
        }
    }
    else{
        strcpy(check_type2,var2);
        if(strcmp(check_type2,"int_const")==0){
            strcpy(check_type2,"int");
        }
        if(strcmp(check_type2,"double_const")==0){
            strcpy(check_type2,"double");
        }
    }
    if(strcmp(check_type1,"double")==0){
        return 1;
    }
    /*if both are types did matches then returing with out an errors if they don't throwing errors*/
    if(strcmp(check_type1,check_type2)==0 ){
        return 1;
    }
    else if (strcmp(check_type1,"NULL")==0 || strcmp( check_type2,"NULL")==0){
        error=1;
        printf("------------------------------------------------------------------------------\n");
        printf("ERROR : L and R value types did not matched because of undeclared variable\n");
        printf("------------------------------------------------------------------------------\n");
        return 0;
    }
    else{
        error=1;
        printf("--------------------------------------------------\n");
        printf("ERROR : L and R value types did not matched\n");
        printf("--------------------------------------------------\n");
        return 0;
    }
}

void write_init_lines()
{
    fp= fopen(filename,"w");
    fprintf(fp,"; ModuleID = \'dummy.c\'\nsource_filename = \"dummy.c\"\ntarget datalayout = \"e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-pc-windows-msvc19.29.30142\"\n\n; Function Attrs: noinline nounwind optnone uwtable\ndefine dso_local i32 @main() #0 {");
}

void write_final_lines()
{   
    for(int i=0;i<filep;i++){
        fputs(file_buffer[i],fp);
    }
    fprintf(fp,"\n\tret i32 0\n}\n\nattributes #0 = { noinline nounwind optnone uwtable \"disable-tail-calls\"=\"false\" \"frame-pointer\"=\"none\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n\n!llvm.module.flags = !{!0, !1}\n!llvm.ident = !{!2}\n\n!0 = !{i32 1, !\"wchar_size\", i32 2}\n!1 = !{i32 7, !\"PIC Level\", i32 2}\n!2 = !{!\"clang version 12.0.1\"}");
}

void write_alloc_instruction(){
    if(strcmp(currType,"int")==0){
        sprintf(file_buffer[filep],"\n\t%%%d = alloca i32, align 4",symbTabEntryCount-1);
        filep++;
    }
    if(strcmp(currType,"double")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = alloca double, align 8",'%',symbTabEntryCount-1);
        filep++;
    }
}

void write_load_instruction(int name,struct table_entry var){
    if(strcmp(var.type,"int")==0){
        sprintf(file_buffer[filep],"\n\t%c%d =  load i32, i32* %c%d, align 4",'%',name,'%',var.irName);
        filep++;
    }
    if(strcmp(var.type,"double")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = load double, double* %c%d, align 8",'%',name,'%',var.irName);
        filep++;
    }
}

void write_add_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval1,double expval2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = add nsw i32 %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',irvar2);
        filep++;
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',irvar2);
        filep++;
    }
    else if(strcmp(type2,"int_const")==0 || strcmp(type1,"int_const")==0 ){
        if (strcmp(type1,"int_const")==0 ){
            if(strcmp(type2,"int")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = add nsw i32 %c%d,%d",'%',symbTabEntryCount,'%',irvar2,(int)expval1);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d,%f",'%',symbTabEntryCount,'%',irvar2,expval1);
                filep++;
            }
        }
        if (strcmp(type2,"int_const")==0){
            if(strcmp(type1,"int")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = add nsw i32 %c%d,%d",'%',symbTabEntryCount,'%',irvar1,(int)expval2);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d,%f",'%',symbTabEntryCount,'%',irvar1,expval2);
                filep++;
            }
        }
    }
    else if(strcmp(type2,"double_const")==0 || strcmp(type1,"double_const")==0){
        if (strcmp(type1,"double_const")==0)
            if (strcmp(type2,"double")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d,%f",'%',symbTabEntryCount,'%',irvar2,expval1);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar2);
                filep++;
                symbTabEntryCount++;
                sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d,%f",'%',symbTabEntryCount,'%',symbTabEntryCount-1,expval1);
                filep++;
            }
        if (strcmp(type2,"double_const")==0)
            if(strcmp(type1,"double")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d,%f",'%',symbTabEntryCount,'%',irvar1,expval2);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar1);
                filep++;
                symbTabEntryCount++;
                sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d,%f",'%',symbTabEntryCount,'%',symbTabEntryCount-1,expval2);
                filep++;
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar1);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d, %c%d",'%',symbTabEntryCount,'%',symbTabEntryCount-1,'%',irvar2);
            filep++;
        }
        if (strcmp(type2,"int")==0) {
            sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar2);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fadd double %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',symbTabEntryCount-1);
            filep++;
        }
    }
    symbTabEntryCount++;
}


void write_sub_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval1,double expval2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = sub nsw i32 %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',irvar2);
        filep++;
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',irvar2);
        filep++;
    }
    else if(strcmp(type2,"int_const")==0 || strcmp(type1,"int_const")==0 ){
        if (strcmp(type1,"int_const")==0 ){
            if(strcmp(type2,"int")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = sub nsw i32 %c%d,%d",'%',symbTabEntryCount,'%',irvar2,(int)expval1);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d,%f",'%',symbTabEntryCount,'%',irvar2,expval1);
                filep++;
            }
        }
        if (strcmp(type2,"int_const")==0){
            if(strcmp(type1,"int")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = sub nsw i32 %c%d,%d",'%',symbTabEntryCount,'%',irvar1,(int)expval2);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d,%f",'%',symbTabEntryCount,'%',irvar1,expval2);
                filep++;
            }
        }
    }
    else if(strcmp(type2,"double_const")==0 || strcmp(type1,"double_const")==0){
        if (strcmp(type1,"double_const")==0)
            if (strcmp(type2,"double")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d,%f",'%',symbTabEntryCount,'%',irvar2,expval1);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar2);
                filep++;
                symbTabEntryCount++;
                sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d,%f",'%',symbTabEntryCount,'%',symbTabEntryCount-1,expval1);
                filep++;
            }
        if (strcmp(type2,"double_const")==0)
            if(strcmp(type1,"double")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d,%f",'%',symbTabEntryCount,'%',irvar1,expval2);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar1);
                filep++;
                symbTabEntryCount++;
                sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d,%f",'%',symbTabEntryCount,'%',symbTabEntryCount-1,expval2);
                filep++;
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar1);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d, %c%d",'%',symbTabEntryCount,'%',symbTabEntryCount-1,'%',irvar2);
            filep++;
        }
        if (strcmp(type2,"int")==0) {
            sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar2);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fsub double %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',symbTabEntryCount-1);
            filep++;
        }
    }
    symbTabEntryCount++;
}



void write_mul_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval1,double expval2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = mul nsw i32 %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',irvar2);
        filep++;
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',irvar2);
        filep++;
    }
    else if(strcmp(type2,"int_const")==0 || strcmp(type1,"int_const")==0 ){
        if (strcmp(type1,"int_const")==0 ){
            if(strcmp(type2,"int")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = mul nsw i32 %c%d,%d",'%',symbTabEntryCount,'%',irvar2,(int)expval1);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d,%f",'%',symbTabEntryCount,'%',irvar2,expval1);
                filep++;
            }
        }
        if (strcmp(type2,"int_const")==0){
            if(strcmp(type1,"int")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = mul nsw i32 %c%d,%d",'%',symbTabEntryCount,'%',irvar1,(int)expval2);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d,%f",'%',symbTabEntryCount,'%',irvar1,expval2);
                filep++;
            }
        }
    }
    else if(strcmp(type2,"double_const")==0 || strcmp(type1,"double_const")==0){
        if (strcmp(type1,"double_const")==0)
            if (strcmp(type2,"double")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d,%f",'%',symbTabEntryCount,'%',irvar2,expval1);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar2);
                filep++;
                symbTabEntryCount++;
                sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d,%f",'%',symbTabEntryCount,'%',symbTabEntryCount-1,expval1);
                filep++;
            }
        if (strcmp(type2,"double_const")==0)
            if(strcmp(type1,"double")==0){
                sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d,%f",'%',symbTabEntryCount,'%',irvar1,expval2);
                filep++;
            }
            else{
                sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar1);
                filep++;
                symbTabEntryCount++;
                sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d,%f",'%',symbTabEntryCount,'%',symbTabEntryCount-1,expval2);
                filep++;
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar1);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d, %c%d",'%',symbTabEntryCount,'%',symbTabEntryCount-1,'%',irvar2);
            filep++;
        }
        if (strcmp(type2,"int")==0) {
            sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar2);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fmul double %c%d, %c%d",'%',symbTabEntryCount,'%',irvar1,'%',symbTabEntryCount-1);
            filep++;
        }
    }
    symbTabEntryCount++;
}


void write_store_instruction(int irvar1,int irvar2,char* type1,char* type2,double expval){
    if(strcmp(type2,"int_const")==0){
        if((strcmp(type1,"double")==0)){
            sprintf(file_buffer[filep],"\n\tstore double %f, double* %c%d, align 4",expval,'%',irvar1);
            filep++;
            return;
        }
        else{
            int new_expval=(int)expval;
            sprintf(file_buffer[filep],"\n\tstore i32 %d, i32* %c%d, align 4",new_expval,'%',irvar1);
            filep++;
            return;
        }
    }
    else if(strcmp(type2,"double_const")==0){
        sprintf(file_buffer[filep],"\n\tstore double %f, double* %c%d, align 8",expval,'%',irvar1);
        filep++;
        return;
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        sprintf(file_buffer[filep],"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',irvar2,'%',irvar1);
        filep++;
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        sprintf(file_buffer[filep],"\n\tstore double %c%d, double* %c%d, align 8",'%',irvar2,'%',irvar1);
        filep++;
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            sprintf(file_buffer[filep],"\n\t%c%d = fptosi double %c%d  to i32",'%',symbTabEntryCount,'%',irvar2);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',symbTabEntryCount-1,'%',irvar1);
            filep++;
        }
        if (strcmp(type2,"int")==0) {
            sprintf(file_buffer[filep],"\n\t%c%d = sitofp i32 %c%d  to double",'%',symbTabEntryCount,'%',irvar2);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\tstore double %c%d, double* %c%d, align 8",'%',symbTabEntryCount-1,'%',irvar1);
            filep++;
        }
    }
}


int addConditionalExp(double expVal1, char *expType1, int irName1, double expVal2, char *expType2, int irName2, char op)
{

    printf("%s %s %f\n",expType1,expType2,expVal1);
    if(op == '>')
    {   
        if((!strcmp(expType1, "int")) && (!strcmp(expType2, "int")))
        {
            /* Write icmp and br i1 statements to the file buffer */
            sprintf(file_buffer[filep],"\n\t%c%d = icmp sgt i32 %c%d,%c%d",'%',symbTabEntryCount,'%',irName1,'%',irName2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
            // printf("%s\n%s\n",file_buffer[0],file_buffer[1]);
        }
        else if((!strcmp(expType1, "double")) && (!strcmp(expType2, "double")))
        {
            /* Write fcmp and br i1 statements to the file buffer */
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',symbTabEntryCount,'%',irName1,'%',irName2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
            // printf("%s\n%s\n",file_buffer[0],file_buffer[1]);
        }
        else if((strcmp(expType1, "int")==0) && (strcmp(expType2, "int_const")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = icmp sgt i32  %c%d,%d",'%',symbTabEntryCount,'%',irName1,(int)expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((strcmp(expType1, "double")==0) && (strcmp(expType2, "double_const")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %c%d,%f",'%',symbTabEntryCount,'%',irName1,expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((strcmp(expType1, "int_const")==0) && (strcmp(expType2, "int")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = icmp sgt i32  %d,%%%d",'%',symbTabEntryCount,(int)expVal1,irName2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((strcmp(expType1, "double_const")==0) && (strcmp(expType2, "double")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',symbTabEntryCount,expVal1,irName2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((strcmp(expType1, "int_const")==0) && (strcmp(expType2, "int_const")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = icmp sgt i32  %d,%d",'%',symbTabEntryCount,(int)expVal1,(int)expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((strcmp(expType1, "double_const")==0) && (strcmp(expType2, "double_const")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %f,%f",'%',symbTabEntryCount,'%',expVal1,expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((strcmp(expType1, "int_const")==0) && (strcmp(expType2, "double_const")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %d,%f",'%',symbTabEntryCount,'%',(int)expVal1,expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((strcmp(expType1, "double_const")==0) && (strcmp(expType2, "int_const")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %f,%d",'%',symbTabEntryCount,'%',expVal1,(int)expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((!strcmp(expType1, "int")) && (!strcmp(expType2, "double")))
        {
            /* Write fcmp and br i1 statements to the file buffer */
            // %6 = sitofp i32 %5 to double
            sprintf(file_buffer[filep],"\n\t%%%d = sitofp i32 %%%d to double",symbTabEntryCount,irName1);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',symbTabEntryCount,'%',symbTabEntryCount-1,'%',irName2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
            // printf("%s\n%s\n",file_buffer[0],file_buffer[1]);
        }
        else if((!strcmp(expType1, "double")) && (!strcmp(expType2, "int")))
        {
            /* Write fcmp and br i1 statements to the file buffer */
            // %6 = sitofp i32 %5 to double
            sprintf(file_buffer[filep],"\n\t%%%d = sitofp i32 %%%d to double",symbTabEntryCount,irName2);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',symbTabEntryCount,'%',irName1,'%',symbTabEntryCount-1);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
            // printf("%s\n%s\n",file_buffer[0],file_buffer[1]);
        }
        else if((!strcmp(expType1, "int")) && (!strcmp(expType2, "double_const")))
        {
            /* Write fcmp and br i1 statements to the file buffer */
            // %6 = sitofp i32 %5 to double
            printf("here .........  %f \n",expVal2);
            sprintf(file_buffer[filep],"\n\t%%%d = sitofp i32 %%%d to double",symbTabEntryCount,irName1);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %c%d,%f ",'%',symbTabEntryCount,'%',symbTabEntryCount-1,expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
            // printf("%s\n%s\n",file_buffer[0],file_buffer[1]);
        }
        else if((strcmp(expType1, "int_const")==0) && (strcmp(expType2, "double")==0))
        {
            /* Handle constants */
            printf("here .........  %f \n",expVal1);
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',symbTabEntryCount,expVal1,irName2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
        else if((!strcmp(expType1, "double")) && (!strcmp(expType2, "int_const")))
        {
            /* Write fcmp and br i1 statements to the file buffer */
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %c%d,%f ",'%',symbTabEntryCount,'%',irName1,expVal2);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
            // printf("%s\n%s\n",file_buffer[0],file_buffer[1]);
        }
        else if((strcmp(expType1, "double_const")==0) && (strcmp(expType2, "int")==0))
        {
            /* Handle constants */
            sprintf(file_buffer[filep],"\n\t%%%d = sitofp i32 %%%d to double",symbTabEntryCount,irName2);
            filep++;
            symbTabEntryCount++;
            sprintf(file_buffer[filep],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',symbTabEntryCount,expVal1,symbTabEntryCount-1);
            filep++;
            sprintf(file_buffer[filep],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',symbTabEntryCount,'%',symbTabEntryCount+1,'%');
            symbTabEntryCount++;
            filep++;
            sprintf(file_buffer[filep],"\n%d:",symbTabEntryCount);
            filep++;
            symbTabEntryCount++;
        }
    }
    else
    {
        /* ignore */
    }
}



void backpatch(int list[], int count, int label){
    // printf("%d ........\n",label);
    for(int i=0;i<count;i++){
        printf(" in backpatch %s\n\n",file_buffer[list[i]]);
        char* temp=file_buffer[list[i]];
        int percount=0,j=0;
        while(percount!=3){
            if(temp[j]=='%')percount++;
            j++;
        }
        char* substr=&file_buffer[list[i]][j];
        sprintf(substr,"%d",label-1);
        // strcat(file_buffer[list[i]],substr);
        printf(" in backpatch %s\n\n",file_buffer[list[i]]); 
    }
}

int main(int argc, char **argv) {
	yyparse();
    /*Printing symbol Table*/
    printf("\nNumber of entries in symbol table is %d\n", count);
    printf("====================================\n");
    printf("|   Variable          Type         | \n");
    printf("====================================\n");
    for(int ele=0;ele<count;ele++){
        printf("| %s\t\t\t%s\t   |%d\n",symbol_table[ele].variable,symbol_table[ele].type,symbol_table[ele].irName);
    }
    printf("====================================\n");
    printf("Functions in code are \n", count);
    for(int ele=0;ele<funccount;ele++){
        printf("%s \n",Function_names[ele]);
    }
}

int yyerror(char *s)
{   
    fprintf(stderr, "%s\n", s);
}
