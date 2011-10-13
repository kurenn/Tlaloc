bison -d parser_tlaloc.y 
flex scanner_tlaloc.l 
gcc -c lex.yy.c 
gcc -c parser_tlaloc.tab.c
gcc -o tlaloc lex.yy.o parser_tlaloc.tab.o -lfl
./tlaloc < main_test.txt
