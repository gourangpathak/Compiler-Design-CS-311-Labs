%{

#include "advanced_parser.tab.h"
#include "head.h"
int addToSymbTab(char *str);
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
"int"  { printf("Detected %s\n", yytext); return INT_CONST; }
[A-Za-z0-9]* { printf("Detected %s\n", yytext); int index = addToSymbTab(yytext); yylval.ival = index; return ID; }
\n         { printf("Inside newline\n"); }
.          { return yytext[0];}
%%
int addToSymbTab(char *str)
{
    return 0;
}
