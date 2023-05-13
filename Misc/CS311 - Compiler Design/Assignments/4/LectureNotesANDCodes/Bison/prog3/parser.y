%{

#include <stdio.h>

int yylex(void);
int yyerror(char *s);

double vbltable[26];
%}

%union {
	double dval;
        int    vblno;
};

%token <vblno> name
%token <dval>  number

%type <dval> expr
%type <dval> term
%type <dval> factor
%%

statement_list: statement '\n'
               | statement_list statement '\n'
                ;
statement: name '=' expr {vbltable[$1] = $3;}
               | expr {printf("=%g\n", $1);}
                ;
expr: expr '+' term { $$ = $1 + $3; printf("Value (expr) %lf\n", $$);}
    | expr '-' term { $$ = $1 - $3; }
    | term { $$ = $1; }
    | name { $$ = vbltable[$1]; }
    ;

term: term '*' factor { $$ = $1 * $3; printf("Value (term) %lf\n", $$);}
    | factor          { $$ = $1; printf("Value (term) %lf\n", $$);}
    ;
factor: number { $$ = $1; printf("Value (factor) %lf\n", $$);}
    ;
%%

int main(int argc, char **argv) {
	yyparse();
}

int yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}
