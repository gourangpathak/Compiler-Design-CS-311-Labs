%{
    // Including all the required standard libraries.
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>

    // Declaring the standard parser related functions.
    int yylex(void);
    int yyerror(char*);

    // Declaring the character arrays ( Similar to strings ) to store the Type & expression.
    char cur_type[50];
    char cur_exp[100] ="";

    // Initialising the counters.
    int cnt = 0;
    int stCnt = 0;

    // Defining the file pointer.
    FILE *fp;

    // Custom Data Structure to represent the symbol table's entry.
    struct st_entry{
        char variable[100];
        char type[50]; 
        double eVal;
        int    irName; 
    }; 

    // Declaring the symbol table using above defined custom data structure.
    struct st_entry symbol_table[100];

    // Defining the array of strings to store the LLVM code being generated. Its corresponding index pointer is i.
    char fBuffer[100*100][100*100]; 
    int i=0;
    
    // Declaring the functions that convert to LLVM IR language.
    void allocInstr();
    void loadInstr(int name,struct st_entry var);
    void storeInstr(int ir1,int ir2,char* t1,char* t2,double eVal);
    void addInstr(int ir1,int ir2,char* t1,char* t2,double e1,double e2);
    void subInstr(int ir1,int ir2,char* t1,char* t2,double e1,double e2);
    void mulInstr(int ir1,int ir2,char* t1,char* t2,double e1,double e2);

    // Declaring the functions that insertEntry & fetch entries from symbol table.
    void insertEntry(char* var);
    struct st_entry getEntry(char* var);

    // Declaring the functions that perform type checking of given expression.
    char* typeChecker(char* v1,char* v2);
    int deepTypeChecker(char* v1,char* v2);
    
    // Declaring the functions that add the conditional expressions and do BackPatching to fill the labels.
    int condExpAdder(double e1, char *exp1, int ir1, double e2, char *exp2, int ir2, char op);
    void doBackPatch(int cnt, int lbl, int list[] );

    // Declaring the functions that add the stub code.
    void starter();
    void ender();
%}


%union{

    double fval;
    int    ival;
    char   sval[20];

    struct eStruct
    {
        char variable[100];
        char type[20]; 
        double eVal;
        int    irName; 
        
        // For boolean expressions, we have True & False Lists.
        struct blList
        {
            int ele[50];
            int cnt;
        } TRUE_List, FALSE_List;

    } eval;

    struct stmtStruct
    {   
        // For statements, we have Next list.
        struct slist    
        {
            int ele[50];
            int cnt;
        } nxtLst;
    } stmtVal;
    
};

%left '/' '*'
%left '+' '-'

%left NOT
%left AND OR

%token BEG END SEMICOLON IF ELSE ELSEIF COMMA  AND NOT WHILE RETURN OR  RELOP 
%token <sval> ID INT_CONST FLOAT_CONST INT DOUBLE CHAR

%type <ival> M
%type <sval> type
%type <eval> exp bexp rexp FACTOR TERM
%type <stmtVal> ifStmt stmt sList sLists whileStmt assnStmt

%%

prog : { starter(); } 
         funcDef 
       { ender(); }

funcDef : type { strcpy(cur_type,$1);  } ID {  insertEntry($3); } '(' argList ')' BEG declList sList END

argList : arg COMMA arg | ;

arg : type  ID {  
                  insertEntry($2);
                  strcpy(cur_type,$1);
              }

type :      INT { strcpy($$,$1); } 
       | DOUBLE { strcpy($$,$1); }
       | CHAR   { strcpy($$,$1); };

declList : declList decl | decl;

decl : type { strcpy(cur_type,$1); } varList SEMICOLON;

varList : ID COMMA { insertEntry($1); allocInstr();} varList 
        | ID       { insertEntry($1); allocInstr(); };

sList : sLists;

sLists : stmt M sLists {  doBackPatch($1.nxtLst.cnt, $2, $1.nxtLst.ele); } |  { };

stmt : assnStmt { $$ = $1; } 
      | ifStmt    { $$ = $1; } | whileStmt;

assnStmt : ID '=' exp SEMICOLON
            {   
                struct st_entry tmp = getEntry($1);

                if ( deepTypeChecker($1,$3.type) == 1 )
                    storeInstr(tmp.irName, $3.irName, tmp.type, $3.type, $3.eVal);

                $$.nxtLst.cnt = 0;
            };

exp : exp '+' TERM {

          // Note that, LHS of the expression "a+b" can be accessed using $1 and RHS can be accessed using $3.

          // If both sides have same type and they are constants, we can compute the value of expression and update.   
          if ( (strcmp($1.type, $3.type)==0 ) && ( strcmp($1.type,"INT_CONST")==0  || strcmp($1.type,"DOUBLE_CONST") ) ) {
              strcpy($$.type,$1.type);
              $$.eVal= $1.eVal + $3.eVal;
          }

          // If LHS is DOUBLE_CONST and RHS is INT_CONST, we convert right to double & do the computation.  
          else if((strcmp($1.type,"DOUBLE_CONST")==0 && strcmp($3.type,"INT_CONST")==0)){
              strcpy($$.type,$1.type);
              $$.eVal= $1.eVal + $3.eVal*1.0;
          }

          // If LHS is INT_CONST and RHS is DOUBLE_CONST, we convert left to double & do the computation.
          else if((strcmp($1.type,"INT_CONST")==0 && strcmp($3.type,"DOUBLE_CONST")==0)){
              strcpy($$.type,$3.type);
              $$.eVal= $1.eVal*1.0 + $3.eVal;
          }

          // In other cases, we call our typeChecker function to do the matching and then we write LLVM code for Add instruction.  
          else{

            // Update type.  
            strcpy($$.type,typeChecker($1.type, $3.type)); 
            
            // Call add instruction writing function.
            addInstr($1.irName,$3.irName,$1.type,$3.type,$1.eVal,$3.eVal); 
            
            $$.irName = stCnt-1;
          }
      } 

      | exp '-' TERM {
          
          // Note that, LHS of the expression "a-b" can be accessed using $1 and RHS can be accessed using $3.

          // If both sides have same type and they are constants, we can compute the value of expression and update.   
          if ( (strcmp($1.type, $3.type)==0 ) && ( strcmp($1.type,"INT_CONST")==0  || strcmp($1.type,"DOUBLE_CONST") ) ) {
              strcpy($$.type,$1.type);
              $$.eVal= $1.eVal - $3.eVal;
          }

          // If LHS is DOUBLE_CONST and RHS is INT_CONST, we convert right to double & do the computation.  
          else if((strcmp($1.type,"DOUBLE_CONST")==0 && strcmp($3.type,"INT_CONST")==0)){
              strcpy($$.type,$1.type);
              $$.eVal= $1.eVal - $3.eVal*1.0;
          }

          // If LHS is INT_CONST and RHS is DOUBLE_CONST, we convert left to double & do the computation.
          else if((strcmp($1.type,"INT_CONST")==0 && strcmp($3.type,"DOUBLE_CONST")==0)){
              strcpy($$.type,$3.type);
              $$.eVal= $1.eVal*1.0 - $3.eVal;
          }

          // In other cases, we call our typeChecker function to do the matching and then we write LLVM code for Add instruction.  
          else{

            // Update type.  
            strcpy($$.type,typeChecker($1.type, $3.type)); 
            
            // Call sub instruction writing function.
            subInstr($1.irName,$3.irName,$1.type,$3.type,$1.eVal,$3.eVal); 
            
            $$.irName = stCnt-1;
          }
        }

      | TERM { 
          $$ = $1;
        };

TERM : TERM '*' FACTOR 
        { 
            
          // Note that, LHS of the expression "a-b" can be accessed using $1 and RHS can be accessed using $3.

          // If both sides have same type and they are constants, we can compute the value of expression and update.   
          if ( (strcmp($1.type, $3.type)==0 ) && ( strcmp($1.type,"INT_CONST")==0  || strcmp($1.type,"DOUBLE_CONST") ) ) {
              strcpy($$.type,$1.type);
              $$.eVal= $1.eVal - $3.eVal;
          }

          // If LHS is DOUBLE_CONST and RHS is INT_CONST, we convert right to double & do the computation.  
          else if((strcmp($1.type,"DOUBLE_CONST")==0 && strcmp($3.type,"INT_CONST")==0)){
              strcpy($$.type,$1.type);
              $$.eVal= $1.eVal - $3.eVal*1.0;
          }

          // If LHS is INT_CONST and RHS is DOUBLE_CONST, we convert left to double & do the computation.
          else if((strcmp($1.type,"INT_CONST")==0 && strcmp($3.type,"DOUBLE_CONST")==0)){
              strcpy($$.type,$3.type);
              $$.eVal= $1.eVal*1.0 - $3.eVal;
          }

          // In other cases, we call our typeChecker function to do the matching and then we write LLVM code for Add instruction.  
          else{

            // Update type.  
            strcpy($$.type,typeChecker($1.type, $3.type)); 
            
            // Call sub instruction writing function.
            subInstr($1.irName,$3.irName,$1.type,$3.type,$1.eVal,$3.eVal); 
            
            $$.irName = stCnt-1;
          }

        }; 
        | TERM '/' FACTOR { strcpy($$.type,typeChecker($1.type,$3.type));  } 
        | FACTOR          {  $$ = $1; };

FACTOR : ID { 
              // Creating a temporary symbol table entry.  
              struct st_entry tmp = getEntry($1); 
              strcpy($$.type,tmp.type);       
              strcpy($$.variable,tmp.variable); 
          
              $$.irName = stCnt;      stCnt++;
              $$.eVal = tmp.eVal; 

              // Calling the load instruction writing function.  
              loadInstr($$.irName,tmp);
            }

        | INT_CONST {   
                $$.eVal = atof($1); 
                strcpy($$.type,"INT_CONST"); 
            } 

        | FLOAT_CONST {   
                $$.eVal = atof($1); 
                strcpy($$.type,"DOUBLE_CONST"); 
            };

ifStmt : IF '(' bexp ')' M BEG 
        sList {

            // Inserting the LLVM code into the File Buffer using corresponding pointer.
            sprintf(fBuffer[i],"\n\tbr label %%%d",stCnt);  i++;
            sprintf(fBuffer[i],"\n%d:",stCnt); i++;
            stCnt++;

        } 

        END el{   

            // Updating the next List of IF statement by merging accordingly.

            // Updating nxtLst with FALSE_List of boolean expression.
            for(int i=0; i< $3.FALSE_List.cnt; i<i++){
                $$.nxtLst.ele[i]=$3.FALSE_List.ele[i];
                $$.nxtLst.cnt++;
            }
            
            // Updating nxtLst with nxtLst of statement. 
            for(int i=0;i< $7.nxtLst.cnt;i++){
                $$.nxtLst.ele[$$.nxtLst.cnt+i]=$7.nxtLst.ele[i];
                $$.nxtLst.cnt++;
            }

        } ;


el: else_coll | elseIf |;

else_coll  : ELSE BEG sList END;

elseIf : ELSEIF '(' bexp ')' '{'sList '}' el;

M     : { $$ = stCnt; }

rexp :exp '>' exp
     {  // We took a specific example where ">" is the RELOP used between the expressions.

        // We know for (a > b), we get 2 conditional statements that will be added to the LLVM Code. They are 1. if (a>b) goto_ 2. goto_
        // Let's add them using the helper function "condExpAdder"
        condExpAdder($1.eVal, $1.type, $1.irName, $3.eVal, $3.type, $3.irName, '>'); 

        // Updating the FALSE_List
        $$.FALSE_List.cnt = 0;   
        $$.FALSE_List.ele[0] = i-2;
        $$.FALSE_List.cnt++;
     };

rexp : exp RELOP exp|exp;

bexp  : '('bexp')' { $$ = $2; } 
        | rexp | bexp AND bexp | bexp OR bexp| 
        NOT bexp   { $$ = $2; };

whileStmt : WHILE '('bexp ')' BEG sList END {  $$ = $6; };

%%

void starter()
{   
    // Helper function that adds the stub code at the beginning of LLVM code.
    fp = fopen("1904119_output.ll","w");

    fprintf(fp,"; ModuleID = \'1904119_parser.c\'\nsource_filename = \"1904119_parser.c\"\ntarget datalayout = \"e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\ntarget triple = \"x86_64-pc-windows-msvc19.27.29111\"\n\n; Function Attrs: noinline nounwind optnone uwtable\ndefine dso_local i32 @main() #0 {");
}

void ender()
{   // Helper function that adds the stub code at the ending of LLVM code.

    // Note that we have used array buffer to get the LLVM code using BackPatching. Now, Let's push in all the data from buffer to the file.
    for(int line =0; line < i; line++){
        fputs(fBuffer[line],fp);
    }

    for(int j=0;j<cnt;j++){
        printf("| \t%s\t\t%s\t   |\n",symbol_table[j].variable,symbol_table[j].type);
    }

    int req = symbol_table[cnt-1].irName;
    
    fprintf(fp, "\n\tret i32 %d", req);
    fprintf(fp,"\n}\n\nattributes #0 = { noinline nounwind optnone uwtable \"disable-tail-calls\"=\"false\" \"frame-pointer\"=\"none\" \"less-precise-fpmad\"=\"false\" \"min-legal-vector-width\"=\"0\" \"no-infs-fp-math\"=\"false\" \"no-jump-tables\"=\"false\" \"no-nans-fp-math\"=\"false\" \"no-signed-zeros-fp-math\"=\"false\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n\n!llvm.module.flags = !{!0, !1}\n!llvm.ident = !{!2}\n\n!0 = !{i32 1, !\"wchar_size\", i32 2}\n!1 = !{i32 7, !\"PIC Level\", i32 2}\n!2 = !{!\"clang version 12.0.1\"}");
}

void insertEntry(char* var){
    // Helper function for Inserting the variable & its type into the symbol table. 
    // If it is already exists, print an error message and return.

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
    
    // Incrementing the counters.
    stCnt++;
    cnt++;
}


struct st_entry getEntry(char* var){        
    // Helper function that gets the entry from the symbol table if the variable exists.

    struct st_entry helper, tmp;
    int flag=0;
    for(int i=0;i<cnt;i++){

        // If the variable name matches:
        if(strcmp(symbol_table[i].variable,var)==0){
            helper = symbol_table[i];
            flag=1;
            break;
        }
    }

    // If variable is not found we show an error as follows & return temporary/dummy entry:
    if(!flag){
        printf("----------> ERROR : Undeclared variable %s is encntered.                       <----------\n",var);
        strcpy(tmp.variable,"NULL");
        strcpy(tmp.type,"NULL");
        return tmp;
    }

    return helper ; 
}

int notATypeItself(char* var){
    // Helper function that returns 1/True if the var itself is not a type itself. 

    return strcmp(var, "int")!=0 && strcmp(var,"INT_CONST")!=0 && strcmp(var,"double")!=0 && strcmp(var,"DOUBLE_CONST")!=0 && strcmp(var,"NULL")!=0;
}

int encodeType(char* type){
    // Helper function that encodes the given type to an Integer.

    if (strcmp(type, "int") == 0){
        return 1;
    }
    if (strcmp(type, "INT_CONST") == 0){
        return 2;
    }
    if (strcmp(type, "double") == 0){
        return 3;
    }
    if (strcmp(type, "DOUBLE_CONST") == 0){
        return 4;
    }
    if (strcmp(type, "NULL") == 0){
        return 0;
    }
}

int doubleCheck(int enc_type1, int enc_type2){
    // Helper function that returns 1 if the encoding of the types should result in a type of "double".

    if (enc_type1 == 3 && enc_type2 == 4 || enc_type1 == 4 && enc_type2 == 3)
        return 1;
    else if (enc_type1 == 3 && enc_type2 == 2 || enc_type1 == 2 && enc_type2 == 3)
        return 1;
    else if (enc_type1 == 4 && enc_type2 == 1 || enc_type1 == 1 && enc_type2 == 4)
        return 1;
    return 0;
}

char* typeChecker(char *v1, char *v2){
    // Helper function that computes the type of expression formed using v1 (LHS) & v2 (RHS) matches.

    // If v1(LHS) is itself a type, we encode it directly.
    // Otherwise, We check the symbol table entry of v1 and fetch it's type & then encode the type using helper function.

    int enc_type1, enc_type2;

    if(notATypeItself(v1)){
        struct st_entry temp= getEntry(v1);
        enc_type1 = encodeType(temp.type);
    }
    else{
        enc_type1 = encodeType(v1);
    }

    // We do similar process as v1 for v2(RHS). 
    if(notATypeItself(v2)){
        struct st_entry temp = getEntry(v2);
        enc_type2 = encodeType(temp.type);
    }
    else{
        enc_type2 = encodeType(v2);
    }

    // Now, lets define the type of expression.

    if(  ( enc_type1 == 1 && enc_type2 == 2) || ( enc_type1 == 2 && enc_type2 == 1) )
        return "int";

     // If any 1 variable is not declared, type of expression cant be defined. So, we set NULL.    
    else if (enc_type1 == 0 || enc_type2 == 0)   
        return "NULL";

    // If both are INT_CONST, resulting expression is also INT_CONST.
    else if (enc_type1 == 2 && enc_type2 == 2)
        return "INT_CONST";

    // If both are DOUBLE_CONST, resulting expression is also DOUBLE_CONST.
    else if(enc_type1 == 4 && enc_type2 == 4)
        return "DOUBLE_CONST"; 

    else if (doubleCheck(enc_type1, enc_type2))
        return "double";
    
    else if(enc_type1 == enc_type2 && enc_type1 == 1)
        return "int";    
    
    else if(enc_type1 == enc_type2 && enc_type1 == 3)
        return "double";
    
    else
        return "double";
}

int deepTypeChecker(char *v1, char *v2){
    // Helper function that returns 1 the type of expression formed using v1 (LHS) & v2 (RHS) matches.

    // If v1 (LHS) is itself a type, we encode it directly.
    // Otherwise, We check the symbol table entry of v1 and fetch it's type & then encode the type using helper function.

    int enc_type1, enc_type2;

    if(notATypeItself(v1)){
        struct st_entry temp= getEntry(v1);
        enc_type1 = encodeType(temp.type);
    }
    else{
        enc_type1 = encodeType(v1);
    }

    // We do similar process as v1 for v2(RHS). 
    if(notATypeItself(v2)){
        struct st_entry temp = getEntry(v2);
        enc_type2 = encodeType(temp.type);
    }
    else{
        enc_type2 = encodeType(v2);
    }

    // Representing type_constant as type.
    if (enc_type1 ==2) enc_type1 = 1; 
    if (enc_type1 ==4) enc_type1 = 3; 
    if (enc_type2 ==2) enc_type2 = 1; 
    if (enc_type2 ==4) enc_type2 = 3; 

    // If LHS has double, irrespective of RHS, we can match. So, we return 1.
    if(enc_type1 == 3){
        return 1;
    }

    // If both types are matching. we return 1.
    if( enc_type1 == enc_type2 ){
        return 1;
    }

    // If any one type is undefined, we can return 0.
    else if ( enc_type1 == 0 || enc_type2 == 0 ){
        printf("----------> ERROR : Types of LHS & RHS didn't match due to undeclared variable! <----------\n");
        return 0;
    }

    // In other cases, we return 0.
    else{
        printf("----------> ERROR : Types of LHS & RHS didn't match!                            <----------\n");
        return 0;
    }
}


void allocInstr(){
    // Helper function that generates & stores the LLVM code WHEN ALLOATION is done.

    if(strcmp(cur_type,"int")==0){

        // Storing into buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%%%d = alloca i32, align 4",stCnt-1); i++;
    }

    if(strcmp(cur_type,"double")==0){

        // Storing into buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = alloca double, align 8",'%',stCnt-1); i++;
    }
}

void loadInstr(int name,struct st_entry var){
    // Helper function that generates & stores the LLVM code WHEN ALLOATION is done.
    
    if(strcmp(var.type,"int")==0){
        sprintf(fBuffer[i],"\n\t%c%d =  load i32, i32* %c%d, align 4",'%',name,'%',var.irName); i++;
    }

    if(strcmp(var.type,"double")==0){
        sprintf(fBuffer[i],"\n\t%c%d = load double, double* %c%d, align 8",'%',name,'%',var.irName); i++;
    }
}


void addHelperINT(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is INT_CONST.

    // If t1 is of INT_CONST.
    if (t1 == 2 ){
        if(t2 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir2,(int)e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
    }

    // If t2 is of INT_CONST.
    if (t2 == 2 ){
        if(t1 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = add nsw i32 %c%d,%d",'%',stCnt,'%',ir1,(int)e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
    }
}

void addHelperDOUBLE(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is DOUBLE_CONST.

    // If t1 is of DOUBLE_CONST.
    if (t1 == 4){
        if (t2 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,e1); i++;
        }
    }

    // If t2 is of DOUBLE_CONST.
    if (t2 == 4){
        if (t1 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d,%f",'%',stCnt,'%',stCnt-1,e2); i++;
        }
    }
}

void addInstr( int ir1, int ir2, char* t1, char* t2, double e1, double e2 ){
    // Helper function that generates the LLVM Code for the add instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);
    
    // If both types are int, we can straight away store the code.
    if ( enc_t1 == 1 && enc_t2 == 1 ){

        // Storing add instr(int) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = add nsw i32 %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }
    
    // If both types are double, we can straight away store the code too.
    else if(  enc_t1 == 3 && enc_t2 == 3 ){

        // Storing add instr(double) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }

    // If one of the type is INT_CONST
    else if(  enc_t1 == 2 || enc_t2 == 2 ){
        addHelperINT(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    // If one of the type is DOUBLE_CONST
    else if( enc_t1 == 4 || enc_t2 == 4 ){
        addHelperDOUBLE(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    else if( enc_t1 != enc_t2  && enc_t1 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    }

    else if( enc_t1 != enc_t2  && enc_t2 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fadd double %c%d, %c%d",'%',stCnt,'%',ir1,'%',stCnt-1); i++;
    }
    stCnt++;
}


void subHelperINT(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is INT_CONST.

    // If t1 is of INT_CONST.
    if (t1 == 2 ){
        if(t2 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir2,(int)e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
    }

    // If t2 is of INT_CONST.
    if (t2 == 2 ){
        if(t1 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = sub nsw i32 %c%d,%d",'%',stCnt,'%',ir1,(int)e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
    }
}

void subHelperDOUBLE(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is DOUBLE_CONST.

    // If t1 is of DOUBLE_CONST.
    if (t1 == 4){
        if (t2 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,e1); i++;
        }
    }

    // If t2 is of DOUBLE_CONST.
    if (t2 == 4){
        if (t1 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d,%f",'%',stCnt,'%',stCnt-1,e2); i++;
        }
    }
}

void subInstr( int ir1, int ir2, char* t1, char* t2, double e1, double e2 ){
    // Helper function that generates the LLVM Code for the add instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);
    
    // If both types are int, we can straight away store the code.
    if ( enc_t1 == 1 && enc_t2 == 1 ){

        // Storing sub instr(int) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = sub nsw i32 %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }
    
    // If both types are double, we can straight away store the code too.
    else if(  enc_t1 == 3 && enc_t2 == 3 ){

        // Storing sub instr(double) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }

    // If one of the type is INT_CONST
    else if(  enc_t1 == 2 || enc_t2 == 2 ){
        subHelperINT(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    // If one of the type is DOUBLE_CONST
    else if( enc_t1 == 4 || enc_t2 == 4 ){
        subHelperDOUBLE(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    else if( enc_t1 != enc_t2  && enc_t1 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    }

    else if( enc_t1 != enc_t2  && enc_t2 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fsub double %c%d, %c%d",'%',stCnt,'%',ir1,'%',stCnt-1); i++;
    }
    stCnt++;
}

void mulHelperINT(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is INT_CONST.

    // If t1 is of INT_CONST.
    if (t1 == 2 ){
        if(t2 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir2,(int)e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
    }

    // If t2 is of INT_CONST.
    if (t2 == 2 ){
        if(t1 == 1){
            sprintf(fBuffer[i],"\n\t%c%d = mul nsw i32 %c%d,%d",'%',stCnt,'%',ir1,(int)e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
    }
}

void mulHelperDOUBLE(int t1, int t2, int ir1, int ir2, double e1, double e2 ){
    // Helper function that is invoked to store the LLVM Code into buffer when one of the type is DOUBLE_CONST.

    // If t1 is of DOUBLE_CONST.
    if (t1 == 4){
        if (t2 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir2,e1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,e1); i++;
        }
    }

    // If t2 is of DOUBLE_CONST.
    if (t2 == 4){
        if (t1 == 3){
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',ir1,e2); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d,%f",'%',stCnt,'%',stCnt-1,e2); i++;
        }
    }
}

void mulInstr( int ir1, int ir2, char* t1, char* t2, double e1, double e2 ){
    // Helper function that generates the LLVM Code for the mul instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);
    
    // If both types are int, we can straight away store the code.
    if ( enc_t1 == 1 && enc_t2 == 1 ){

        // Storing mul instr(int) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = mul nsw i32 %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }
    
    // If both types are double, we can straight away store the code too.
    else if(  enc_t1 == 3 && enc_t2 == 3 ){

        // Storing mul instr(double) code into the buffer and incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    }

    // If one of the type is INT_CONST
    else if(  enc_t1 == 2 || enc_t2 == 2 ){
        mulHelperINT(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    // If one of the type is DOUBLE_CONST
    else if( enc_t1 == 4 || enc_t2 == 4 ){
        mulHelperDOUBLE(enc_t1, enc_t2, ir1, ir2, e1, e2);
    }

    else if( enc_t1 != enc_t2  && enc_t1 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir1); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    }

    else if( enc_t1 != enc_t2  && enc_t2 == 1 ){
            sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
            stCnt++;
            sprintf(fBuffer[i],"\n\t%c%d = fmul double %c%d, %c%d",'%',stCnt,'%',ir1,'%',stCnt-1); i++;
    }
    stCnt++;
}

void storeInstr(int ir1,int ir2,char* t1,char* t2,double eVal){
    // Helper function that generates the LLVM Code for the store instruction and stores into the file buffer.

    int enc_t1 = encodeType(t1), enc_t2 = encodeType(t2);

    if(enc_t2 == 2){
        if(enc_t1 == 3){
            sprintf(fBuffer[i],"\n\tstore double %f, double* %c%d, align 4",eVal,'%',ir1); i++;
        }
        else{
            sprintf(fBuffer[i],"\n\tstore i32 %d, i32* %c%d, align 4",(int)eVal,'%',ir1); i++;
        }
    }
    else if(enc_t2 == 4){
        sprintf(fBuffer[i],"\n\tstore double %f, double* %c%d, align 8",eVal,'%',ir1); i++;
    }
    else if( enc_t1 == 1 && enc_t2 == 1 ){
        sprintf(fBuffer[i],"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',ir2,'%',ir1); i++;
    }
    else if(enc_t1 == 3 && enc_t2 == 3){
        sprintf(fBuffer[i],"\n\tstore double %c%d, double* %c%d, align 8",'%',ir2,'%',ir1); i++;
    }
    else if( enc_t1 != enc_t2 && enc_t1 == 1 ){
        sprintf(fBuffer[i],"\n\t%c%d = fptosi double %c%d  to i32",'%',stCnt,'%',ir2); i++;
        stCnt++;
        sprintf(fBuffer[i],"\n\tstore i32 %c%d, i32* %c%d, align 4",'%',stCnt-1,'%',ir1); i++;
    }
    else if( enc_t1 != enc_t2 && enc_t2 == 1 ){
        sprintf(fBuffer[i],"\n\t%c%d = sitofp i32 %c%d  to double",'%',stCnt,'%',ir2); i++;
        stCnt++;
        sprintf(fBuffer[i],"\n\tstore double %c%d, double* %c%d, align 8",'%',stCnt-1,'%',ir1); i++;
    }
}


void ceh_int(double e1, double e2, int ir1, int ir2){
    // If both are of Integer Type.

    // Storing the icmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32 %c%d,%c%d",'%',stCnt,'%',ir1,'%',ir2); i++;
    
    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i. 
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void ceh_int_cons(double e1, double e2, int ir1, int ir2){
    // If both are of IntegerConstant Type.

    // Storing the icmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32  %d,%d",'%',stCnt,(int)e1,(int)e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void ceh_double(double e1, double e2, int ir1, int ir2){
    // If both are of Double Type.

    // Storing the fcmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',stCnt,'%',ir1,'%',ir2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');   i++;

    stCnt++;
    // Storing the new line with symbol table count & incrementing the i. 
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void ceh_double_cons(double e1, double e2, int ir1, int ir2){
    // If both are of DoubleConstant Type.

    // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %d,%f",'%',stCnt,'%',e1,e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void condExpHelper_same(char *exp1, double e1, double e2, int ir1, int ir2){
    // Helper function that gets invoked when the types of exp1 and exp2 are same inside condExpAdder function.

    if (strcmp(exp1, "int") == 0){
        ceh_int(e1, e2, ir1, ir2);
    }
    else if (strcmp(exp1, "double") == 0){
        ceh_double(e1, e2, ir1, ir2);
    }
    else if (strcmp(exp1, "INT_CONST") == 0){
        ceh_int_cons(e1, e2, ir1, ir2);
    }
    else if (strcmp(exp1, "DOUBLE_CONST") == 0){
        ceh_double_cons(e1, e2, ir1, ir2);
    }
}


void dc_1_int_cons(double e1, double e2){
     // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %d,%d",'%',stCnt,'%',(int)e1,e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;

    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void dc_2_int_cons(double e1, double e2){
    // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %d,%f",'%',stCnt,'%',e1,(int)e2); i++;

    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;

    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void diffCons(char *exp1, double e1, double e2){
    // Helper function that gets invoked when the types of exp1 and exp2 are both Constant types but not same.
    if (strcmp(exp1, "INT_CONST" ) == 0){
        dc_1_int_cons(e1, e2);
    }
    else{
        dc_2_int_cons(e1, e2);
    }
}


void  dc_2_int(int ir1, int ir2){
    // If exp1 is of INT type and exp2 is of DOUBLE type.

    // Storing the sitofp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir1); i++;
    stCnt++;
    
    // Storing the fcmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    
    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void  dc_1_int(int ir1, int ir2){
    // If exp1 is of INT type and exp2 is of DOUBLE type.
     
    // Storing the sitofp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir1); i++;
    stCnt++;
    
    // Storing the fcmp statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%c%d",'%',stCnt,'%',stCnt-1,'%',ir2); i++;
    
    // Storing the br i1 statement to our file buffer using i & incrementing the i.
    sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
    stCnt++;
    // Storing the new line with symbol table count & incrementing the i.
    sprintf(fBuffer[i],"\n%d:",stCnt); i++;
    stCnt++;
}

void diff(char *exp1, int ir1, int ir2){
    // Helper function that gets invoked when the types of exp1 and exp2 are both NOT Constant types but not same.
    if (strcmp(exp1, "int" ) == 0){
        dc_1_int(ir1, ir2);
    }
    else{
        dc_2_int(ir1, ir2);
    }
}

void rem_cases(double e1, char *exp1, int ir1, double e2, char *exp2, int ir2, char op){
    // Helper function that takes care of non trivial cases that happen in condExpAdder function and 
    // stores the LLVM IR code accordingly into the file buffer.
    
    // If exp1 is of DOUBLE type and exp2 is of INT_CONST type.
    if( strcmp(exp2, "INT_CONST") == 0 && strcmp(exp1, "double") == 0)
    {
        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%f ",'%',stCnt,'%',ir1,e2); i++;
        
        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
    
        // Storing the new line with symbol table count & incrementing the i.
        stCnt++; sprintf(fBuffer[i],"\n%d:",stCnt); i++;
        stCnt++;
    }

    // If exp1 is of INT type and exp2 is of DOUBLE_CONST type.
    else if( strcmp(exp1, "int") == 0 && strcmp(exp2, "DOUBLE_CONST") == 0)
    {   
        // Storing the sitofp statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir1); i++;
        stCnt++;

        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%f ",'%',stCnt,'%',stCnt-1,e2); i++;
        
        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
        
        stCnt++;
        // Storing the new line with symbol table count & incrementing the i.
        sprintf(fBuffer[i],"\n%d:",stCnt); i++;
        stCnt++;
    }

    // If exp1 is of INT_CONST type and exp2 is of DOUBLE type.
    else if((strcmp(exp1, "INT_CONST")==0) && (strcmp(exp2, "double")==0))
    {   
        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',stCnt,e1,ir2); i++;

        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
        
        stCnt++;
        // Storing the new line with symbol table count & incrementing the i.
        sprintf(fBuffer[i],"\n%d:",stCnt);  i++;
        stCnt++;
    }

    // If exp1 is of DOUBLE_CONST type and exp2 is of INT type.
    else if((strcmp(exp1, "DOUBLE_CONST")==0) && (strcmp(exp2, "int")==0))
    {
        // Storing the sitofp statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%%%d = sitofp i32 %%%d to double",stCnt,ir2); i++;
        stCnt++;
        
        // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',stCnt,e1,stCnt-1); i++;

        // Storing the br i1 statement to our file buffer using i & incrementing the i.
        sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
        
        stCnt++;
        // Storing the new line with symbol table count & incrementing the i.
        sprintf(fBuffer[i],"\n%d:",stCnt); i++;
        stCnt++;
    }
}

int condExpAdder(double e1, char *exp1, int ir1, double e2, char *exp2, int ir2, char op){
    // Helper function that adds the conditional expressions which are required in the BackPatching process.

    if(op == '>'){

        // Since we are concerned about only when the expression is exp1 > exp2, We take all possible cases of types in LHS & RHS
        // and store the corresponding LLVM Code into the buffer for future use.
        
        // If both are of INT_CONST Type.
        if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "INT_CONST") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }

        // If both are of Integer Type.
        else if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "int") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }
        
        // If exp1 is of INT type variable but exp2 is INT_CONST.
        else if((strcmp(exp1, "int")==0) && (strcmp(exp2, "INT_CONST")==0))
        {
            // Storing the icmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32  %c%d,%d",'%',stCnt,'%',ir1,(int)e2);   i++;
           
            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
            
            stCnt++;
            // Storing the new line with symbol table count & incrementing the i. 
            sprintf(fBuffer[i],"\n%d:",stCnt);  i++;
            stCnt++;
        }
        
        // If exp1 is of INT_CONST but exp2 is of INT type variable.
        else if((strcmp(exp1, "INT_CONST")==0) && (strcmp(exp2, "int")==0))
        {
            // Storing the icmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = icmp sgt i32  %d,%%%d",'%',stCnt,(int)e1,ir2);  i++;

            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%');  i++;
            
            stCnt++;
            // Storing the new line with symbol table count & incrementing the i. 
            sprintf(fBuffer[i],"\n%d:",stCnt);     i++;
            stCnt++;
        }

        // If both are of Double Type.
        else if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "double") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }

        // If both are of DOUBLE_CONST Type.
        else if(  strcmp(exp1, exp2) == 0 && strcmp(exp1, "DOUBLE_CONST") == 0 ){
            condExpHelper_same(exp1, e1, e2, ir1, ir2);
        }

        // If exp1 is of DOUBLE type variable but exp2 is DOUBLE_CONST.
        else if((strcmp(exp2, "DOUBLE_CONST")==0) && (strcmp(exp1, "double")==0))
        {
            // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %c%d,%f",'%',stCnt,'%',ir1,e2); i++;

            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
            
            // Storing the new line with symbol table count & incrementing the i. 
            stCnt++; sprintf(fBuffer[i],"\n%d:",stCnt); i++;
            stCnt++;
        }

        // If exp2 is of DOUBLE type variable & exp1 is of DOUBLE_CONST.
        else if((strcmp(exp1, "DOUBLE_CONST")==0) && (strcmp(exp2, "double")==0))
        {
            // Storing the fcmp statement ( Dealing with constants ) to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\t%c%d = fcmp ogt double  %f,%%%d",'%',stCnt,e1,ir2); i++;

            // Storing the br i1 statement to our file buffer using i & incrementing the i.
            sprintf(fBuffer[i],"\n\tbr i1 %c%d, label %c%d, label %c   \n",'%',stCnt,'%',stCnt+1,'%'); i++;
            
            stCnt++;
            // Storing the new line with symbol table count & incrementing the i. 
            sprintf(fBuffer[i],"\n%d:",stCnt); i++;
            stCnt++;
        }

        // If exp1 is of DOUBLE_CONST type and exp2 is of INT_CONST type.
        else if((strcmp(exp1, "DOUBLE_CONST")==0) && (strcmp(exp2, "INT_CONST")==0))
        {   
            diffCons(exp1, e1, e2);
        }

        // If exp1 is of INT_CONST type and exp2 is of DOUBLE_CONST type.
        else if((strcmp(exp1, "INT_CONST")==0) && (strcmp(exp2, "DOUBLE_CONST")==0))
        {       
            diffCons(exp1, e1, e2);
        }

        // If exp2 is of INT type and exp1 is of DOUBLE type.
        else if( strcmp(exp2, "int") == 0 &&  strcmp(exp1, "double") == 0 )
        {
            diff(exp1, ir1, ir2);
        }

        // If exp1 is of INT type and exp2 is of DOUBLE type.
        else if( strcmp(exp1, "int") == 0 &&  strcmp(exp2, "double") == 0 )
        {
            diff(exp1, ir1, ir2);
        }

        // Now lets deal with remaining cases.
        else{
            rem_cases(e1, exp1, ir1, e2, exp2, ir2, op );
        }
    }
}

void doBackPatch(int lcnt, int lbl, int list[]){
    // Helper function that does the job of BackPatching and fills the target labels in our LLVM code buffer accordingly.

    // Iterate over each index j to use list[j]
    for( int j = 0; j < lcnt; j++ ){
        
        // Finding the location (ind) to put the label.
        int pcnt = 0, ind = 0;
        for(; ; ind++){
            if (pcnt == 3) break;
            if ( fBuffer[list[j]][ind] == '%' ) 
                pcnt++;
        }

        // Updating the LLVM code in the buffer with the labels accordingly.
        sprintf(&fBuffer[list[j]][ind],"%d",lbl-1);
    }
}

int main(int argc, char **argv) {
	yyparse();
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("|   variable              type     | \n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for(int j=0;j<cnt;j++){
        printf("| \t%s\t\t%s\t   |\n",symbol_table[j].variable,symbol_table[j].type);
    }
}

int yyerror(char *s){
    fprintf(stderr, "error : %s\n", s);
}
