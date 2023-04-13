%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"


%}

%%

[ \t]+ ;
\n           { printf("A newline is detected\n"); }
'+'          { printf("An operator %s is detected\n", yytext); return yytext[0];} 
'*'          { printf("An operator %s is detected\n", yytext); return yytext[0];} 
'='          { printf("An operator %s is detected\n", yytext); return yytext[0];} 
[0-9]+       { printf("An integer constant %s is detected\n", yytext); return INT_CONST;}
[A-Za-z]+    { printf("An identifier %s is detected\n", yytext); return ID; }
.            { printf("Other character %s is detected\n", yytext); return yytext[0];}
%%
