%{
    #include <stdio.h>
    int charCount = 0;
    int lineCount = 0;
%}

%%
.        { charCount++; printf("char count %d ", charCount); printf("\n");}
\n       { lineCount++; printf("line count %d\n", lineCount); }
%%

int main()
{
    yylex();
    printf("Char count %d line count %d\n", charCount, lineCount);
}
