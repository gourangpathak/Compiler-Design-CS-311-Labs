- There are 2 Input code files to test the program i.e.
	- Code given as part of assignment which is named as `InputFile` 
	- Custom Input file named as `InputFile2`

- To run Syntax analyzer, The following commands are to be executed in order : 
	--> bison -d 1904119_parser.y
	--> flex 1904119_lexer.l
	--> gcc 1904119_parser.tab.c lex.yy.c -lfl -Ly
	--> ./a.out < InputFile
    --> lli 1904119_output.ll  ( Run in the command Prompt. Not the WSL Terminal. )

