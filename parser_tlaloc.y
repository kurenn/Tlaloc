%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	extern int yylineno;
	char *type;
	char *name;
	char *proc;
    int dimension = 0;
	
	void yyerror(const char *message)
	{
	  fprintf(stderr, "error: '%s' - LINE '%d'", message, yylineno);
	}
	
	main(int argc, char **argv) {
		create_proc_table();
		yyparse();
		//print_hash_table();
	}
	
	
%}

%union {
	char *str;
	int integer;
	float decimal;
}

%token PROGRAM METHOD PRINT PRINTLINE READ CASE DEFAULT DEFINE AS TO STEP INTEGER DECIMAL MAIN
%token STRING
%token BOOLEAN END FALSO VERDADERO VOID RETURN AND OR ABS COS SIN LOG TAN SQRT
%token FOR WHILE
%token IF SELECT ELSE
%token PAR_ABIERTO PAR_CERRADO COMA DOS_PUNTOS CORCHETE_ABIERTO CORCHETE_CERRADO
%token IGUAL IGUAL_IGUAL MENOR_QUE MAYOR_QUE DIFERENTE POR MAS MENOS DIVISION
%token EXPONENCIAL PUNTO APUNTADOR COMILLAS
%token ID
%token CTE_STRING
%token CTE_DECIMAL
%token CTE_INTEGER
%start tlaloc

%%
 
	tlaloc: PROGRAM ID {insert_proc_to_table(yylval.str, "global"); proc = yylval.str} DOS_PUNTOS vars {print_var_table(proc);} metodo metodo_main END PROGRAM
		  ;
	
	vars: vars vars_def
		  |
		  ;
	
	vars_def: DEFINE declaracion {name = yylval.str;} AS tipo {insert_vars_to_proc_table(name, yylval.str, dimension); dimension = 0 } asignacion_var PUNTO
		    ;
	
	declaracion: APUNTADOR ID
				 | ID
			     ;
	
	
	tipo: INTEGER 
		  | STRING
		  | BOOLEAN 
		  | DECIMAL 
		  | VOID
		  ;
	
    // Manda dimension - 1 para manipular indexaciones de 0 a N-1
	asignacion_var: IGUAL expresion 
	                | CORCHETE_ABIERTO CTE_INTEGER {dimension = yylval.integer -1;} CORCHETE_CERRADO 
	                | CORCHETE_ABIERTO CTE_INTEGER COMA CTE_INTEGER CORCHETE_CERRADO 
	                |   
			        ;		
	
	expresion: exp 
	          | exp operador_logico exp
			  ;
	
	funcion_matematica: math_choices PAR_ABIERTO exp PAR_CERRADO
					  ;
	
	math_choices: ABS
		          | COS
			      | SIN
			      | LOG
			      | TAN
			      | SQRT
				  ;
	
	operador_logico: AND 
				     | OR 
				     | MAYOR_QUE 
					 | MENOR_QUE 
					 | DIFERENTE 
					 | IGUAL_IGUAL 
					 | 
				     ;
				
	exp: termino
		 | termino MAS termino 
		 | termino MENOS termino
	     ;
	
	termino: exponencial 
	         | exponencial POR exponencial 
	  		 | exponencial DIVISION exponencial
		     ;
		
	exponencial: factor 
	  		     | factor EXPONENCIAL
			     ;
	
	factor: var 
	 	    | PAR_ABIERTO expresion PAR_CERRADO 
			| factor_alterno
	        ;
	
	factor_alterno: operadores_binarios factor_alterno_choices
	 	          ;
	
	operadores_binarios: MAS 
		   	            | MENOS 
						| 
	                    ;
	
	factor_alterno_choices: CTE_INTEGER | llamado | funcion_matematica | ID CORCHETE_ABIERTO exp CORCHETE_CERRADO | ID;
	
	var: ID 
		| CTE_INTEGER 
			 | CTE_STRING 
			 | CTE_DECIMAL 
			 | VERDADERO 
			 | FALSO
		   	 ;
		 
	metodo: metodo metodo_def 
			| 
		  ;
	 
	metodo_main: METHOD VOID MAIN {insert_proc_to_table(yylval.str, "void"); proc = yylval.str} PAR_ABIERTO parametros PAR_CERRADO DOS_PUNTOS metodo_body {print_var_table(proc);} END METHOD 
	
	metodo_def: METHOD tipo {type = yylval.str;} ID {insert_proc_to_table(yylval.str, type); proc = yylval.str} PAR_ABIERTO parametros PAR_CERRADO DOS_PUNTOS metodo_body {print_var_table(proc);} RETURN expresion PUNTO END METHOD 
			  ;
	
	metodo_body: metodo_body body_code | ; 
	
	parametros: parametros_def
			  ;
	
	parametros_def: tipo {type = yylval.str } declaracion {insert_vars_to_proc_table(yylval.str, type);} parametros_extra 
		            | 
			  		;
 
	parametros_extra: COMA parametros_def 
	 	  			  | 
					  ;

	body_code: vars_def
			   | asignacion
			   | estatuto
			   | llamado PUNTO
			   | default_functions
			   ;
	
	llamado: ID PAR_ABIERTO exp PAR_CERRADO
		   ;
	
	asignacion: ID IGUAL expresion PUNTO 
				| array_assignment
			    ;
	
	array_assignment: ID CORCHETE_ABIERTO exp CORCHETE_CERRADO IGUAL expresion PUNTO
	 				| ID CORCHETE_ABIERTO exp COMA exp CORCHETE_CERRADO IGUAL expresion PUNTO
					;	
	
	estatuto: if_statement 
		      | for_statement
			  | while_statement
			  | select_statement
			  ;
	
	if_statement: IF PAR_ABIERTO expresion PAR_CERRADO DOS_PUNTOS metodo_body ELSE DOS_PUNTOS metodo_body END IF
				;
	
	
	for_statement: FOR ID IGUAL exp TO exp for_step END FOR
				 ;
	
	for_step: DOS_PUNTOS metodo_body 
			  | STEP exp DOS_PUNTOS metodo_body 
		    ; 
	
	while_statement: WHILE PAR_ABIERTO expresion PAR_CERRADO DOS_PUNTOS metodo_body END WHILE
				   ;
	
	select_statement: SELECT ID DOS_PUNTOS CASE DEFAULT DOS_PUNTOS metodo_body END CASE case_statement END SELECT
				   ;
	
	case_statement: case_statement_def case_statement | 
			        ;
	
	case_statement_def: CASE CTE_INTEGER DOS_PUNTOS metodo_body END CASE
				  ;
				
	default_functions: default_choices PAR_ABIERTO default_function_input_def default_function_input PAR_CERRADO PUNTO | read
				     ;
	
	read: READ PAR_ABIERTO ID ids PAR_CERRADO PUNTO
		;
	
	ids: ids_def ids | 
	   ;
	
	ids_def: COMA ID
		   ;
	 
	default_function_input: MAS default_function_input_def default_function_input | 
					      ;
					
	default_function_input_def: expresion | COMILLAS CTE_STRING COMILLAS
						      ;
	
	default_choices: PRINT | PRINTLINE;
	
%%
