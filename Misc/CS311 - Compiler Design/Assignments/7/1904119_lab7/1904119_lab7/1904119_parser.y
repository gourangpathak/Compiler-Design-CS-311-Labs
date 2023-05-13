%{  
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylex(void);
    int yyerror(char*);
    int cnt = 0;
    int stCnt = 0;

    char cur_type[10];
    char cur_exp[50] ="";
    struct st_entry{
        char variable[50];
        char type[10]; 
        double expval;
        int irName;
    };
    struct st_entry symbol_table[50];

    void insert(char* var);
    char* typeChecker(char* var1,char* var2);
    int deepTypeChecker(char* var1,char* var2);
    struct st_entry fetch_entry(char* var);

    FILE *fp;
    void write_begin_lines();
    void write_end_lines();

    void write_alloc_instr();
    void write_load_instr(int name,struct st_entry var);
    void write_add_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2);
    void write_sub_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2);
    void write_mul_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2);
    void write_store_instr(int ir_var1,int ir_var2,char* type1,char* type2,double expval);

%}

%union{
    int    ival;
    double fval;
    char   sval[10];
    struct expStruct
    {
        char variable[50];
        char type[10]; 
        double expval;
        int    irName; 
    } eval;
};

%left '+' '-'
%left '/' '*'
%left AND OR
%left NOT


%token <sval> ID INTEGER_CONSTANT DOUBLE_CONSTANT INT DOUBLE CHAR 
%token SEMICOLON COMMA BEG END ASSIGN IF ELIF ELSE AND OR NOT WHILE RETURN RELOP INVALID 
%type <eval> EXP TERM FACTOR 
%type <sval> type


%%

prog : { write_begin_lines(); }  funcDef { write_end_lines(); }

funcDef : type {strcpy(cur_type, $1);} ID { insert($3); } '(' argList ')' BEG declList stmtList END

argList : arg COMMA arg | %empty;

arg : type ID { strcpy(cur_type,$1); insert($2); }

type      : INT {strcpy($$,$1);} | DOUBLE {strcpy($$,$1);} | CHAR {strcpy($$,$1);};

declList  : declList decl | decl ;

decl      : type { strcpy(cur_type,$1); } varList SEMICOLON;

varList : ID COMMA 
        { insert($1); write_alloc_instr(); } varList 
        | ID {insert($1); write_alloc_instr(); };

stmtList : stmtList stmt | stmt;

stmt : assignStmt | ifStmt | whileStmt | elseIfStmt | elseStmt ;

assignStmt : ID ASSIGN EXP 
            { 
                
                int check = deepTypeChecker($1, $3.type);
                struct st_entry tmp= fetch_entry($1);
                if(check==1) {
                    write_store_instr(tmp.irName,$3.irName,tmp.type,$3.type,$3.expval);
                }
                
            } SEMICOLON;

EXP : EXP '+' TERM 
      {   
          char inp1[50],inp2[50];
          if(strcmp($1.type,"int")!=0 || strcmp($1.type,"double")!=0 ) strcpy(inp1,$1.type);
          else strcpy(inp1,$1.variable);
          if(strcmp($3.type,"int")!=0 || strcmp($3.type,"double")!=0 ) strcpy(inp2,$3.type);
          else strcpy(inp1,$3.variable);

          if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"IntConst")==0) || (strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"DoubleConst")==0)  ) {
              $$.expval= $1.expval + $3.expval;
              strcpy($$.type,$1.type);
          }
          else if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"DoubleConst")==0)){
              $$.expval= $1.expval*1.0 + $3.expval;
              strcpy($$.type,$3.type);
          }
          else if((strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"IntConst")==0)){
              $$.expval= $1.expval + $3.expval*1.0;
              strcpy($$.type,$1.type);
          }
          
          if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"IntConst")==0) || (strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"DoubleConst")==0)  ) {
              $$.expval= $1.expval + $3.expval;
              strcpy($$.type,$1.type);
          }
          else{
            strcpy($$.type,typeChecker(inp1,inp2)); 
            write_add_instr($1.irName,$3.irName,$1.type,$3.type,$1.expval,$3.expval); 
            $$.irName=stCnt-1;
          }
      } 
      | EXP '-' TERM { 

            char inp1[50],inp2[50];
            if(strcmp($1.type,"int")!=0 || strcmp($1.type,"double")!=0 ) strcpy(inp1,$1.type);
            else strcpy(inp1,$1.variable);
            if(strcmp($3.type,"int")!=0 || strcmp($3.type,"double")!=0 ) strcpy(inp2,$3.type);
            else strcpy(inp1,$3.variable);

            if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"IntConst")==0) || (strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"DoubleConst")==0)  ) {
                $$.expval= $1.expval - $3.expval;
                strcpy($$.type,$1.type);
            }
            else if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"DoubleConst")==0)){
                $$.expval= $1.expval*1.0 - $3.expval;
                strcpy($$.type,$3.type);
            }
            else if((strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"IntConst")==0)){
                $$.expval= $1.expval - $3.expval*1.0;
                strcpy($$.type,$1.type);
            }

            if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"IntConst")==0) || (strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"DoubleConst")==0)  ) {
                $$.expval= $1.expval - $3.expval;
                strcpy($$.type,$1.type);
            }
            else{
            strcpy($$.type,typeChecker(inp1,inp2)); 
            write_add_instr($1.irName,$3.irName,$1.type,$3.type,$1.expval,$3.expval); 
            $$.irName=stCnt-1;
            }

        } 
      | TERM {$$=$1;};

TERM : TERM '*' FACTOR 
        {  
            
          char inp1[50],inp2[50];
          if(strcmp($1.type,"int")!=0 || strcmp($1.type,"double")!=0 ) strcpy(inp1,$1.type);
          else strcpy(inp1,$1.variable);
          if(strcmp($3.type,"int")!=0 || strcmp($3.type,"double")!=0 ) strcpy(inp2,$3.type);
          else strcpy(inp1,$3.variable);

          if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"IntConst")==0) || (strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"DoubleConst")==0)  ) {
              $$.expval= $1.expval * $3.expval;
              strcpy($$.type,$1.type);
          }
          else if((strcmp($1.type,"IntConst")==0 && strcmp($3.type,"DoubleConst")==0)){
              $$.expval= $1.expval*1.0 * $3.expval;
              strcpy($$.type,$3.type);
          }
          else if((strcmp($1.type,"DoubleConst")==0 && strcmp($3.type,"IntConst")==0)){
              $$.expval= $1.expval * $3.expval*1.0;
              strcpy($$.type,$1.type);
          }
          else{
            strcpy($$.type,typeChecker(inp1,inp2)); 
            write_mul_instr($1.irName,$3.irName,$1.type,$3.type,$1.expval,$3.expval); 
            $$.irName=stCnt-1;
          }

        }; 
        | TERM '/' FACTOR {strcpy($$.type,typeChecker($1.variable,$3.variable));} 
        | FACTOR {$$=$1;};

FACTOR : ID { 
              struct st_entry tmp = fetch_entry($1); 
              strcpy($$.variable,tmp.variable); 
              strcpy($$.type,tmp.type); 

              $$.irName=stCnt;
              stCnt++;
              
              $$.expval=tmp.expval; 
              write_load_instr($$.irName,tmp);
            } 
        | INTEGER_CONSTANT 
            {   strcpy($$.type,"IntConst"); 
                $$.expval=atof($1);
            } 
        | DOUBLE_CONSTANT {strcpy($$.type,"DoubleConst"); $$.expval=atof($1); };

ifStmt : IF '(' bExp ')' BEG stmtList END;

bExp : EXP RELOP EXP;

bExp : bExp AND bExp |  bExp OR bExp |  NOT '(' bExp ')' ;

whileStmt : WHILE '(' bExp ')' BEG stmtList END;

elseIfStmt : ELIF '(' bExp ')' BEG stmtList END ; 

elseStmt : ELSE BEG stmtList END ; 

%%


struct st_entry fetch_entry(char* var){
    struct st_entry ans, tmp;
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
        strcpy(tmp.variable,"NULL");
        strcpy(tmp.type,"NULL");
        return tmp;
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
    symbol_table[cnt].irName=stCnt;
    stCnt++;
    cnt++;
    return;
}

int deepTypeChecker(char *var1,char *var2){
    char type1[50],type2[50];
    if(strcmp(var1,"int")!=0 && strcmp(var1,"IntConst")!=0 && strcmp(var1,"double")!=0 && strcmp(var1,"DoubleConst")!=0 && strcmp(var1,"NULL")!=0 ){
        struct st_entry temp= fetch_entry(var1);
        strcpy(type1,temp.type);
        if(strcmp(type1,"IntConst")==0){
            strcpy(type1,"int");
        }
        else if(strcmp(type1,"DoubleConst")==0){
            strcpy(type1,"double");
        }
    }
    else{
        strcpy(type1,var1);
        if(strcmp(type1,"IntConst")==0){
            strcpy(type1,"int");
        }
        if(strcmp(type1,"DoubleConst")==0){
            strcpy(type1,"double");
        }
    }

    if(strcmp(var2,"int")!=0 &&  strcmp(var2,"IntConst")!=0 && strcmp(var2,"double")!=0 && strcmp(var2,"DoubleConst")!=0 && strcmp(var2,"NULL")!=0 ){
        struct st_entry temp= fetch_entry(var2);
        strcpy(type2,temp.type);
        if(strcmp(type2,"IntConst")==0){
            strcpy(type2,"int");
        }
        if(strcmp(type2,"DoubleConst")==0){
            strcpy(type2,"double");
        }
    }
    else{
        strcpy(type2,var2);
        if(strcmp(type2,"IntConst")==0){
            strcpy(type2,"int");
        }
        if(strcmp(type2,"DoubleConst")==0){
            strcpy(type2,"double");
        }
    }

    if(strcmp(type1,type2)==0 ){
        return 1;
    }
    else if (strcmp(type1,"NULL")==0 || strcmp( type2,"NULL")==0){
        printf("----------> ERROR : Types of LHS & RHS didn't match due to undeclared variable! <----------\n");
        return 0;
    }
    else{
        printf("----------> ERROR : Types of LHS & RHS didn't match!                            <----------\n");
        return 0;
    }
}


char* typeChecker(char *var1,char *var2){

    char type1[50],type2[50];
    if(strcmp(var1,"int")!=0 && strcmp(var1,"IntConst")!=0 && strcmp(var1,"double")!=0 && strcmp(var1,"DoubleConst")!=0 && strcmp(var1,"NULL")!=0){
        struct st_entry temp= fetch_entry(var1);
        strcpy(type1,temp.type);
    }
    else{
        strcpy(type1,var1);
    }

    if(strcmp(var2,"int")!=0 && strcmp(var2,"IntConst")!=0 &&  strcmp(var2,"double")!=0 &&  strcmp(var2,"DoubleConst")!=0 && strcmp(var2,"NULL")!=0){
        struct st_entry temp= fetch_entry(var2);
        strcpy(type2,temp.type);
    }
    else{
        strcpy(type2,var2);
    }

    if(strcmp(type1,"NULL")==0 || strcmp(type2,"NULL")==0 ){
        return "NULL";
    }
    else if(strcmp(type1,"IntConst")==0 && strcmp(type2,"IntConst")==0)
        return "IntConst";
    else if(strcmp(type1,"DoubleConst")==0 && strcmp(type2,"DoubleConst")==0)
        return "DoubleConst"; 
    else if(strcmp(type1,"int")==0 && strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 && strcmp(type2,"int")==0){
        return "int";
    }
    else if(strcmp(type1,"double")==0 && strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0 && strcmp(type2,"double")==0) 
        return "double";
    else if(strcmp(type1,"double")==0 && strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 && strcmp(type2,"double")==0) 
        return "double";
    else if(strcmp(type1,"DoubleConst")==0 && strcmp(type2,"int")==0 || strcmp(type1,"int")==0 && strcmp(type2,"DoubleConst")==0){
        return "double";
    }
    else if(strcmp(type1,type2)==0){
        if(strcmp(type1,"int")==0 ){
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


void write_begin_lines()
{   
    fp= fopen("1904119_output.ll","w");
    fprintf(fp,"; ModuleID = \'1.c\'\nsource_filename = \"1.c\"\ntarget datalayout = \"e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-pc-windows-msvc19.27.29111\"\n\n; Function Attrs: noinline nounwind optnone uwtable\ndefine dso_local i32 @main() #0 {");
}

void write_end_lines()
{   
    fprintf(fp,"\n\tret i32 0\n}\n\nattributes #0 = { noinline nounwind optnone uwtable \"disable-tail-calls\"=\"false\" \"frame-pointer\"=\"none\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n\n!llvm.module.flags = !{!0, !1}\n!llvm.ident = !{!2}\n\n!0 = !{i32 1, !\"wchar_size\", i32 2}\n!1 = !{i32 7, !\"PIC Level\", i32 2}\n!2 = !{!\"clang version 12.0.1\"}");
}

void write_alloc_instr(){
    if(strcmp(cur_type,"int")==0){
        fprintf(fp,"\n\t%c%d = alloca i32, align 4",'%',stCnt-1);
    }
    if(strcmp(cur_type,"double")==0){
        fprintf(fp,"\n\t%c%d = alloca double, align 8",'%',stCnt-1);
    }
}

void write_load_instr(int name,struct st_entry var){
    if(strcmp(var.type,"int")==0){
        fprintf(fp,"\n\t%c%d =  load i32, i32* %c%d, align 4",'%',name,'%',var.irName);
    }
    if(strcmp(var.type,"double")==0){
        fprintf(fp,"\n\t%c%d = load double, double* %c%d, align 8",'%',name,'%',var.irName);
    }
}


void write_add_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\t%c%d = add nsw i32 %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 ){
        if (strcmp(type1,"IntConst")==0 ){
            if(strcmp(type2,"int")==0)
                fprintf(fp,"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir_var2,(int)exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            }
        }
        if (strcmp(type2,"IntConst")==0){
            if(strcmp(type1,"int")==0)
                fprintf(fp,"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir_var1,(int)exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            }
        }
    }
    else if(strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0){
        if (strcmp(type1,"DoubleConst")==0)
            if (strcmp(type2,"double")==0)
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val1);
            }
        if (strcmp(type2,"DoubleConst")==0)
            if(strcmp(type1,"double")==0)
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val2);
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir_var2);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',stCnt-1);
        }
    }
    stCnt++;
}


void write_sub_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\t%c%d = sub nsw i32 %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 ){
        if (strcmp(type1,"IntConst")==0 ){
            if(strcmp(type2,"int")==0)
                fprintf(fp,"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir_var2,(int)exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            }
        }
        if (strcmp(type2,"IntConst")==0){
            if(strcmp(type1,"int")==0)
                fprintf(fp,"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir_var1,(int)exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            }
        }
    }
    else if(strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0){
        if (strcmp(type1,"DoubleConst")==0)
            if (strcmp(type2,"double")==0)
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val1);
            }
        if (strcmp(type2,"DoubleConst")==0)
            if(strcmp(type1,"double")==0)
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val2);
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir_var2);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',stCnt-1);
        }
    }
    stCnt++;
}


void write_mul_instr(int ir_var1,int ir_var2,char* type1,char* type2,double exp_val1,double exp_val2){
    if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\t%c%d = mul nsw i32 %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',ir_var2);
    }
    else if(strcmp(type2,"IntConst")==0 || strcmp(type1,"IntConst")==0 ){
        if (strcmp(type1,"IntConst")==0 ){
            if(strcmp(type2,"int")==0)
                fprintf(fp,"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir_var2,(int)exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            }
        }
        if (strcmp(type2,"IntConst")==0){
            if(strcmp(type1,"int")==0)
                fprintf(fp,"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir_var1,(int)exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            }
        }
    }
    else if(strcmp(type2,"DoubleConst")==0 || strcmp(type1,"DoubleConst")==0){
        if (strcmp(type1,"DoubleConst")==0)
            if (strcmp(type2,"double")==0)
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var2,exp_val1);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val1);
            }
        if (strcmp(type2,"DoubleConst")==0)
            if(strcmp(type1,"double")==0)
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir_var1,exp_val2);
            else{
                fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
                stCnt++;
                fprintf(fp,"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,exp_val2);
            }
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir_var2);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir_var1,'%',stCnt-1);
        }
    }
    stCnt++;
}

void write_store_instr(int ir_var1,int ir_var2,char* type1,char* type2,double expval){
    if(strcmp(type2,"IntConst")==0){
        int new_expval=(int)expval;
        fprintf(fp,"\n\tstore i32 %d, i32* %c%d, align 4",new_expval,'%',ir_var1);
    }
    else if(strcmp(type2,"DoubleConst")==0){
        fprintf(fp,"\n\tstore double %f, double* %c%d, align 8",expval,'%',ir_var1);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"int")==0){
        fprintf(fp,"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',ir_var2,'%',ir_var1);
    }
    else if(strcmp(type1,type2)==0 && strcmp(type1,"double")==0){
        fprintf(fp,"\n\tstore double %c%d, double* %c%d, align 8",'%',ir_var2,'%',ir_var1);
    }
    else if(strcmp(type1,type2)!=0 ){
        if (strcmp(type1,"int")==0)
        {
            fprintf(fp,"\n\t%c%d = fptosi double %c%d  to i32",'%',stCnt,'%',ir_var2);
            stCnt++;
            fprintf(fp,"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',stCnt-1,'%',ir_var1);
        }
        if (strcmp(type2,"int")==0) {
            fprintf(fp,"\n\t%c%d = fptosi i32 %c%d  to double",'%',stCnt,'%',ir_var1);
            stCnt++;
            fprintf(fp,"\n\tstore double %c%d, double* %c%d, align 8",'%',stCnt-1,'%',ir_var2);
        }
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
