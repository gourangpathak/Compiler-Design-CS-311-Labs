%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}

%%

[0-9]* {yylval.dval = atof(yytext); return number;}
[ \t] ;
[a-z] {yylval.vblno = yytext[0] - 'a'; return name;}
"$"   {return 0;}
\n    {return yytext[0];}
.     {return yytext[0];}
%%
