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
     STRING = 269,
     INTEGER = 270,
     DECIMAL = 271,
     BOOLEAN = 272,
     END = 273,
     FALSO = 274,
     VERDADERO = 275,
     VOID = 276,
     RETURN = 277,
     AND = 278,
     OR = 279,
     ABS = 280,
     COS = 281,
     SIN = 282,
     LOG = 283,
     TAN = 284,
     SQRT = 285,
     FOR = 286,
     WHILE = 287,
     IF = 288,
     SELECT = 289,
     ELSE = 290,
     PAR_ABIERTO = 291,
     PAR_CERRADO = 292,
     COMA = 293,
     DOS_PUNTOS = 294,
     CORCHETE_ABIERTO = 295,
     CORCHETE_CERRADO = 296,
     IGUAL = 297,
     IGUAL_IGUAL = 298,
     MENOR_QUE = 299,
     MAYOR_QUE = 300,
     DIFERENTE = 301,
     POR = 302,
     MAS = 303,
     MENOS = 304,
     DIVISION = 305,
     EXPONENCIAL = 306,
     PUNTO = 307,
     ID = 308,
     CTE_INTEGER = 309,
     CTE_DECIMAL = 310,
     CTE_BOOLEAN = 311,
     CTE_STRING = 312
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
#define STRING 269
#define INTEGER 270
#define DECIMAL 271
#define BOOLEAN 272
#define END 273
#define FALSO 274
#define VERDADERO 275
#define VOID 276
#define RETURN 277
#define AND 278
#define OR 279
#define ABS 280
#define COS 281
#define SIN 282
#define LOG 283
#define TAN 284
#define SQRT 285
#define FOR 286
#define WHILE 287
#define IF 288
#define SELECT 289
#define ELSE 290
#define PAR_ABIERTO 291
#define PAR_CERRADO 292
#define COMA 293
#define DOS_PUNTOS 294
#define CORCHETE_ABIERTO 295
#define CORCHETE_CERRADO 296
#define IGUAL 297
#define IGUAL_IGUAL 298
#define MENOR_QUE 299
#define MAYOR_QUE 300
#define DIFERENTE 301
#define POR 302
#define MAS 303
#define MENOS 304
#define DIVISION 305
#define EXPONENCIAL 306
#define PUNTO 307
#define ID 308
#define CTE_INTEGER 309
#define CTE_DECIMAL 310
#define CTE_BOOLEAN 311
#define CTE_STRING 312




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

