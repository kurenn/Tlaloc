%{
    /*
    Compilador y Máquina Virtual para el lenguaje de programación Tláloc, como proyecto académico. 

    Copyright (C) 2011 Eduardo López & Abraham Kuri

    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/gpl.html.
    */

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
"readint"   { return READINT; }
"readline" 	{ return READLINE; }
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
"true" 		{ yylval.str = strdup(yytext); return VERDADERO; }
"false" 	{ yylval.str = strdup(yytext); return FALSO; }
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
">="		{ return MAYOR_IGUAL; }
"<="		{ return MENOR_IGUAL; }


[a-zA-Z_][a-zA-Z0-9_]*     { yylval.str = strdup(yytext); return ID; }
[0-9]+ 					   { yylval.integer = atoi(yytext); return CTE_INTEGER; }
[0-9]+\.[0-9]+ 			   { yylval.str = strdup(yytext); return CTE_DECIMAL; }
\".*\"             		   { yylval.str = strdup(yytext); return CTE_STRING; }
\n
\b
\t
.
%%
