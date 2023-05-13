%{  
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "Parser_1904119.tab.h"
%}

digit [0-9]
letter [a-zA-Z]
letter_or_digit { digit}|{letter}|[_]    

%%

[ \t]+                        { ; }
[-]?{digit}+                  { printf("An INTEGER_CONSTANT : %s is encountered.\n", yytext); return INTEGER_CONSTANT ; }
[-]?{digit}*"."{digit}+       { printf("A FLOAT_CONSTANT : %s is encountered.\n", yytext); return FLOAT_CONSTANT ; }

"{"                           { printf("Curly Open Bracket is encountered.\n");   return  yytext[0]; }
"}"                           { printf("Curly Closed Bracket is encountered.\n"); return  yytext[0]; }
"("                           { printf("Open Bracket is encountered.\n");         return  yytext[0]; }
")"                           { printf("Closed Bracket is encountered.\n");       return  yytext[0]; }

">"                           { printf("GT is encountered.\n"); return GT; }
">="                          { printf("GE is encountered.\n"); return GE; }
"<"                           { printf("LT is encountered.\n"); return LT; }
"<="                          { printf("LE is encountered.\n"); return LE; }

"&&"                          { printf("AND is encountered.\n"); return AND; }   
"||"                          { printf("OR is encountered.\n"); return OR; }
"!"                           { printf("NOT is encountered.\n"); return NOT; }
"=="                          { printf("EQ is encountered.\n"); return EQ; }
"!="                          { printf("NE is encountered.\n"); return NE; }

";"                           { printf("SEMICOLON is encountered.\n"); return SEMICOLON; }
","                           { printf("COMMA is encountered.\n"); return COMMA; }

"if"                          { printf("IF is encountered.\n"); return IF; }
"else"                        { printf("ELSE is encountered.\n"); return ELSE; }
"assign"                      { printf("ASSIGN is encountered.\n"); return ASSIGN; }

"int"                         { printf("INT is encountered.\n"); return INT; }
"float"                       { printf("FLOAT is encountered.\n"); return FLOAT; }
"char"                        { printf("CHAR is encountered.\n"); return CHAR; }

"while"                       { printf("WHILE is encountered.\n"); return WHILE; }
"return"                      { printf("RETURN is encountered.\n"); return RETURN; }

{letter}+                     { printf("ID %s is encountered.\n", yytext); return ID; }

"\n"                          { printf("A line is ended! \n"); }
.                             { ; }

%%
