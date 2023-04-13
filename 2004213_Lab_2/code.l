%{
  #include<stdio.h>
  int maxlen = 0; 
%}

letter [a-zA-Z]
digit [0-9]

%% 

{letter}({letter}|{digit})* {
  if (yyleng > maxlen) {
    maxlen = yyleng;
  }
} ;

\n ;

[ \t]+ ;
%%
  
int main() {
  yylex();
  printf("largest identifier length: %d", maxlen);
  printf("\n");
}