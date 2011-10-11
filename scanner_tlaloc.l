%{
	#include "parser_tlaloc.tab.h"
%}
%option yylineno
%%

"program" 	{ return PROGRAM; }
"method" 	{ return METHOD; }
"print" 	{ return PRINT; }
"printline" { return PRINTLINE; }
"read" 		{ return READ; }
"case" 		{ return CASE; }
"default" 	{ return DEFAULT; }
"define" 	{ return DEFINE; }
"as" 		{ return AS; }
"to" 		{ return TO; }
"step" 		{ return STEP; }
"string" 	{ return STRING; }
"integer" 	{ return INTEGER; }
"decimal" 	{ return DECIMAL; }
"boolean" 	{ return BOOLEAN; }
"end" 		{ return END;}
"true" 		{ return VERDADERO; }
"false" 	{ return FALSO; }
"void" 		{ return VOID; }
"return" 	{ return RETURN; }
"and" 		{ return AND; }
"or" 		{ return OR; }
"abs" 		{ return ABS; }
"cos" 		{ return COS; }
"sin" 		{ return SIN; }
"log" 		{ return LOG; }
"tan" 		{ return TAN; }
"sqrt" 		{ return SQRT; }


"for" 		{ return FOR; }
"while" 	{ return WHILE; }


"if" 		{ return IF; }
"else" 		{ return ELSE; }
"select" 	{ return SELECT; }


"("    		{ return PAR_ABIERTO; }     
")"    		{ return PAR_CERRADO; }     
","    		{ return COMA;}             
":"    		{ return DOS_PUNTOS; }       
"["    		{ return CORCHETE_ABIERTO; }
"]"    		{ return CORCHETE_CERRADO; }
"=" 		{ return IGUAL; }           
"==" 		{ return IGUAL_IGUAL;}
"<" 		{ return MENOR_QUE; }
">" 		{ return MAYOR_QUE; }
"<>" 		{ return DIFERENTE; }
"*" 		{ return POR; }
"+" 		{ return MAS; }
"-" 		{ return MENOS; }
"/" 		{ return DIVISION; }
"^" 		{ return EXPONENCIAL; }
"." 		{ return PUNTO; }
"->"		{ return APUNTADOR; }
"\""		{ return COMILLAS; }


[a-zA-Z]([a-zA-Z]|[0-9])* { return ID; }
[0-9]+ 					  { return CTE_INTEGER; }
[0-9]+\.[0-9]+ 			  { return CTE_DECIMAL; }
\".*\"             		  { return CTE_STRING; }
\n
.
%%