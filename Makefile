tlaloc: scanner_tlaloc.l parser_tlaloc.y semantic_structure.c semantic_structure.h
	bison -d parser_tlaloc.y
	flex scanner_tlaloc.l
	gcc -o $@  `pkg-config --cflags --libs glib-2.0` parser_tlaloc.tab.c lex.yy.c semantic_structure.c semantic_structure.h -lfl
