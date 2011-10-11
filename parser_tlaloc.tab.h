
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
     APUNTADOR = 308,
     COMILLAS = 309,
     ID = 310,
     CTE_INTEGER = 311,
     CTE_DECIMAL = 312,
     CTE_STRING = 313
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


