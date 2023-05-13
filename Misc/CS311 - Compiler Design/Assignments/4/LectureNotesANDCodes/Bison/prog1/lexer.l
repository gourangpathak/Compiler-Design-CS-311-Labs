%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"


%}

%%

[ \t]+ ;
"begin"       { printf("Inside begin\n"); return BEG; }
"end"         { printf("Inside end\n"); return END;}
[A-Za-z0-9]*  { printf("str %s\n", yytext); return TEXT;}
\n            { printf("The paragraph ended\n"); return yytext[0];}
.             { return yytext[0];}
%%
