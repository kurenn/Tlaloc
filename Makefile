tlaloc: scanner_tlaloc.l parser_tlaloc.y
	bison -d parser_tlaloc.y
	flex scanner_tlaloc.l
	gcc -o $@ parser_tlaloc.tab.c lex.yy.c -lfl
