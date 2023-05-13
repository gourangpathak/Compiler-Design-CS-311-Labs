%{

#include <stdio.h>

int yylex(void);
int yyerror(char*);


%}

%union{
    char *str;
}

%token BEG END 
%token <str> TEXT


%%


paragraph : BEG TEXT END { printf("A paragraph with string \"%s\" is seen\n", $2); } '\n'
          ;


%%

int main(int argc, char **argv) {
	yyparse();
}

int yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}
