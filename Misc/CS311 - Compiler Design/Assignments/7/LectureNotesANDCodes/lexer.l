%{

#include "advanced_parser.tab.h"
#include "head.h"
%}

%%

[ \t]+ ;
"{"    { printf("Detected %s\n", yytext); return yytext[0]; }
"}"    { printf("Detected %s\n", yytext); return yytext[0];}
"("    { printf("Detected %s\n", yytext); return yytext[0];}
")"    { printf("Detected %s\n", yytext); return yytext[0];}
"="    { printf("Detected %s\n", yytext); return yytext[0]; }
","    { printf("Detected %s\n", yytext); return COMMA; }
";"    { printf("Detected %s\n", yytext); return SEMICOLON; }
"=="|">="|"<="|"!="|"<"|">" {printf("Detected %s\n", yytext); return RELOP;}
"||"   { printf("Detected %s\n", yytext); return OR; }
"&&"   { printf("Detected %s\n", yytext); return AND; }
"!"    { printf("Detected %s\n", yytext); return NOT; }
"if"   { printf("Detected %s\n", yytext); return IF; }
"while"   { printf("Detected %s\n", yytext); return WHILE; }
"+"|"-"|"/"|"*"    { printf("Detected %s\n", yytext); return yytext[0];}
"int"  { printf("Detected %s\n", yytext); strcpy(yylval.sval, "int"); return INT; }
"double"  { printf("Detected %s\n", yytext); strcpy(yylval.sval, "double"); return DOUBLE; }
[0-9]+     { printf("Detected const : %s\n", yytext); yylval.ival = atoi(yytext); return INT_CONST; }
[0-9]+"."[0-9]+     { printf("Detected const : %s\n", yytext); yylval.dval = (double)atoi(yytext); return DOUBLE_CONST; }
[A-Za-z0-9]* { printf("Detected ID : %s\n", yytext);  
               strcpy(yylval.sval, yytext); return ID; }
\n         { printf("Inside newline\n"); }
.          { return yytext[0];}
%%
