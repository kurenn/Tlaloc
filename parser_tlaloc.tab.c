
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
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
		//print_hash_table();
	}
	
	


/* Line 189 of yacc.c  */
#line 142 "parser_tlaloc.tab.c"

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
     EXPONENCIAL = 307,
     PUNTO = 308,
     APUNTADOR = 309,
     COMILLAS = 310,
     ID = 311,
     CTE_STRING = 312,
     CTE_DECIMAL = 313,
     CTE_INTEGER = 314
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 69 "parser_tlaloc.y"

	char *str;
	int integer;
	float decimal;



/* Line 214 of yacc.c  */
#line 245 "parser_tlaloc.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 257 "parser_tlaloc.tab.c"

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
# if YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNRULES -- Number of states.  */
#define YYNSTATES  258

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

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
      55,    56,    57,    58,    59
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
     105,   107,   109,   111,   113,   115,   117,   118,   123,   124,
     129,   131,   132,   137,   138,   143,   145,   146,   151,   153,
     154,   159,   162,   165,   168,   171,   173,   175,   177,   182,
     184,   186,   188,   190,   192,   194,   197,   198,   199,   200,
     213,   214,   215,   216,   233,   236,   237,   239,   240,   245,
     246,   249,   250,   252,   254,   256,   259,   261,   266,   267,
     268,   275,   277,   285,   295,   297,   299,   301,   303,   315,
     325,   328,   333,   342,   355,   358,   359,   366,   373,   375,
     376,   377,   386,   389,   390,   393,   397,   398,   400,   404,
     406
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      61,     0,    -1,    -1,    -1,     3,    56,    62,    40,    64,
      63,    94,    95,    19,     3,    -1,    64,    65,    -1,    -1,
      -1,    -1,    10,    68,    66,    11,    71,    67,    72,    53,
      -1,    54,    56,    -1,    56,    -1,    54,    56,    -1,    56,
      -1,    -1,    56,    70,    73,    -1,    14,    -1,    17,    -1,
      18,    -1,    15,    -1,    22,    -1,    43,    77,    -1,    73,
      -1,    -1,    -1,    41,    59,    74,    42,    -1,    -1,    -1,
      41,    59,    75,    39,    59,    76,    42,    -1,    82,    -1,
      82,    81,    82,    -1,    -1,    80,    37,    79,    82,    38,
      -1,    26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,
      -1,    31,    -1,    24,    -1,    25,    -1,    46,    -1,    45,
      -1,    47,    -1,    44,    -1,    85,    -1,    -1,    85,    49,
      83,    82,    -1,    -1,    85,    50,    84,    82,    -1,    88,
      -1,    -1,    88,    48,    86,    82,    -1,    -1,    88,    51,
      87,    82,    -1,    90,    -1,    -1,    90,    52,    89,    82,
      -1,    93,    -1,    -1,    37,    91,    77,    38,    -1,    49,
      59,    -1,    49,    58,    -1,    50,    59,    -1,    50,    58,
      -1,    92,    -1,   108,    -1,    78,    -1,    56,    41,    82,
      42,    -1,    56,    -1,    59,    -1,    57,    -1,    58,    -1,
      21,    -1,    20,    -1,    94,    98,    -1,    -1,    -1,    -1,
       4,    22,    16,    96,    37,   103,    38,    40,   102,    97,
      19,     4,    -1,    -1,    -1,    -1,     4,    71,    99,    56,
     100,    37,   103,    38,    40,   102,   101,    23,    77,    53,
      19,     4,    -1,   102,   107,    -1,    -1,   104,    -1,    -1,
      71,   105,    69,   106,    -1,    -1,    39,   104,    -1,    -1,
      65,    -1,   109,    -1,   113,    -1,   108,    53,    -1,   121,
      -1,    56,    37,    82,    38,    -1,    -1,    -1,    56,   110,
      43,   111,    77,    53,    -1,   112,    -1,    56,    41,    82,
      42,    43,    77,    53,    -1,    56,    41,    82,    39,    82,
      42,    43,    77,    53,    -1,   114,    -1,   115,    -1,   117,
      -1,   118,    -1,    34,    37,    77,    38,    40,   102,    36,
      40,   102,    19,    34,    -1,    32,    56,    43,    82,    12,
      82,   116,    19,    32,    -1,    40,   102,    -1,    13,    82,
      40,   102,    -1,    33,    37,    77,    38,    40,   102,    19,
      33,    -1,    35,    56,    40,     8,     9,    40,   102,    19,
       8,   119,    19,    35,    -1,   120,   119,    -1,    -1,     8,
      59,    40,   102,    19,     8,    -1,   129,    37,   128,   127,
      38,    53,    -1,   122,    -1,    -1,    -1,     7,   123,    37,
      56,   124,   125,    38,    53,    -1,   126,   125,    -1,    -1,
      39,    56,    -1,    49,   128,   127,    -1,    -1,    77,    -1,
      55,    57,    55,    -1,     5,    -1,     6,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    91,    91,    94,    95,    98,    98,    98,
     104,   105,   108,   109,   110,   110,   113,   114,   115,   116,
     117,   120,   121,   122,   125,   125,   128,   128,   128,   131,
     132,   135,   135,   139,   140,   141,   142,   143,   144,   147,
     148,   149,   150,   151,   152,   155,   156,   156,   157,   157,
     160,   161,   161,   162,   162,   165,   166,   166,   170,   171,
     171,   172,   173,   174,   175,   176,   179,   179,   179,   181,
     182,   183,   184,   185,   186,   189,   190,   193,   193,   193,
     196,   196,   196,   196,   199,   199,   201,   204,   204,   205,
     208,   209,   212,   213,   214,   215,   216,   219,   223,   223,
     223,   224,   227,   228,   231,   232,   233,   234,   237,   241,
     244,   245,   248,   251,   254,   254,   257,   260,   260,   263,
     263,   263,   266,   266,   269,   272,   272,   275,   275,   278,
     278
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
  "DIFERENTE", "POR", "MAS", "MENOS", "DIVISION", "EXPONENCIAL", "PUNTO",
  "APUNTADOR", "COMILLAS", "ID", "CTE_STRING", "CTE_DECIMAL",
  "CTE_INTEGER", "$accept", "tlaloc", "$@1", "$@2", "vars", "vars_def",
  "$@3", "$@4", "declaracion", "params", "$@5", "tipo", "asignacion_var",
  "dimension_arreglo", "$@6", "$@7", "$@8", "expresion",
  "funcion_matematica", "$@9", "math_choices", "operador_logico", "exp",
  "$@10", "$@11", "termino", "$@12", "$@13", "exponencial", "$@14",
  "factor", "$@15", "factor_alterno", "var", "metodo", "metodo_main",
  "$@16", "$@17", "metodo_def", "$@18", "$@19", "$@20", "metodo_body",
  "parametros", "parametros_def", "$@21", "parametros_extra", "body_code",
  "llamado", "asignacion", "$@22", "$@23", "array_assignment", "estatuto",
  "if_statement", "for_statement", "for_step", "while_statement",
  "select_statement", "case_statement", "case_statement_def",
  "default_functions", "read", "$@24", "$@25", "ids", "ids_def",
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    62,    63,    61,    64,    64,    66,    67,    65,
      68,    68,    69,    69,    70,    69,    71,    71,    71,    71,
      71,    72,    72,    72,    74,    73,    75,    76,    73,    77,
      77,    79,    78,    80,    80,    80,    80,    80,    80,    81,
      81,    81,    81,    81,    81,    82,    83,    82,    84,    82,
      85,    86,    85,    87,    85,    88,    89,    88,    90,    91,
      90,    90,    90,    90,    90,    90,    92,    92,    92,    93,
      93,    93,    93,    93,    93,    94,    94,    96,    97,    95,
      99,   100,   101,    98,   102,   102,   103,   105,   104,   104,
     106,   106,   107,   107,   107,   107,   107,   108,   110,   111,
     109,   109,   112,   112,   113,   113,   113,   113,   114,   115,
     116,   116,   117,   118,   119,   119,   120,   121,   121,   123,
     124,   122,   125,   125,   126,   127,   127,   128,   128,   129,
     129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,    10,     2,     0,     0,     0,     8,
       2,     1,     2,     1,     0,     3,     1,     1,     1,     1,
       1,     2,     1,     0,     0,     4,     0,     0,     7,     1,
       3,     0,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       1,     0,     4,     0,     4,     1,     0,     4,     1,     0,
       4,     2,     2,     2,     2,     1,     1,     1,     4,     1,
       1,     1,     1,     1,     1,     2,     0,     0,     0,    12,
       0,     0,     0,    16,     2,     0,     1,     0,     4,     0,
       2,     0,     1,     1,     1,     2,     1,     4,     0,     0,
       6,     1,     7,     9,     1,     1,     1,     1,    11,     9,
       2,     4,     8,    12,     2,     0,     6,     6,     1,     0,
       0,     8,     2,     0,     2,     3,     0,     1,     3,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,     3,     0,    76,
       5,     0,    11,     7,     0,    10,     0,     0,     0,    75,
       0,    16,    19,    17,    18,    20,    80,     0,    20,     8,
      77,     0,     4,    23,     0,    81,     0,     0,     0,    22,
      89,     0,    24,    74,    73,    33,    34,    35,    36,    37,
      38,    59,     0,     0,    69,    71,    72,    70,    21,    67,
       0,    29,    45,    50,    55,    65,    58,    66,     9,    87,
       0,    86,    89,     0,     0,     0,    62,    61,    64,    63,
       0,     0,    31,    39,    40,    44,    42,    41,    43,     0,
      46,    48,    51,    53,    56,     0,     0,     0,    25,     0,
       0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,    13,    91,    85,     0,    27,    60,    97,    68,     0,
      47,    49,    52,    54,    57,    12,     0,    89,    88,    78,
      85,     0,    32,    15,    90,   129,   130,   119,     0,     0,
       0,     0,    98,    92,     0,    84,     0,    93,   101,    94,
     104,   105,   106,   107,    96,   118,     0,    82,    28,     0,
       0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
       0,     0,     0,     0,     0,     0,    99,    79,     0,   127,
     126,     0,   120,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,     0,    85,    85,     0,     0,
       0,     0,   128,   126,     0,     0,     0,     0,   123,     0,
       0,     0,    85,     0,     0,   100,   125,   117,     0,   124,
       0,   122,     0,    85,     0,     0,     0,     0,     0,   102,
      83,   121,     0,   110,     0,   112,    85,     0,     0,    85,
     109,     0,   115,   103,   111,     0,     0,     0,   115,   108,
       0,     0,   114,    85,   113,     0,     0,   116
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,     9,     7,   143,    16,    33,    13,   112,
     126,    69,    38,    39,    73,    74,   131,   179,    59,   103,
      60,    89,    61,   105,   106,    62,   107,   108,    63,   109,
      64,    75,    65,    66,    14,    18,    34,   144,    19,    31,
      41,   169,   129,    70,    71,    95,   128,   145,    67,   147,
     165,   189,   148,   149,   150,   151,   224,   152,   153,   247,
     248,   154,   155,   159,   194,   207,   208,   192,   180,   156
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -125
static const yytype_int16 yypact[] =
{
      10,   -40,    37,  -125,  -125,    27,  -125,    49,   -42,  -125,
    -125,     8,  -125,  -125,    65,  -125,    71,    39,    64,  -125,
      48,  -125,  -125,  -125,  -125,    68,  -125,    85,  -125,  -125,
    -125,    33,  -125,   -18,    53,  -125,    34,   191,    41,  -125,
      48,    58,    57,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,   -10,    13,   -33,  -125,  -125,  -125,  -125,  -125,
      60,    -4,    24,   -45,    46,  -125,  -125,  -125,  -125,  -125,
      61,  -125,    48,    62,    66,   191,  -125,  -125,  -125,  -125,
     191,   191,  -125,  -125,  -125,  -125,  -125,  -125,  -125,   191,
    -125,  -125,  -125,  -125,  -125,     4,    67,    72,  -125,    47,
      73,    74,    77,   191,  -125,   191,   191,   191,   191,   191,
      44,    86,    75,  -125,    94,  -125,  -125,  -125,  -125,    98,
    -125,  -125,  -125,  -125,  -125,  -125,    96,    48,  -125,   160,
    -125,    97,  -125,  -125,  -125,  -125,  -125,  -125,    82,    76,
     103,    89,   -26,  -125,   122,  -125,    93,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,   110,   160,  -125,   117,
     119,   191,   191,   113,   191,   125,   165,  -125,   176,   148,
     118,   191,   137,   138,   169,    -7,  -125,  -125,   121,  -125,
     131,   191,  -125,   170,   141,   143,   175,   191,   142,   191,
     135,   176,   161,   145,   162,   191,  -125,  -125,   168,   158,
     191,   156,  -125,   131,   171,   195,   159,   185,   162,    -6,
      12,    45,  -125,   184,   177,  -125,  -125,  -125,   225,  -125,
     183,  -125,   191,  -125,   218,   205,   199,   116,   191,  -125,
    -125,  -125,   202,   160,   211,  -125,  -125,   236,   192,  -125,
    -125,   123,   238,  -125,   160,   217,   193,   234,   238,  -125,
     214,   220,  -125,  -125,  -125,   154,   248,  -125
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,  -125,  -125,  -125,   250,  -125,  -125,  -125,  -125,
    -125,    19,  -125,   132,  -125,  -125,  -125,   -37,  -125,  -125,
    -125,  -125,   -79,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -121,   187,   133,  -125,  -125,  -125,  -124,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,    14,
    -125,  -125,  -125,  -125,  -125,    55,  -125,    63,    70,  -125
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -27
static const yytype_int16 yytable[] =
{
      58,   101,   102,    92,    80,   146,    93,   222,    81,   157,
     104,    80,    11,     1,    12,   164,     3,   135,   136,   137,
      83,    84,     8,    36,   119,    37,   120,   121,   122,   123,
     124,   225,   187,   146,   223,   188,    26,     4,   100,    29,
      85,    86,    87,    88,   138,   139,   140,   141,    76,    77,
     135,   136,   137,    21,    22,     8,    23,    24,   110,     8,
     111,    25,    21,    22,    15,    23,    24,     6,   142,    17,
      28,    78,    79,    90,    91,   210,   211,   138,   139,   140,
     141,   226,    20,    27,    30,   175,   146,   146,    32,    35,
      40,   227,   183,    42,    68,    72,   -26,    82,    94,    96,
     125,   142,   233,   146,    98,    99,   115,   113,   199,   146,
     114,   116,   117,   161,   127,   241,   209,   146,   244,   118,
     146,   135,   136,   137,   172,   173,     8,   -14,   135,   136,
     137,   146,   255,     8,   130,   237,   132,    36,   160,   158,
     162,   166,   245,   232,   193,   163,   167,   168,   138,   139,
     140,   141,   201,   174,   170,   138,   139,   140,   141,   135,
     136,   137,   171,   214,     8,   135,   136,   137,   176,   177,
       8,   181,   142,   256,   182,   184,   185,   186,   190,   142,
     191,   196,   195,   197,   198,   200,   138,   139,   140,   141,
     202,   238,   138,   139,   140,   141,    43,    44,   205,   204,
     213,   206,    45,    46,    47,    48,    49,    50,   212,   215,
     142,    43,    44,    51,   218,   219,   142,    45,    46,    47,
      48,    49,    50,   220,   217,    52,    53,   228,    51,   230,
     229,   178,    54,    55,    56,    57,   231,   234,   235,   236,
      52,    53,   239,   240,   242,   243,   246,    54,    55,    56,
      57,   249,   250,   251,   253,   254,   257,    10,   133,    97,
     134,   203,   252,   221,     0,     0,   216
};

static const yytype_int16 yycheck[] =
{
      37,    80,    81,    48,    37,   129,    51,    13,    41,   130,
      89,    37,    54,     3,    56,    41,    56,     5,     6,     7,
      24,    25,    10,    41,   103,    43,   105,   106,   107,   108,
     109,    19,    39,   157,    40,    42,    17,     0,    75,    20,
      44,    45,    46,    47,    32,    33,    34,    35,    58,    59,
       5,     6,     7,    14,    15,    10,    17,    18,    54,    10,
      56,    22,    14,    15,    56,    17,    18,    40,    56,     4,
      22,    58,    59,    49,    50,   196,   197,    32,    33,    34,
      35,    36,    11,    19,    16,   164,   210,   211,     3,    56,
      37,   212,   171,    59,    53,    37,    39,    37,    52,    38,
      56,    56,   223,   227,    42,    39,    59,    40,   187,   233,
      38,    38,    38,    37,    39,   236,   195,   241,   239,    42,
     244,     5,     6,     7,   161,   162,    10,    41,     5,     6,
       7,   255,   253,    10,    40,    19,    38,    41,    56,    42,
      37,    19,    19,   222,   181,    56,    53,    37,    32,    33,
      34,    35,   189,    40,    37,    32,    33,    34,    35,     5,
       6,     7,    43,   200,    10,     5,     6,     7,    43,     4,
      10,    23,    56,    19,    56,    38,    38,     8,    57,    56,
      49,    40,    12,    40,     9,    43,    32,    33,    34,    35,
      55,   228,    32,    33,    34,    35,    20,    21,    53,    38,
      42,    39,    26,    27,    28,    29,    30,    31,    40,    53,
      56,    20,    21,    37,    19,    56,    56,    26,    27,    28,
      29,    30,    31,    38,    53,    49,    50,    43,    37,     4,
      53,    55,    56,    57,    58,    59,    53,    19,    33,    40,
      49,    50,    40,    32,     8,    53,     8,    56,    57,    58,
      59,    34,    59,    19,    40,    35,     8,     7,   126,    72,
     127,   191,   248,   208,    -1,    -1,   203
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    61,    56,     0,    62,    40,    64,    10,    63,
      65,    54,    56,    68,    94,    56,    66,     4,    95,    98,
      11,    14,    15,    17,    18,    22,    71,    19,    22,    71,
      16,    99,     3,    67,    96,    56,    41,    43,    72,    73,
      37,   100,    59,    20,    21,    26,    27,    28,    29,    30,
      31,    37,    49,    50,    56,    57,    58,    59,    77,    78,
      80,    82,    85,    88,    90,    92,    93,   108,    53,    71,
     103,   104,    37,    74,    75,    91,    58,    59,    58,    59,
      37,    41,    37,    24,    25,    44,    45,    46,    47,    81,
      49,    50,    48,    51,    52,   105,    38,   103,    42,    39,
      77,    82,    82,    79,    82,    83,    84,    86,    87,    89,
      54,    56,    69,    40,    38,    59,    38,    38,    42,    82,
      82,    82,    82,    82,    82,    56,    70,    39,   106,   102,
      40,    76,    38,    73,   104,     5,     6,     7,    32,    33,
      34,    35,    56,    65,    97,   107,   108,   109,   112,   113,
     114,   115,   117,   118,   121,   122,   129,   102,    42,   123,
      56,    37,    37,    56,    41,   110,    19,    53,    37,   101,
      37,    43,    77,    77,    40,    82,    43,     4,    55,    77,
     128,    23,    56,    82,    38,    38,     8,    39,    42,   111,
      57,    49,   127,    77,   124,    12,    40,    40,     9,    82,
      43,    77,    55,   128,    38,    53,    39,   125,   126,    82,
     102,   102,    40,    42,    77,    53,   127,    53,    19,    56,
      38,   125,    13,    40,   116,    19,    36,   102,    43,    53,
       4,    53,    82,   102,    19,    33,    40,    19,    77,    40,
      32,   102,     8,    53,   102,    19,     8,   119,   120,    34,
      59,    19,   119,    40,    35,   102,    19,     8
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
# if YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1455 of yacc.c  */
#line 91 "parser_tlaloc.y"
    {insert_proc_to_table(yylval.str, "global"); proc = yylval.str;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 91 "parser_tlaloc.y"
    {print_var_table(proc); reset_block_vars(); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 98 "parser_tlaloc.y"
    {name = yylval.str;;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 98 "parser_tlaloc.y"
    { 
                var_type = yylval.str; 
                set_dimension();
            ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 108 "parser_tlaloc.y"
    {insert_vars_to_proc_table(yylval.str, var_type, 0);;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 109 "parser_tlaloc.y"
    {insert_vars_to_proc_table(yylval.str, var_type, 0);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 110 "parser_tlaloc.y"
    {name = yylval.str; set_dimension();;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 125 "parser_tlaloc.y"
    {
                       get_constant(yylval.integer);
                    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 128 "parser_tlaloc.y"
    { first_dim = yylval.integer; ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 128 "parser_tlaloc.y"
    { get_constant(yylval.integer * first_dim); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 131 "parser_tlaloc.y"
    { generate_relational_quadruple(); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 132 "parser_tlaloc.y"
    { generate_relational_quadruple(); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 135 "parser_tlaloc.y"
    { insert_to_StackOper('['); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 136 "parser_tlaloc.y"
    { remove_from_StackOper(); generate_exp_quadruples(); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 139 "parser_tlaloc.y"
    { insert_to_StackOper(212); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 140 "parser_tlaloc.y"
    { insert_to_StackOper(214); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 141 "parser_tlaloc.y"
    { insert_to_StackOper(225); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 142 "parser_tlaloc.y"
    { insert_to_StackOper(211); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 143 "parser_tlaloc.y"
    { insert_to_StackOper(225); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 144 "parser_tlaloc.y"
    { insert_to_StackOper(231); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 147 "parser_tlaloc.y"
    { insert_to_StackOper('a'); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 148 "parser_tlaloc.y"
    { insert_to_StackOper('o'); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 149 "parser_tlaloc.y"
    { insert_to_StackOper('>'); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 150 "parser_tlaloc.y"
    { insert_to_StackOper('<'); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 151 "parser_tlaloc.y"
    { insert_to_StackOper('!'); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 152 "parser_tlaloc.y"
    { insert_to_StackOper('i'); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 155 "parser_tlaloc.y"
    { generate_add_sust_quadruple(); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 156 "parser_tlaloc.y"
    { insert_to_StackOper('+'); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 156 "parser_tlaloc.y"
    { generate_add_sust_quadruple(); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 157 "parser_tlaloc.y"
    { insert_to_StackOper('-'); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 157 "parser_tlaloc.y"
    { generate_add_sust_quadruple(); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 160 "parser_tlaloc.y"
    { generate_mult_div_quadruple(); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 161 "parser_tlaloc.y"
    { insert_to_StackOper('*'); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 161 "parser_tlaloc.y"
    { generate_mult_div_quadruple(); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 162 "parser_tlaloc.y"
    { insert_to_StackOper('/'); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 162 "parser_tlaloc.y"
    { generate_mult_div_quadruple(); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 165 "parser_tlaloc.y"
    { generate_exponential_quadruple(); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 166 "parser_tlaloc.y"
    { insert_to_StackOper('^'); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 166 "parser_tlaloc.y"
    { generate_exponential_quadruple(); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 171 "parser_tlaloc.y"
    { insert_to_StackOper('['); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 171 "parser_tlaloc.y"
    { remove_from_StackOper(); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 172 "parser_tlaloc.y"
    { insert_cte_int_to_StackO(yylval.integer); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 173 "parser_tlaloc.y"
    { insert_cte_decimal_to_StackO(yylval.integer); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 174 "parser_tlaloc.y"
    { insert_cte_int_to_StackO(yylval.integer * -1); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 175 "parser_tlaloc.y"
    { insert_cte_decimal_to_StackO(yylval.integer * -1); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 181 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 182 "parser_tlaloc.y"
    { insert_cte_int_to_StackO(yylval.integer); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 183 "parser_tlaloc.y"
    { insert_cte_string_to_StackO(yylval.str); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 184 "parser_tlaloc.y"
    { insert_cte_decimal_to_StackO(yylval.decimal); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 193 "parser_tlaloc.y"
    {insert_proc_to_table(yylval.str, "void"); proc = yylval.str;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 193 "parser_tlaloc.y"
    {print_var_table(proc);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 196 "parser_tlaloc.y"
    {type = yylval.str;;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 196 "parser_tlaloc.y"
    {insert_proc_to_table(yylval.str, type); proc = yylval.str;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 196 "parser_tlaloc.y"
    {print_var_table(proc);;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 204 "parser_tlaloc.y"
    {var_type = yylval.str;;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 223 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 223 "parser_tlaloc.y"
    { insert_to_StackOper('='); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 223 "parser_tlaloc.y"
    { generate_exp_quadruples(); reset_temp_vars(); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 260 "parser_tlaloc.y"
    { remove_from_StackOper(); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 263 "parser_tlaloc.y"
    { insert_to_StackOper(215); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 263 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); generate_exp_quadruples(); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 263 "parser_tlaloc.y"
    { remove_from_StackOper(); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 269 "parser_tlaloc.y"
    { insert_id_to_StackO(yylval.str); generate_exp_quadruples(); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 275 "parser_tlaloc.y"
    { generate_exp_quadruples(); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 278 "parser_tlaloc.y"
    { insert_to_StackOper(213); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 278 "parser_tlaloc.y"
    { insert_to_StackOper(228); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2164 "parser_tlaloc.tab.c"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1675 of yacc.c  */
#line 280 "parser_tlaloc.y"


