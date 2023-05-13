%{  
    #include <stdio.h>
    #include <stdlib.h>
    #include "1904119_parser.tab.h"
%}

digit [0-9]
letter [a-zA-Z]
letter_or_digit {digit}|{letter}

%%

[" "|\t]                     { }
\/\*.*\*\/                   { printf("The comments are removed.\n"); }

">"                          { printf("The following greaterThan Operator: %s is encountered\n", yytext); return yytext[0]; }    
"+"|"-"|"="|"*"|"/"          { printf("The following arithmetic operator : %s is encountered\n", yytext); return yytext[0]; }
"<"|">="|"<="|"=="|"!="      { printf("The following relational operator : %s is encountered.\n", yytext);  return RELOP; }
"("|")"|"["|"]"              { printf("The following symbol : %s is encountered\n", yytext); return yytext[0]; }

"char"                       {  printf("The following keyword : %s is encountered\n", yytext); strcpy(yylval.sval,yytext); return CHAR; }
"int"                        {  printf("The following keyword : %s is encountered\n", yytext); strcpy(yylval.sval,yytext); return INT; }
"double"                     {  printf("The following keyword : %s is encountered\n", yytext); strcpy(yylval.sval,yytext); return DOUBLE; }

"||"                         { printf("The following symbol : %s is encountered\n", yytext); return OR; }
"!"                          { printf("The following symbol : %s is encountered\n", yytext); return NOT; }
"&&"                         { printf("The following symbol : %s is encountered\n", yytext); return AND; }

"while"                      { printf("The following keyword : %s is encountered\n", yytext); return WHILE; }
"return"                     { printf("The following keyword : %s is encountered\n", yytext); return RETURN; }

"if"                         { printf("The following keyword : %s is encountered\n", yytext); return IF; }
"else"                       { printf("The following keyword : %s is encountered\n", yytext); return ELSE; }
"else if"                    { printf("The following keyword : %s is encountered\n", yytext); return ELSEIF; }

"beg"                        { printf("The following symbol : %s is encountered\n", yytext); return BEG; }
"end"                        { printf("The following symbol : %s is encountered\n", yytext); return END; }

";"                          { printf("Semicolon is encountered\n"); return SEMICOLON; }
","                          { printf("Comma is encountered\n"); return COMMA; }

"-"?{digit}+                 { printf("The following Integer Constant        : %s is encountered\n", yytext); strcpy(yylval.sval,yytext); return INT_CONST; }
[-]?{digit}*"."{digit}+      { printf("The following Floating Point Constant : %s is encountered\n", yytext); strcpy(yylval.sval,yytext); return FLOAT_CONST; }             

{letter}{letter_or_digit}*   { printf("The following Identifier              : %s is encountered\n", yytext); strcpy(yylval.sval,yytext); return ID; }

\n                           { }    

%%