- Designing a syntax analyzer using Bison which will accept an input code written in a toy programming language.

- There are 2 Input code files to test the program i.e.
	- Code given as part of assignment which is named as `InputFile.cc`
	- A Custom code written in C++ and named as `customInputFile.cc` 

- Note that the zip file will also contain `lex.yy.c`, `Parser_1904119.tab.h`, `Parser_1904119.tab.c`, `a.out` 
	in addition to the files (bison, flex, input Files, README).

- To run Syntax analyzer, The following commands are to be executed in order : 
	--> bison -d Parser_1904119.y
	--> flex Lexer_1904119.l
	--> gcc Parser_1904119.tab.c lex.yy.c -lfl -Ly
	--> ./a.out < InputFile.cc

