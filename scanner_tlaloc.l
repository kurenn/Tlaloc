%{
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "parser_tlaloc.tab.h"
%}
%option noyywrap nodefault yylineno case-insensitive

%%

"program" 	{ yylval.str = strdup(yytext); return PROGRAM; }
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
"string" 	{ yylval.str = strdup(yytext); return STRING; }
"integer" 	{ yylval.str = strdup(yytext); return INTEGER; }
"decimal" 	{ yylval.str = strdup(yytext); return DECIMAL; }
"boolean" 	{ yylval.str = strdup(yytext); return BOOLEAN; }
"end" 		{ return END;}
"true" 		{ return VERDADERO; }
"false" 	{ return FALSO; }
"void" 		{ yylval.str = strdup(yytext); return VOID; }
"return" 	{ return RETURN; }
"and" 		{ return AND; }
"or" 		{ return OR; }
"abs" 		{ return ABS; }
"cos" 		{ return COS; }
"sin" 		{ return SIN; }
"log" 		{ return LOG; }
"tan" 		{ return TAN; }
"sqrt" 		{ return SQRT; }
"main"		{ yylval.str = strdup(yytext); return MAIN; }


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


[a-zA-Z_][a-zA-Z0-9_]*     { yylval.str = strdup(yytext); return ID; }
[0-9]+ 					   { yylval.integer = atoi(yytext); return CTE_INTEGER; }
[0-9]+\.[0-9]+ 			   { yylval.decimal = atof(yytext); return CTE_DECIMAL; }
\".*\"             		   { return CTE_STRING; }
\n
.
%%
