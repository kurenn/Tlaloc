/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     METHOD = 259,
     PRINT = 260,
     PRINTLINE = 261,
     READ = 262,
     CASE = 263,
     DEFAULT = 264,
     DEFINE = 265,
     AS = 266,
     TO = 267,
     STEP = 268,
     INTEGER = 269,
     DECIMAL = 270,
     MAIN = 271,
     STRING = 272,
     BOOLEAN = 273,
     END = 274,
     FALSO = 275,
     VERDADERO = 276,
     VOID = 277,
     RETURN = 278,
     AND = 279,
     OR = 280,
     ABS = 281,
     COS = 282,
     SIN = 283,
     LOG = 284,
     TAN = 285,
     SQRT = 286,
     FOR = 287,
     WHILE = 288,
     IF = 289,
     SELECT = 290,
     ELSE = 291,
     PAR_ABIERTO = 292,
     PAR_CERRADO = 293,
     COMA = 294,
     DOS_PUNTOS = 295,
     CORCHETE_ABIERTO = 296,
     CORCHETE_CERRADO = 297,
     IGUAL = 298,
     IGUAL_IGUAL = 299,
     MENOR_QUE = 300,
     MAYOR_QUE = 301,
     DIFERENTE = 302,
     POR = 303,
     MAS = 304,
     MENOS = 305,
     DIVISION = 306,
     MAYOR_IGUAL = 307,
     MENOR_IGUAL = 308,
     EXPONENCIAL = 309,
     PUNTO = 310,
     APUNTADOR = 311,
     COMILLAS = 312,
     ID = 313,
     CTE_STRING = 314,
     CTE_DECIMAL = 315,
     CTE_INTEGER = 316
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define METHOD 259
#define PRINT 260
#define PRINTLINE 261
#define READ 262
#define CASE 263
#define DEFAULT 264
#define DEFINE 265
#define AS 266
#define TO 267
#define STEP 268
#define INTEGER 269
#define DECIMAL 270
#define MAIN 271
#define STRING 272
#define BOOLEAN 273
#define END 274
#define FALSO 275
#define VERDADERO 276
#define VOID 277
#define RETURN 278
#define AND 279
#define OR 280
#define ABS 281
#define COS 282
#define SIN 283
#define LOG 284
#define TAN 285
#define SQRT 286
#define FOR 287
#define WHILE 288
#define IF 289
#define SELECT 290
#define ELSE 291
#define PAR_ABIERTO 292
#define PAR_CERRADO 293
#define COMA 294
#define DOS_PUNTOS 295
#define CORCHETE_ABIERTO 296
#define CORCHETE_CERRADO 297
#define IGUAL 298
#define IGUAL_IGUAL 299
#define MENOR_QUE 300
#define MAYOR_QUE 301
#define DIFERENTE 302
#define POR 303
#define MAS 304
#define MENOS 305
#define DIVISION 306
#define MAYOR_IGUAL 307
#define MENOR_IGUAL 308
#define EXPONENCIAL 309
#define PUNTO 310
#define APUNTADOR 311
#define COMILLAS 312
#define ID 313
#define CTE_STRING 314
#define CTE_DECIMAL 315
#define CTE_INTEGER 316




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 69 "parser_tlaloc.y"
{
	char *str;
	int integer;
	float decimal;
}
/* Line 1529 of yacc.c.  */
#line 177 "parser_tlaloc.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

