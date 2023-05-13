- The code for the Lexical Analyser is written in `flex` and named as `LexicalAnalyser_1904119.l`. 
	It performs all the tasks mentioned in the Assignment Doc of previous Lab Assignment. 
	In addition, it ignores the Block Comments ( Multi Line comments enclosed in /* and */ ) in the input code.

- It is assumed that the input code files are syntactically correct & can contain keywords as mentioned in the Assignment Doc.
- There is one Input code file on which the Lexical Analyser is tested i.e. A Custom code written in C++ and named as InputFile.cc 
- Note that the zip file will also contain `lex.yy.c` and `a.out` in addition to the files (flex, input, README).

- To run lexical analyzer, The following commands are to be executed in order : 
                    -->   flex LexicalAnalyser_1904119.l
				    -->   gcc lex.yy.c -lfl
				    -->   ./a.out < InputFile.cc

