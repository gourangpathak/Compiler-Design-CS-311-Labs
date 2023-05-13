%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"


%}

%%

[ \t]+ ;
"begin"    { printf("Inside begin\n"); return BEG; }
"end"      { printf("Inside end\n"); return END;}
[A-Za-z0-9]*  { yylval.str = strdup(yytext); printf("str %s\n", yylval.str); return TEXT;}
"$"        { return 0;}
\n         { printf("Inside newline\n"); return yytext[0];}
.          { return yytext[0];}
%%
