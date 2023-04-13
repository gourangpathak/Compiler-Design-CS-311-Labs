%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
int yylex(void);
int yyerror(char *);
%}


%token ID INT_CONST 
%%
S : ID '=' E { printf("The rule with equal to operator is triggered\n"); }
E : E '+' T { printf("The rule with plus operator is triggered\n"); }
E : T { printf("The rule  E = T is triggered\n"); }
T : T '*' F { printf("The rule * operator is triggered\n"); }
T : F { printf("The rule T = F is triggered\n"); }
F : ID { printf("The rule with ID is triggered\n"); }
F : INT_CONST { printf("The rule with ID is triggered\n"); }
%%

int main()
{
    yyparse();
}

int yyerror(char *s) {
    fprintf(stderr,"An Error in the parser is : %s\n", s);
}
