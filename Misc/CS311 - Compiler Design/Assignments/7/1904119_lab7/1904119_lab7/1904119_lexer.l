%{  
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "1904119_parser.tab.h"
%}

digit [0-9]
letter [a-zA-Z]
letter_or_digit { digit}|{letter}|[_]    

%%

[ \t]+                        { ; }
\/\*.*\*\/                    { printf("The comments are ignored\n"); }

[-]?{digit}+                  { strcpy(yylval.sval,yytext); printf("An INTEGER_CONSTANT : %s is encountered.\n", yytext); return INTEGER_CONSTANT ; }
[-]?{digit}*"."{digit}+       { strcpy(yylval.sval,yytext); printf("A DOUBLE_CONSTANT : %s is encountered.\n", yytext); return DOUBLE_CONSTANT ; }

"beg"                           { printf("Curly Open Bracket is encountered.\n");   return  BEG; }
"end"                           { printf("Curly Closed Bracket is encountered.\n"); return  END; }
"("                           { printf("Open Bracket is encountered.\n");         return  yytext[0]; }
")"                           { printf("Closed Bracket is encountered.\n");       return  yytext[0]; }

"="                           { printf("= is encountered\n"); return ASSIGN; }
">"|"<"|">="|"<="|"=="|"!="   { printf("Relational Operator is encountered.\n");  return RELOP; }

"&&"                          { printf("AND is encountered.\n"); return AND; }   
"||"                          { printf("OR is encountered.\n"); return OR; }
"!"                           { printf("NOT is encountered.\n"); return NOT; }

"+"|"*"|"/"|"-"|"+="|"−="|"∗="|"/=" { printf("An arithmetic operator : %s is encountered\n", yytext); return yytext[0]; }

";"                           { printf("SEMICOLON is encountered.\n"); return SEMICOLON; }
","                           { printf("COMMA is encountered.\n"); return COMMA; }

"if"                          { printf("IF is encountered.\n"); return IF; }
"else"                        { printf("ELSE is encountered.\n"); return ELSE; }
"else if"                     { printf("ELIF is encountered.\n"); return ELIF; }
"assign"                      { printf("ASSIGN is encountered.\n"); return ASSIGN; }

"int"                         { strcpy(yylval.sval,yytext); printf("INT is encountered.\n"); return INT; }
"double"                      { strcpy(yylval.sval,yytext); printf("DOUBLE is encountered.\n"); return DOUBLE; }
"char"                        { strcpy(yylval.sval,yytext); printf("CHAR is encountered.\n"); return CHAR; }

"while"                       { printf("WHILE is encountered.\n"); return WHILE; }
"return"                      { printf("RETURN is encountered.\n"); return RETURN; }

{letter}+                     { strcpy(yylval.sval,yytext); printf("ID %s is encountered.\n", yytext); return ID; }

"\n"                          { printf("A line is ended! \n"); }
.                             { printf("Some other character: %s is encountered", yytext); return yytext[0]; }

%%
