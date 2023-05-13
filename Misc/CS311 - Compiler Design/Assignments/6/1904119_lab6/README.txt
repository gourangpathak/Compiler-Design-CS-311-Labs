- Designing a syntax analyzer using Bison which will accept an input code written in a toy programming language.

- Incorporating a symbol table which keeps track of all the variables and function names that are declared.
It will have two fields per variable, name and type, and these fields will be populated when any declaration statement is encountered.
For function names, it will have two fields, name and return type.

- Type-checking code for assignment statements is also included which shows appropriate errors.

- There are 2 Input code files to test the program i.e.
	- Code given as part of assignment which is named as `InputFile.cc`
	- A Custom code written in C++ and named as `customInputFile.cc` 

- Note that the zip file will also contain `lex.yy.c`, `1904119_parser.tab.h`, `1904119_parser.tab.c`, `a.out` 
	in addition to the files (bison, flex, input files, README).

- To run Syntax analyzer, The following commands are to be executed in order : 
	--> bison -d 1904119_parser.y
	--> flex 1904119_lexer.l
	--> gcc 1904119_parser.tab.c lex.yy.c -lfl -Ly
	--> ./a.out < InputFile.cc

