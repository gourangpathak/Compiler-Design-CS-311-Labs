%{  
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "parser.tab.h"
%}

%%

[ \t\r]+                      ; 
"{"                           { printf("Detected %s\n", yytext);  return  yytext[0]; }
"}"                           { printf("Detected %s\n", yytext);  return  yytext[0]; }
"("                           { printf("Detected %s\n", yytext);  return  yytext[0]; }
")"                           { printf("Detected %s\n", yytext);  return  yytext[0]; }
"int"                         { printf("Detected %s\n", yytext); yylval.intval = strdup(yytext);  return INT; }
"float"                       { printf("Detected %s\n", yytext); yylval.floatval = strdup(yytext);  return FLOAT; }
"boolean"                     { printf("Detected %s\n", yytext); yylval.intval = strdup(yytext);  return BOOL; }
";"                           { printf("Detected %s\n", yytext); return SEMICOLON; }
","                           { printf("Detected %s\n", yytext); return COMMA; }
"="                           { printf("Detected %s\n", yytext);  return yytext[0]; }
">"|"<"|">="|"<="|"=="|"!="   { printf("Detected %s\n", yytext);  return RELOP; }
"&&"                          { printf("Detected %s\n", yytext); return AND; }   
"||"                          { printf("Detected %s\n", yytext); return OR; }
"!"                           { printf("Detected %s\n", yytext); return NOT; }
"+"|"*"|"/"|"-"               { printf("Detected %s\n", yytext);  return yytext[0]; }
"if"                          { printf("Detected %s\n", yytext);  return IF; }
"else"                        { printf("Detected %s\n", yytext);  return ELSE; }
"else if"                     { printf("Detected %s\n", yytext);  return ELIF; }
"while"                       { printf("Detected %s\n", yytext); return WHILE; }
"for"                         { printf("Detected %s\n", yytext); return FOR; }
[0-9]+                        { printf("Detected %s\n", yytext);  return INT_CONST ; }
[A-Za-z0-9]+                  { printf("Detected %s\n", yytext); yylval.intval = strdup(yytext);  return ID; }
[0-9]*"."[0-9]+               { printf("Detected %s\n", yytext);  return FLOAT_CONST ; }
\/\*.*\*\/                    { printf("Comments are ignored\n"); }
"\n"                          { printf("Inside newline\n");  }
.                             { return yytext[0]; }

%%