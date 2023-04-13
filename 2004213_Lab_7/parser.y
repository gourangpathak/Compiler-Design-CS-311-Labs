%{
#include <stdio.h>
#include <string.h>
#include "parser.tab.h"
int yylex(void);
int yyerror(char *);
%}

%token id 
 

%%
  E : E '+' E
  E : E '*' E
  E : id
%%


int main(int argc, char **argv) {
	yyparse();
}

