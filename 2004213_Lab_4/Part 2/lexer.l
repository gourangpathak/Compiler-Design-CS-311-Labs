%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}

%%

[ \t\r]+ ;
"{"    { printf("Detected %s\n", yytext); return yytext[0]; }
"}"    { printf("Detected %s\n", yytext); return yytext[0];}
"("    { printf("Detected %s\n", yytext); return yytext[0];}
")"    { printf("Detected %s\n", yytext); return yytext[0];}
"int"  { printf("Detected %s\n", yytext); return INT; }
"float"  { printf("Detected %s\n", yytext); return FLOAT; }
","    { printf("Detected %s\n", yytext); return COMMA; }
";"    { printf("Detected %s\n", yytext); return SEMICOLON; }
[A-Za-z0-9]+ { printf("Detected %s\n", yytext); return ID; }
\n         { printf("Inside newline\n"); }
.          { return yytext[0];}
%%
