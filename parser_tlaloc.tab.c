/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "parser_tlaloc.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	extern int yylineno;    // Guarda la linea que se lee, por si existe error de sitaxis 
	char *type;             // Tipo de procedimiento que se guardara en la tabla de procs
    char *var_type = "";    // Tipo de dato de la variable que se guardara en tabla de vars
	char *name;             // Nombre de variable que se guardara en tabla de vars
	char *proc;             // Procedimiento ejecutandose actualmente en memoria
    int first_dim;          // Primera dimension de un arreglo bidimensional. Usado para obtener dimension entera.
    int equals_var;         // Guarda la direccion de la variable a la cual se le asignara una expresion

    // Dimensiones para cada tipo de variable, si es que se declaran arreglos
    int integer_dimension = 0, string_dimension = 0, boolean_dimension = 0, decimal_dimension = 0;
	
	void yyerror(const char *message)
	{
	  fprintf(stderr, "error: '%s' - LINE '%d'\n", message, yylineno);
	}

    // Inicializa variables para uso en otros metodos después de terminar el bloque global
    void reset_block_vars(){
        var_type = ""; name = ""; 
        integer_dimension = 0; string_dimension = 0; 
        boolean_dimension = 0; decimal_dimension = 0; 
    }
	
    // Llama al metodo con la dimension que le corresponde a esta nueva nueva variable a agregar
    void set_dimension(){
        if (strcmp(var_type, "integer") == 0) {
                insert_vars_to_proc_table(name, var_type, integer_dimension);
                integer_dimension = 0;
        } else if (strcmp(var_type, "string") == 0) {
                insert_vars_to_proc_table(name, var_type, string_dimension);
                string_dimension = 0;
        } else if (strcmp(var_type, "boolean") == 0) {
                insert_vars_to_proc_table(name, var_type, boolean_dimension);
                boolean_dimension = 0;
        } else if (strcmp(var_type, "decimal") == 0) {
                insert_vars_to_proc_table(name, var_type, decimal_dimension);
                decimal_dimension = 0;
        } else { 
                insert_vars_to_proc_table(name, var_type, 0); 
        }
    }

    // Guarda dimension - 1 para manipular indexaciones de 0 a N-1
    void get_constant(int constant){
        if (strcmp(var_type, "integer") == 0) integer_dimension = constant - 1;
        if (strcmp(var_type, "string") == 0) string_dimension = constant - 1;
        if (strcmp(var_type, "boolean") == 0) boolean_dimension = constant - 1;
        if (strcmp(var_type, "decimal") == 0) decimal_dimension = constant - 1;
    }
    
	main(int argc, char **argv) {
		create_proc_table();
        create_constants_table();
        create_stacks_and_queues();
		create_quadruples_array();
		yyparse();
		print_quadruples_array_to_file();
		print_hash_table();
	}
	
	


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 69 "parser_tlaloc.y"
{
	char *str;
	int integer;
	float decimal;
}
/* Line 193 of yacc.c.  */
#line 292 "parser_tlaloc.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 305 "parser_tlaloc.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   262

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  138
/* YYNRULES -- Number of states.  */
#define YYNSTATES  265

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     5,    16,    19,    20,    21,    22,
      31,    34,    36,    39,    41,    42,    46,    48,    50,    52,
      54,    56,    59,    61,    62,    63,    68,    69,    70,    78,
      80,    84,    85,    91,    93,    95,    97,    99,   101,   103,
     105,   107,   109,   111,   113,   115,   117,   119,   121,   122,
     127,   128,   133,   135,   136,   141,   142,   147,   149,   150,
     155,   157,   158,   163,   166,   169,   172,   175,   177,   179,
     181,   186,   188,   190,   192,   194,   196,   198,   201,   202,
     203,   204,   217,   218,   219,   220,   237,   240,   241,   243,
     244,   249,   250,   253,   254,   256,   258,   260,   263,   265,
     270,   271,   272,   279,   281,   289,   299,   301,   303,   305,
     307,   308,   319,   320,   325,   326,   336,   339,   344,   345,
     346,   357,   370,   373,   374,   381,   388,   390,   391,   392,
     401,   404,   405,   408,   412,   413,   415,   419,   421
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      63,     0,    -1,    -1,    -1,     3,    58,    64,    40,    66,
      65,    96,    97,    19,     3,    -1,    66,    67,    -1,    -1,
      -1,    -1,    10,    70,    68,    11,    73,    69,    74,    55,
      -1,    56,    58,    -1,    58,    -1,    56,    58,    -1,    58,
      -1,    -1,    58,    72,    75,    -1,    14,    -1,    17,    -1,
      18,    -1,    15,    -1,    22,    -1,    43,    79,    -1,    75,
      -1,    -1,    -1,    41,    61,    76,    42,    -1,    -1,    -1,
      41,    61,    77,    39,    61,    78,    42,    -1,    84,    -1,
      84,    83,    84,    -1,    -1,    82,    37,    81,    84,    38,
      -1,    26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,
      -1,    31,    -1,    24,    -1,    25,    -1,    46,    -1,    45,
      -1,    47,    -1,    44,    -1,    52,    -1,    53,    -1,    87,
      -1,    -1,    87,    49,    85,    84,    -1,    -1,    87,    50,
      86,    84,    -1,    90,    -1,    -1,    90,    48,    88,    84,
      -1,    -1,    90,    51,    89,    84,    -1,    92,    -1,    -1,
      92,    54,    91,    84,    -1,    95,    -1,    -1,    37,    93,
      79,    38,    -1,    49,    61,    -1,    49,    60,    -1,    50,
      61,    -1,    50,    60,    -1,    94,    -1,   110,    -1,    80,
      -1,    58,    41,    84,    42,    -1,    58,    -1,    61,    -1,
      59,    -1,    60,    -1,    21,    -1,    20,    -1,    96,   100,
      -1,    -1,    -1,    -1,     4,    22,    16,    98,    37,   105,
      38,    40,   104,    99,    19,     4,    -1,    -1,    -1,    -1,
       4,    73,   101,    58,   102,    37,   105,    38,    40,   104,
     103,    23,    79,    55,    19,     4,    -1,   104,   109,    -1,
      -1,   106,    -1,    -1,    73,   107,    71,   108,    -1,    -1,
      39,   106,    -1,    -1,    67,    -1,   111,    -1,   115,    -1,
     110,    55,    -1,   128,    -1,    58,    37,    84,    38,    -1,
      -1,    -1,    58,   112,    43,   113,    79,    55,    -1,   114,
      -1,    58,    41,    84,    42,    43,    79,    55,    -1,    58,
      41,    84,    39,    84,    42,    43,    79,    55,    -1,   116,
      -1,   120,    -1,   122,    -1,   125,    -1,    -1,    34,    37,
      79,    38,    40,   117,   104,   118,    19,    34,    -1,    -1,
      36,    40,   119,   104,    -1,    -1,    32,    58,    43,    84,
      12,    84,   121,    19,    32,    -1,    40,   104,    -1,    13,
      84,    40,   104,    -1,    -1,    -1,    33,    37,   123,    79,
      38,    40,   124,   104,    19,    33,    -1,    35,    58,    40,
       8,     9,    40,   104,    19,     8,   126,    19,    35,    -1,
     127,   126,    -1,    -1,     8,    61,    40,   104,    19,     8,
      -1,   136,    37,   135,   134,    38,    55,    -1,   129,    -1,
      -1,    -1,     7,   130,    37,    58,   131,   132,    38,    55,
      -1,   133,   132,    -1,    -1,    39,    58,    -1,    49,   135,
     134,    -1,    -1,    79,    -1,    57,    59,    57,    -1,     5,
      -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    91,    91,    94,    95,    98,    98,    98,
     104,   105,   108,   109,   110,   110,   113,   114,   115,   116,
     117,   120,   121,   122,   125,   125,   128,   128,   128,   131,
     132,   135,   135,   139,   140,   141,   142,   143,   144,   147,
     148,   149,   150,   151,   152,   153,   154,   157,   158,   158,
     159,   159,   162,   163,   163,   164,   164,   167,   168,   168,
     172,   173,   173,   174,   175,   176,   177,   178,   181,   181,
     181,   183,   184,   185,   186,   187,   188,   191,   192,   195,
     195,   195,   198,   198,   198,   198,   201,   201,   203,   206,
     206,   207,   210,   211,   214,   215,   216,   217,   218,   221,
     225,   225,   225,   226,   229,   230,   233,   234,   235,   236,
     239,   239,   242,   242,   242,   244,   247,   248,   251,   251,
     251,   254,   257,   257,   260,   263,   263,   266,   266,   266,
     269,   269,   272,   275,   275,   278,   278,   281,   281
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "METHOD", "PRINT",
  "PRINTLINE", "READ", "CASE", "DEFAULT", "DEFINE", "AS", "TO", "STEP",
  "INTEGER", "DECIMAL", "MAIN", "STRING", "BOOLEAN", "END", "FALSO",
  "VERDADERO", "VOID", "RETURN", "AND", "OR", "ABS", "COS", "SIN", "LOG",
  "TAN", "SQRT", "FOR", "WHILE", "IF", "SELECT", "ELSE", "PAR_ABIERTO",
  "PAR_CERRADO", "COMA", "DOS_PUNTOS", "CORCHETE_ABIERTO",
  "CORCHETE_CERRADO", "IGUAL", "IGUAL_IGUAL", "MENOR_QUE", "MAYOR_QUE",
  "DIFERENTE", "POR", "MAS", "MENOS", "DIVISION", "MAYOR_IGUAL",
  "MENOR_IGUAL", "EXPONENCIAL", "PUNTO", "APUNTADOR", "COMILLAS", "ID",
  "CTE_STRING", "CTE_DECIMAL", "CTE_INTEGER", "$accept", "tlaloc", "@1",
  "@2", "vars", "vars_def", "@3", "@4", "declaracion", "params", "@5",
  "tipo", "asignacion_var", "dimension_arreglo", "@6", "@7", "@8",
  "expresion", "funcion_matematica", "@9", "math_choices",
  "operador_logico", "exp", "@10", "@11", "termino", "@12", "@13",
  "exponencial", "@14", "factor", "@15", "factor_alterno", "var", "metodo",
  "metodo_main", "@16", "@17", "metodo_def", "@18", "@19", "@20",
  "metodo_body", "parametros", "parametros_def", "@21", "parametros_extra",
  "body_code", "llamado", "asignacion", "@22", "@23", "array_assignment",
  "estatuto", "if_statement", "@24", "else_statement", "@25",
  "for_statement", "for_step", "while_statement", "@26", "@27",
  "select_statement", "case_statement", "case_statement_def",
  "default_functions", "read", "@28", "@29", "ids", "ids_def",
  "default_function_input", "default_function_input_def",
  "default_choices", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    64,    65,    63,    66,    66,    68,    69,    67,
      70,    70,    71,    71,    72,    71,    73,    73,    73,    73,
      73,    74,    74,    74,    76,    75,    77,    78,    75,    79,
      79,    81,    80,    82,    82,    82,    82,    82,    82,    83,
      83,    83,    83,    83,    83,    83,    83,    84,    85,    84,
      86,    84,    87,    88,    87,    89,    87,    90,    91,    90,
      92,    93,    92,    92,    92,    92,    92,    92,    94,    94,
      94,    95,    95,    95,    95,    95,    95,    96,    96,    98,
      99,    97,   101,   102,   103,   100,   104,   104,   105,   107,
     106,   106,   108,   108,   109,   109,   109,   109,   109,   110,
     112,   113,   111,   111,   114,   114,   115,   115,   115,   115,
     117,   116,   119,   118,   118,   120,   121,   121,   123,   124,
     122,   125,   126,   126,   127,   128,   128,   130,   131,   129,
     132,   132,   133,   134,   134,   135,   135,   136,   136
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,    10,     2,     0,     0,     0,     8,
       2,     1,     2,     1,     0,     3,     1,     1,     1,     1,
       1,     2,     1,     0,     0,     4,     0,     0,     7,     1,
       3,     0,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     1,     0,     4,     0,     4,     1,     0,     4,
       1,     0,     4,     2,     2,     2,     2,     1,     1,     1,
       4,     1,     1,     1,     1,     1,     1,     2,     0,     0,
       0,    12,     0,     0,     0,    16,     2,     0,     1,     0,
       4,     0,     2,     0,     1,     1,     1,     2,     1,     4,
       0,     0,     6,     1,     7,     9,     1,     1,     1,     1,
       0,    10,     0,     4,     0,     9,     2,     4,     0,     0,
      10,    12,     2,     0,     6,     6,     1,     0,     0,     8,
       2,     0,     2,     3,     0,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,     3,     0,    78,
       5,     0,    11,     7,     0,    10,     0,     0,     0,    77,
       0,    16,    19,    17,    18,    20,    82,     0,    20,     8,
      79,     0,     4,    23,     0,    83,     0,     0,     0,    22,
      91,     0,    24,    76,    75,    33,    34,    35,    36,    37,
      38,    61,     0,     0,    71,    73,    74,    72,    21,    69,
       0,    29,    47,    52,    57,    67,    60,    68,     9,    89,
       0,    88,    91,     0,     0,     0,    64,    63,    66,    65,
       0,     0,    31,    39,    40,    44,    42,    41,    43,    45,
      46,     0,    48,    50,    53,    55,    58,     0,     0,     0,
      25,     0,     0,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     0,    13,    93,    87,     0,    27,    62,    99,
      70,     0,    49,    51,    54,    56,    59,    12,     0,    91,
      90,    80,    87,     0,    32,    15,    92,   137,   138,   127,
       0,     0,     0,     0,   100,    94,     0,    86,     0,    95,
     103,    96,   106,   107,   108,   109,    98,   126,     0,    84,
      28,     0,     0,   118,     0,     0,     0,     0,     0,    97,
       0,     0,     0,     0,     0,     0,     0,     0,   101,    81,
       0,   135,   134,     0,   128,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,   110,
       0,     0,     0,     0,   136,   134,     0,     0,     0,     0,
     131,     0,   119,    87,    87,     0,     0,   102,   133,   125,
       0,   132,     0,   130,     0,    87,     0,    87,   114,     0,
       0,   104,    85,   129,     0,   116,     0,     0,     0,     0,
       0,     0,    87,   115,     0,   112,     0,   123,   105,   117,
     120,    87,   111,     0,     0,   123,   113,     0,     0,   122,
      87,   121,     0,     0,   124
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,     9,     7,   145,    16,    33,    13,   114,
     128,    69,    38,    39,    73,    74,   133,   181,    59,   105,
      60,    91,    61,   107,   108,    62,   109,   110,    63,   111,
      64,    75,    65,    66,    14,    18,    34,   146,    19,    31,
      41,   171,   131,    70,    71,    97,   130,   147,    67,   149,
     167,   191,   150,   151,   152,   213,   239,   251,   153,   226,
     154,   174,   227,   155,   254,   255,   156,   157,   161,   196,
     209,   210,   194,   182,   158
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -130
static const yytype_int16 yypact[] =
{
       1,   -49,    23,  -130,  -130,   -23,  -130,    27,    -1,  -130,
    -130,    10,  -130,  -130,    50,  -130,    63,   102,    56,  -130,
     204,  -130,  -130,  -130,  -130,    61,  -130,    79,  -130,  -130,
    -130,    25,  -130,    17,    49,  -130,    32,   146,    33,  -130,
     204,    58,    60,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,     9,    11,   -31,  -130,  -130,  -130,  -130,  -130,
      64,   164,    -4,   -32,    43,  -130,  -130,  -130,  -130,  -130,
      62,  -130,   204,    65,    66,   146,  -130,  -130,  -130,  -130,
     146,   146,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,   146,  -130,  -130,  -130,  -130,  -130,     3,    68,    74,
    -130,    45,    76,    83,    84,   146,  -130,   146,   146,   146,
     146,   146,    67,    87,    90,  -130,    92,  -130,  -130,  -130,
    -130,   101,  -130,  -130,  -130,  -130,  -130,  -130,    99,   204,
    -130,   128,  -130,   111,  -130,  -130,  -130,  -130,  -130,  -130,
      85,   107,   118,    98,   -30,  -130,   138,  -130,   104,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,   127,   128,
    -130,   131,   126,  -130,   146,   144,   146,   142,   183,  -130,
     121,   167,   133,   146,   146,   154,   186,   -15,  -130,  -130,
     139,  -130,   148,   146,  -130,   187,   162,   161,   193,   146,
     160,   146,   155,   121,   175,   159,   176,   146,   180,  -130,
     184,   181,   146,   170,  -130,   148,   172,   209,   171,   192,
     176,    -5,  -130,  -130,  -130,   188,   177,  -130,  -130,  -130,
     229,  -130,   179,  -130,   146,  -130,   216,  -130,     8,    15,
     146,  -130,  -130,  -130,   196,   128,   205,    46,   198,   220,
     232,   189,  -130,  -130,   208,  -130,   211,   234,  -130,   128,
    -130,  -130,  -130,   182,   227,   234,   128,   207,   213,  -130,
    -130,  -130,    57,   241,  -130
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,  -130,  -130,   243,  -130,  -130,  -130,  -130,
    -130,    19,  -130,   123,  -130,  -130,  -130,   -37,  -130,  -130,
    -130,  -130,   -79,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -129,   185,   124,  -130,  -130,  -130,  -126,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,    -3,  -130,  -130,  -130,  -130,  -130,
      44,  -130,    51,    69,  -130
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -27
static const yytype_int16 yytable[] =
{
      58,   103,   104,   159,     1,   148,    80,    80,   224,     3,
      81,   166,   106,   137,   138,   139,    94,     6,     8,    95,
     137,   138,   139,     4,   189,     8,   121,   190,   122,   123,
     124,   125,   126,   148,   240,   225,    26,     8,   102,    29,
     140,   141,   142,   143,   238,    92,    93,   140,   141,   142,
     143,   137,   138,   139,    17,    11,     8,    12,    36,   112,
      37,   113,   137,   138,   139,   244,   144,     8,    15,    76,
      77,    78,    79,   144,    20,    27,   263,    30,   140,   141,
     142,   143,    32,    35,   228,   229,    40,   177,    68,   140,
     141,   142,   143,    42,   185,    72,   235,    96,   237,   -26,
      98,    82,   148,   148,   144,   101,   117,   100,   115,   148,
     201,   148,   116,   249,   118,   144,    21,    22,   211,    23,
      24,   119,   256,   148,    25,   127,   120,   175,   -14,   129,
     148,   262,   132,   137,   138,   139,   148,   186,     8,   134,
      36,    43,    44,   162,   163,   234,   195,    45,    46,    47,
      48,    49,    50,   160,   203,   164,   165,   168,    51,   169,
     140,   141,   142,   143,   170,   216,    43,    44,   172,   173,
      52,    53,    45,    46,    47,    48,    49,    50,   180,    54,
      55,    56,    57,    51,   176,   178,   144,   179,    83,    84,
     183,   184,   187,   241,   188,    52,    53,   193,   192,   197,
     198,   199,   200,   202,    54,    55,    56,    57,    85,    86,
      87,    88,   204,   206,   207,   208,    89,    90,    21,    22,
     212,    23,    24,   215,   214,   217,    28,   219,   220,   221,
     222,   230,   231,   232,   233,   236,   242,   243,   245,   246,
     247,   250,   253,   257,   248,   252,   258,   260,   261,   264,
      10,   135,   259,   136,   223,     0,   218,    99,     0,     0,
       0,     0,   205
};

static const yytype_int16 yycheck[] =
{
      37,    80,    81,   132,     3,   131,    37,    37,    13,    58,
      41,    41,    91,     5,     6,     7,    48,    40,    10,    51,
       5,     6,     7,     0,    39,    10,   105,    42,   107,   108,
     109,   110,   111,   159,    19,    40,    17,    10,    75,    20,
      32,    33,    34,    35,    36,    49,    50,    32,    33,    34,
      35,     5,     6,     7,     4,    56,    10,    58,    41,    56,
      43,    58,     5,     6,     7,    19,    58,    10,    58,    60,
      61,    60,    61,    58,    11,    19,    19,    16,    32,    33,
      34,    35,     3,    58,   213,   214,    37,   166,    55,    32,
      33,    34,    35,    61,   173,    37,   225,    54,   227,    39,
      38,    37,   228,   229,    58,    39,    61,    42,    40,   235,
     189,   237,    38,   242,    38,    58,    14,    15,   197,    17,
      18,    38,   251,   249,    22,    58,    42,   164,    41,    39,
     256,   260,    40,     5,     6,     7,   262,   174,    10,    38,
      41,    20,    21,    58,    37,   224,   183,    26,    27,    28,
      29,    30,    31,    42,   191,    37,    58,    19,    37,    55,
      32,    33,    34,    35,    37,   202,    20,    21,    37,    43,
      49,    50,    26,    27,    28,    29,    30,    31,    57,    58,
      59,    60,    61,    37,    40,    43,    58,     4,    24,    25,
      23,    58,    38,   230,     8,    49,    50,    49,    59,    12,
      38,    40,     9,    43,    58,    59,    60,    61,    44,    45,
      46,    47,    57,    38,    55,    39,    52,    53,    14,    15,
      40,    17,    18,    42,    40,    55,    22,    55,    19,    58,
      38,    43,    55,     4,    55,    19,    40,    32,    40,    19,
       8,    33,     8,    61,    55,    34,    19,    40,    35,     8,
       7,   128,   255,   129,   210,    -1,   205,    72,    -1,    -1,
      -1,    -1,   193
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    63,    58,     0,    64,    40,    66,    10,    65,
      67,    56,    58,    70,    96,    58,    68,     4,    97,   100,
      11,    14,    15,    17,    18,    22,    73,    19,    22,    73,
      16,   101,     3,    69,    98,    58,    41,    43,    74,    75,
      37,   102,    61,    20,    21,    26,    27,    28,    29,    30,
      31,    37,    49,    50,    58,    59,    60,    61,    79,    80,
      82,    84,    87,    90,    92,    94,    95,   110,    55,    73,
     105,   106,    37,    76,    77,    93,    60,    61,    60,    61,
      37,    41,    37,    24,    25,    44,    45,    46,    47,    52,
      53,    83,    49,    50,    48,    51,    54,   107,    38,   105,
      42,    39,    79,    84,    84,    81,    84,    85,    86,    88,
      89,    91,    56,    58,    71,    40,    38,    61,    38,    38,
      42,    84,    84,    84,    84,    84,    84,    58,    72,    39,
     108,   104,    40,    78,    38,    75,   106,     5,     6,     7,
      32,    33,    34,    35,    58,    67,    99,   109,   110,   111,
     114,   115,   116,   120,   122,   125,   128,   129,   136,   104,
      42,   130,    58,    37,    37,    58,    41,   112,    19,    55,
      37,   103,    37,    43,   123,    79,    40,    84,    43,     4,
      57,    79,   135,    23,    58,    84,    79,    38,     8,    39,
      42,   113,    59,    49,   134,    79,   131,    12,    38,    40,
       9,    84,    43,    79,    57,   135,    38,    55,    39,   132,
     133,    84,    40,   117,    40,    42,    79,    55,   134,    55,
      19,    58,    38,   132,    13,    40,   121,   124,   104,   104,
      43,    55,     4,    55,    84,   104,    19,   104,    36,   118,
      19,    79,    40,    32,    19,    40,    19,     8,    55,   104,
      33,   119,    34,     8,   126,   127,   104,    61,    19,   126,
      40,    35,   104,    19,     8
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 91 "parser_tlaloc.y"
    {insert_proc_to_table(yylval.str, "global"); proc = yylval.str;}
    break;

  case 3:
#line 91 "parser_tlaloc.y"
    {print_var_table(proc); reset_block_vars(); ;}
    break;

  case 7:
#line 98 "parser_tlaloc.y"
    {name = yylval.str;;}
    break;

  case 8:
#line 98 "parser_tlaloc.y"
    { 
                var_type = yylval.str; 
                set_dimension();
            ;}
    break;

  case 12:
#line 108 "parser_tlaloc.y"
    {insert_vars_to_proc_table(yylval.str, var_type, 0);;}
    break;

  case 13:
#line 109 "parser_tlaloc.y"
    {insert_vars_to_proc_table(yylval.str, var_type, 0);;}
    break;

  case 14:
#line 110 "parser_tlaloc.y"
    {name = yylval.str; set_dimension();;}
    break;

  case 24:
#line 125 "parser_tlaloc.y"
    {
                       get_constant(yylval.integer);
                    ;}
    break;

  case 26:
#line 128 "parser_tlaloc.y"
    { first_dim = yylval.integer; ;}
    break;

  case 27:
#line 128 "parser_tlaloc.y"
    { get_constant(yylval.integer * first_dim); ;}
    break;

  case 29:
#line 131 "parser_tlaloc.y"
    { generate_relational_quadruple(); ;}
    break;

  case 30:
#line 132 "parser_tlaloc.y"
    { generate_relational_quadruple(); ;}
    break;

  case 31:
#line 135 "parser_tlaloc.y"
    { insert_to_StackOper('['); ;}
    break;

  case 32:
#line 136 "parser_tlaloc.y"
    { remove_from_StackOper(); generate_exp_quadruples(); ;}
    break;

  case 33:
#line 139 "parser_tlaloc.y"
    { insert_to_StackOper(212); ;}
    break;

  case 34:
#line 140 "parser_tlaloc.y"
    { insert_to_StackOper(214); ;}
    break;

  case 35:
#line 141 "parser_tlaloc.y"
    { insert_to_StackOper(225); ;}
    break;

  case 36:
#line 142 "parser_tlaloc.y"
    { insert_to_StackOper(211); ;}
    break;

  case 37:
#line 143 "parser_tlaloc.y"
    { insert_to_StackOper(225); ;}
    break;

  case 38:
#line 144 "parser_tlaloc.y"
    { insert_to_StackOper(231); ;}
    break;

  case 39:
#line 147 "parser_tlaloc.y"
    { insert_to_StackOper('a'); ;}
    break;

  case 40:
#line 148 "parser_tlaloc.y"
    { insert_to_StackOper('o'); ;}
    break;

  case 41:
#line 149 "parser_tlaloc.y"
    { insert_to_StackOper('>'); ;}
    break;

  case 42:
#line 150 "parser_tlaloc.y"
    { insert_to_StackOper('<'); ;}
    break;

  case 43:
#line 151 "parser_tlaloc.y"
    { insert_to_StackOper('!'); ;}
    break;

  case 44:
#line 152 "parser_tlaloc.y"
    { insert_to_StackOper('i'); ;}
    break;

  case 45:
#line 153 "parser_tlaloc.y"
    { insert_to_StackOper(124); ;}
    break;

  case 46:
#line 154 "parser_tlaloc.y"
    { insert_to_StackOper(125); ;}
    break;

  case 47:
#line 157 "parser_tlaloc.y"
    { generate_add_sust_quadruple(); ;}
    break;

  case 48:
#line 158 "parser_tlaloc.y"
    { insert_to_StackOper('+'); ;}
    break;

  case 49:
#line 158 "parser_tlaloc.y"
    { generate_add_sust_quadruple(); ;}
    break;

  case 50:
#line 159 "parser_tlaloc.y"
    { insert_to_StackOper('-'); ;}
    break;

  case 51:
#line 159 "parser_tlaloc.y"
    { generate_add_sust_quadruple(); ;}
    break;

  case 52:
#line 162 "parser_tlaloc.y"
    { generate_mult_div_quadruple(); ;}
    break;

  case 53:
#line 163 "parser_tlaloc.y"
    { insert_to_StackOper('*'); ;}
    break;

  case 54:
#line 163 "parser_tlaloc.y"
    { generate_mult_div_quadruple(); ;}
    break;

  case 55:
#line 164 "parser_tlaloc.y"
    { insert_to_StackOper('/'); ;}
    break;

  case 56:
#line 164 "parser_tlaloc.y"
    { generate_mult_div_quadruple(); ;}
    break;

  case 57:
#line 167 "parser_tlaloc.y"
    { generate_exponential_quadruple(); ;}
    break;

  case 58:
#line 168 "parser_tlaloc.y"
    { insert_to_StackOper('^'); ;}
    break;

  case 59:
#line 168 "parser_tlaloc.y"
    { generate_exponential_quadruple(); ;}
    break;

  case 61:
#line 173 "parser_tlaloc.y"
    { insert_to_StackOper('['); ;}
    break;

  case 62:
#line 173 "parser_tlaloc.y"
    { remove_from_StackOper(); ;}
    break;

  case 63:
#line 174 "parser_tlaloc.y"
    { insert_cte_int_to_StackO(yylval.integer); ;}
    break;

  case 64:
#line 175 "parser_tlaloc.y"
    { insert_cte_decimal_to_StackO(yylval.integer); ;}
    break;

  case 65:
#line 176 "parser_tlaloc.y"
    { insert_cte_int_to_StackO(yylval.integer * -1); ;}
    break;

  case 66:
#line 177 "parser_tlaloc.y"
    { insert_cte_decimal_to_StackO(yylval.integer * -1); ;}
    break;

  case 71:
#line 183 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); ;}
    break;

  case 72:
#line 184 "parser_tlaloc.y"
    { insert_cte_int_to_StackO(yylval.integer); ;}
    break;

  case 73:
#line 185 "parser_tlaloc.y"
    { insert_cte_string_to_StackO(yylval.str); ;}
    break;

  case 74:
#line 186 "parser_tlaloc.y"
    { insert_cte_decimal_to_StackO(yylval.decimal); ;}
    break;

  case 79:
#line 195 "parser_tlaloc.y"
    {insert_proc_to_table(yylval.str, "void"); proc = yylval.str;}
    break;

  case 80:
#line 195 "parser_tlaloc.y"
    {print_var_table(proc);;}
    break;

  case 82:
#line 198 "parser_tlaloc.y"
    {type = yylval.str;;}
    break;

  case 83:
#line 198 "parser_tlaloc.y"
    {insert_proc_to_table(yylval.str, type); proc = yylval.str;}
    break;

  case 84:
#line 198 "parser_tlaloc.y"
    {print_var_table(proc);;}
    break;

  case 89:
#line 206 "parser_tlaloc.y"
    {var_type = yylval.str;;}
    break;

  case 100:
#line 225 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); ;}
    break;

  case 101:
#line 225 "parser_tlaloc.y"
    { insert_to_StackOper('='); ;}
    break;

  case 102:
#line 225 "parser_tlaloc.y"
    { generate_exp_quadruples(); reset_temp_vars(); ;}
    break;

  case 110:
#line 239 "parser_tlaloc.y"
    {generate_gotoF_if_quadruple();;}
    break;

  case 111:
#line 239 "parser_tlaloc.y"
    {fill_if();;}
    break;

  case 112:
#line 242 "parser_tlaloc.y"
    {generate_goto_if_quadruple();;}
    break;

  case 118:
#line 251 "parser_tlaloc.y"
    {push_cont_to_stack_jumps();;}
    break;

  case 119:
#line 251 "parser_tlaloc.y"
    {generate_while_gotoF_quadruple();;}
    break;

  case 120:
#line 251 "parser_tlaloc.y"
    {fill_while();;}
    break;

  case 125:
#line 263 "parser_tlaloc.y"
    { remove_from_StackOper(); ;}
    break;

  case 127:
#line 266 "parser_tlaloc.y"
    { insert_to_StackOper(215); ;}
    break;

  case 128:
#line 266 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); generate_exp_quadruples(); ;}
    break;

  case 129:
#line 266 "parser_tlaloc.y"
    { remove_from_StackOper(); ;}
    break;

  case 132:
#line 272 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); generate_exp_quadruples(); ;}
    break;

  case 135:
#line 278 "parser_tlaloc.y"
    { generate_exp_quadruples(); ;}
    break;

  case 137:
#line 281 "parser_tlaloc.y"
    { insert_to_StackOper(213); ;}
    break;

  case 138:
#line 281 "parser_tlaloc.y"
    { insert_to_StackOper(228); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2131 "parser_tlaloc.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 283 "parser_tlaloc.y"


