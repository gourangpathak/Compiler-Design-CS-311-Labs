%{

#include <stdio.h>

int yylex(void);
int yyerror(char*);


%}

%token BEG END TEXT 
%%
paragraph : BEG TEXT END { printf("A paragraph is seen\n"); } '\n'
          ;
%%

int main(int argc, char **argv) {
	yyparse();
}

int yyerror(char *s)
{
    fprintf(stderr, "error : %s\n", s);
}
