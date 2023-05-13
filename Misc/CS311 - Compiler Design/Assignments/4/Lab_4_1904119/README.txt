- Designing a syntax analyzer using Bison which will accept an input code written in a toy programming language.

- There is one Input code file to test the program i.e. A Custom code written in C++ and named as `InputFile.cc` 
- Note that the zip file will also contain `lex.yy.c`, `Parser_1904119.tab.h`, `Parser_1904119.tab.c`, `a.out` 
	in addition to the files (bison, flex, input, README).

- To run Syntax analyzer, The following commands are to be executed in order : 
	--> bison -d Parser_1904119.y
	--> flex Lexer_1904119.l
	--> gcc Parser_1904119.tab.c lex.yy.c -lfl
	--> ./a.out < InputFile.cc

