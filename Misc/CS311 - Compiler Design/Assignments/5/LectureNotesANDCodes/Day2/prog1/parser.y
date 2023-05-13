%{

#include <stdio.h>

int yylex(void);
int yyerror(char*);

double vbltable[26];
%}

%union {
	double dval;
        int    vblno;
};

%token <vblno> name
%token <dval>  number

%type <dval> expr
%%

statement_list: statement '\n'
               | statement_list statement '\n'
                ;
statement: name '=' expr { printf("vbl[%d] = %lf\n", $1, $3); vbltable[$1] = $3;}
               | expr {printf("%lf\n", $1);}
                ;
expr: expr '+' expr { $$ = $1 + $3;  }
    | expr '-' expr { $$ = $1 - $3;  }
    | expr '*' expr { $$ = $1 * $3;  }
    | number { $$ = $1; }
    | name { $$ = vbltable[$1]; printf("vbl[%d]\n", $1); }
    ;
%%

int main(int argc, char **argv) {
	yyparse();
}

int yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}
