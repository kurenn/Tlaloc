tlaloc: scanner_tlaloc.l parser_tlaloc.y hashing_tables.c hashing_tables.h
	bison -d parser_tlaloc.y --verbose --report=all 
	flex scanner_tlaloc.l
	gcc -o $@  `pkg-config --cflags --libs glib-2.0` parser_tlaloc.tab.c lex.yy.c hashing_tables.c hashing_tables.h -lfl
