%{
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
    int step_presence = 1;  // Identificador de si existe o no step en el for
    int parameter = 0;      // Si una variable es parametro, se manda en 1, si es local, 0
    int params_counter=0;   // Cuenta parametros que se mandan de un llamada de metodo
    char *id_array= "";          // ID que guarda la variable que se le asigna un array       

    // Constantes para la identificacion de operadores en la generacion de cuadruplos
    enum symbols {PRINT_S=213, PRINTLINE_S=228, READINT_S=215, READLINE_S=216, RETURN_S=224, AND_S=197, OR_S=198, ABS_S=212,    
				  COS_S=214, SIN_S=225, LOG_S=211, TAN_S=226, SQRT_S=231, RET_S=166, __TRUE_S=217, __FALSE_S=203, GOTOF_S=205, 
				  GOTO_S=206, GOSUB_S=209, GOTOV_S=207, EQUALS_S=61, SAME_S=122, LT_S=60, GT_S=62, DIFF_S=123, TIMES_S=42, PLUS_S=43,
				  MINUS_S=45, DIV_S=47, EXP_S=94, POINTER_S=107, G_EQUAL_T_S=124, L_EQUAL_T_S=125, OPEN_BRACKET_S=91, GOTOFOR_S=208, 
				  GOTOWHILE_S=207, INDEX_S=500, ARRAY_S=501 };

    // Dimensiones para cada tipo de variable, si es que se declaran arreglos
    int integer_dimension = 0, string_dimension = 0, boolean_dimension = 0, decimal_dimension = 0;
	
	/**
	#Nombre: yyerror
	#Descripcion: Imprime el numero de linea en la cual ocurrio el error de sintaxis
	#Parametros: - const char *message
	#Salida: void
	**/
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
	
	/**
	#Nombre: set_dimension
	#Descripcion: Llama al metodo con la dimension que le corresponde a esta nueva nueva variable a agregar
	#Parametros: -
	#Salida: void
	**/
    void set_dimension(){
        if (strcmp(var_type, "integer") == 0) {
                insert_vars_to_proc_table(name, var_type, integer_dimension, parameter);
                integer_dimension = 0;
        } else if (strcmp(var_type, "string") == 0) {
                insert_vars_to_proc_table(name, var_type, string_dimension, parameter);
                string_dimension = 0;
        } else if (strcmp(var_type, "boolean") == 0) {
                insert_vars_to_proc_table(name, var_type, boolean_dimension, parameter);
                boolean_dimension = 0;
        } else if (strcmp(var_type, "decimal") == 0) {
                insert_vars_to_proc_table(name, var_type, decimal_dimension, parameter);
                decimal_dimension = 0;
        } else { 
                insert_vars_to_proc_table(name, var_type, 0, parameter); 
        }
        parameter = 0;  // Asigna 0 nuevamente, indicando que la variable no es un parametro
    }

	/**
	#Nombre: set_dimension
	#Descripcion: Guarda dimension - 1 para manipular indexaciones de 0 a N-1
	#Parametros: -
	#Salida: void
	#Dependencias: set_var_dimension
	**/
    void get_constant_arr(int constant){
        if (strcmp(var_type, "integer") == 0) integer_dimension = constant - 1;
        if (strcmp(var_type, "string") == 0) string_dimension = constant - 1;
        if (strcmp(var_type, "boolean") == 0) boolean_dimension = constant - 1;
        if (strcmp(var_type, "decimal") == 0) decimal_dimension = constant - 1;
        set_var_dimension(constant, name); // Asigna la dimension despues de guardar la constante
    }

    // Guarda dimension - 1 para manipular indexaciones de 0 a N-1 cuando llegan matrices
    void get_constant_mat(int dim1, int dim2){
        int constant = dim1 * dim2;     // Desplazamiento total de la siguiente variable a agregar
        if (strcmp(var_type, "integer") == 0) integer_dimension = constant - 1;
        if (strcmp(var_type, "string") == 0) string_dimension = constant - 1;
        if (strcmp(var_type, "boolean") == 0) boolean_dimension = constant - 1;
        if (strcmp(var_type, "decimal") == 0) decimal_dimension = constant - 1;
        set_mat_dimension(dim1, dim2, name); // Asigna la dimension despues de guardar la constante
    }
    
	/**
	#Nombre: main
	#Descripcion: Metodo principal para la ejecucion de todo el programa
	#Parametros: int argc, char **argv
	#Salida: -
	#Dependencias: create_proc_table, create_constants_table, create_stacks_and_queues, print_to_file, print_hash_table
	**/
	main(int argc, char **argv) {
		create_proc_table();
        create_constants_table();
        create_stacks_and_queues();
		create_quadruples_array();
		yyparse();
		print_to_file();
		//print_hash_table();
        //printf("---------------------------\n\n");
        //system("ruby VMTlaloc/init.rb");    // Ejecuta maquina virtual con comando en consola
	}
	
	
%}

// manipulacion de tipos de daots o casting de estos en la sintaxis
%union {
	char *str;
	int integer;
	float decimal;
}

/**
	Bloque de deficion de tokens
**/

%token PROGRAM METHOD PRINT PRINTLINE READINT READLINE CASE DEFAULT DEFINE AS TO STEP INTEGER DECIMAL MAIN
%token STRING BOOLEAN END FALSO VERDADERO VOID RETURN AND OR ABS COS SIN LOG TAN SQRT CTE_INTEGER
%token FOR WHILE IF SELECT ELSE PAR_ABIERTO PAR_CERRADO COMA DOS_PUNTOS CTE_STRING CTE_DECIMAL
%token CORCHETE_ABIERTO CORCHETE_CERRADO IGUAL IGUAL_IGUAL MENOR_QUE MAYOR_QUE DIFERENTE POR MAS
%token MENOS DIVISION MAYOR_IGUAL MENOR_IGUAL EXPONENCIAL PUNTO APUNTADOR COMILLAS ID
%start tlaloc

%%
 
	tlaloc: PROGRAM ID {insert_proc_to_table(yylval.str, "global"); proc = yylval.str} DOS_PUNTOS vars {print_var_table(proc); reset_block_vars(); } metodo metodo_main END PROGRAM
		  ;
	
	vars: vars vars_def
		  |
		  ;
	
	vars_def: DEFINE declaracion {name = yylval.str;} AS tipo { 
                var_type = yylval.str; 
                parameter = 0;
                set_dimension();
                insert_id_to_StackO(name);
            } asignacion_var PUNTO { remove_from_StackO(); } // Retira el id en caso de no tener asignacion alguna
		    ;
	
	declaracion: APUNTADOR ID
				 | ID
			     ;
	
    params: APUNTADOR ID {insert_vars_to_proc_table(yylval.str, var_type, 0, 1);}
				 | ID {insert_vars_to_proc_table(yylval.str, var_type, 0, 1);}
                 | ID {name = yylval.str; parameter = 1; set_dimension();} dimension_arreglo
			     ;
	
	tipo: INTEGER { type = "integer"; }
		  | STRING { type = "string"; }
		  | BOOLEAN { type = "boolean"; }
		  | DECIMAL { type = "decimal"; } 
		  | VOID { type = "void"; }
		  ;
	
	asignacion_var: IGUAL { insert_to_StackOper(EQUALS_S); } expresion { generate_exp_quadruples(); reset_temp_vars(); }
                    | dimension_arreglo
	                |   
			        ;

    dimension_arreglo: CORCHETE_ABIERTO CTE_INTEGER {
                       get_constant_arr(yylval.integer);
                    } CORCHETE_CERRADO
	                | CORCHETE_ABIERTO CTE_INTEGER { first_dim = yylval.integer; } COMA CTE_INTEGER { get_constant_mat(first_dim, yylval.integer); } CORCHETE_CERRADO
                    ;
	
	expresion: exp { generate_relational_quadruple(); }
	          | exp operador_logico exp { generate_relational_quadruple(); }
			  ;
	
	funcion_matematica: math_choices PAR_ABIERTO { insert_to_StackOper(OPEN_BRACKET_S); } exp 
                                     PAR_CERRADO { remove_from_StackOper(); generate_exp_quadruples(); }
					  ;
	
	math_choices: ABS { insert_to_StackOper(ABS_S); } 
		          | COS { insert_to_StackOper(COS_S); } 
			      | SIN { insert_to_StackOper(SIN_S); } 
			      | LOG { insert_to_StackOper(LOG_S); } 
			      | TAN { insert_to_StackOper(TAN_S); } 
			      | SQRT { insert_to_StackOper(SQRT_S); } 
				  ;
	
	operador_logico: AND { insert_to_StackOper(AND_S); }
				     | OR { insert_to_StackOper(OR_S); }
				     | MAYOR_QUE { insert_to_StackOper(GT_S); }
					 | MENOR_QUE { insert_to_StackOper(LT_S); }
					 | DIFERENTE { insert_to_StackOper(DIFF_S); }
					 | IGUAL_IGUAL { insert_to_StackOper(SAME_S); }
					 | MAYOR_IGUAL { insert_to_StackOper(G_EQUAL_T_S); }
					 | MENOR_IGUAL { insert_to_StackOper(L_EQUAL_T_S); }
				     ;
				
	exp: termino { generate_add_sust_quadruple(); }
		 | termino MAS { insert_to_StackOper(PLUS_S); } exp { generate_add_sust_quadruple(); }
		 | termino MENOS { insert_to_StackOper(MINUS_S); } exp { generate_add_sust_quadruple(); }
	     ;
	
	termino: exponencial { generate_mult_div_quadruple(); }
	         | exponencial POR { insert_to_StackOper(TIMES_S); } exp { generate_mult_div_quadruple(); }
	  		 | exponencial DIVISION { insert_to_StackOper(DIV_S); } exp { generate_mult_div_quadruple(); }
		     ;
		
	exponencial: factor { generate_exponential_quadruple(); }
	  		     | factor EXPONENCIAL { insert_to_StackOper(EXP_S); } exp { generate_exponential_quadruple(); }
			     ;
	
    // Inserta corchete para distinguir de parentesis como fondo falso 91 = [ -- 93 = ]
	factor: var
	 	    | PAR_ABIERTO { insert_to_StackOper(OPEN_BRACKET_S); } expresion PAR_CERRADO { remove_from_StackOper(); }
            | MAS CTE_INTEGER { insert_cte_int_to_StackO(yylval.integer); } // Acepta enteros y decimales negativos
            | MENOS CTE_INTEGER { insert_cte_int_to_StackO(yylval.integer * -1); }
			| factor_alterno
	        ;
	
	factor_alterno: llamado 
                    | funcion_matematica 
                    | ID { name = yylval.str; /*insert_id_to_StackO(name);*/ insert_to_StackOper(INDEX_S); } factor_arreglo
            ;

    factor_arreglo: CORCHETE_ABIERTO exp CORCHETE_CERRADO { generate_exp_quadruples(); insert_arr_index_to_StackO(name); insert_movement_quadruple(name); }
                    | CORCHETE_ABIERTO exp { insert_arr_index_to_StackO(name); remove_from_StackO(); } COMA {} exp CORCHETE_CERRADO { generate_exp_quadruples(); insert_arr2_index_to_StackO(name); insert_movement_quadruple(name); }
                    ;

	var: ID { insert_id_to_StackO(yylval.str); }
		| CTE_INTEGER { insert_cte_int_to_StackO(yylval.integer); }
			 | CTE_STRING { insert_cte_string_to_StackO(yylval.str); }
			 | CTE_DECIMAL { insert_cte_decimal_to_StackO(yylval.str); }
			 | VERDADERO  { insert_cte_boolean_to_StackO(yylval.str); }
			 | FALSO      { insert_cte_boolean_to_StackO(yylval.str); }
		   	 ;
		 
	metodo: metodo metodo_def 
			| 
		  ;
	 
	metodo_main: METHOD VOID MAIN { fill_goto_main(); insert_proc_to_table(yylval.str, "void"); proc = yylval.str} PAR_ABIERTO parametros PAR_CERRADO DOS_PUNTOS { generate_beginning_address(); } metodo_body {print_var_table(proc);} END METHOD
                ;
	
	metodo_def: METHOD tipo ID { insert_proc_to_table(yylval.str, type); insert_proc_as_global_var(type, yylval.str); proc = yylval.str} 
				PAR_ABIERTO parametros PAR_CERRADO DOS_PUNTOS { generate_beginning_address(); } 
				metodo_body {print_var_table(proc); type = ""; } {insert_to_StackOper(RETURN_S); insert_id_to_StackO(proc);}
				RETURN expresion {generate_return_action(proc);} PUNTO END METHOD { generate_ret_action(); } 
			  ;
	
	metodo_body: metodo_body body_code | ; 
	
	parametros: parametros_def
			  ;
	
	parametros_def: tipo {var_type = yylval.str;} params parametros_extra 
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
	
	llamado: ID { name=yylval.str; verify_non_method_presence(name); } llamado_params { generate_gosub(name); params_counter = 0; }
		   ;

    llamado_params: PAR_ABIERTO { generate_era_action(); } exp { params_semantic_validation(name, params_counter); params_counter = params_counter + 1; } exp_extra PAR_CERRADO { check_params_number(name, params_counter); }
                    | PAR_ABIERTO  { generate_era_action(); }  PAR_CERRADO { check_params_number(name, params_counter); }
	                ;
        
    exp_extra: COMA exp { params_semantic_validation(name, params_counter); params_counter = params_counter + 1; } exp_extra
                |
                ;

    // Guarda direccion de memoria a la cual se le asignara el resultado en el cuadruplo de asignacion
	asignacion: ID { array_in_id(yylval.str); name = yylval.str; insert_id_to_StackO(yylval.str); } IGUAL {insert_to_StackOper(EQUALS_S); } expresion PUNTO {generate_exp_quadruples(); reset_temp_vars(); }
				| ID { name = yylval.str; insert_id_to_StackO(name); insert_to_StackOper(INDEX_S); } array_assignment {  generate_exp_quadruples(); reset_temp_vars(); }
			    ;

	// Genera el cuadruplo de verificacion de dimension y al final suma desplazamiento
    array_assignment: CORCHETE_ABIERTO exp CORCHETE_CERRADO { generate_exp_quadruples(); insert_arr_index_to_StackO(name); insert_movement_quadruple(name); remove_from_StackOper(); } IGUAL { insert_to_StackOper(EQUALS_S); } expresion PUNTO 
	// Genera los dos cuadruplos de verificacion de dimensiones y al final suma desplazamiento
                    | CORCHETE_ABIERTO exp { insert_arr_index_to_StackO(name); remove_from_StackO();  } COMA {} exp CORCHETE_CERRADO { generate_exp_quadruples(); insert_arr2_index_to_StackO(name); insert_movement_quadruple(name); remove_from_StackOper(); } IGUAL { insert_to_StackOper(EQUALS_S); } expresion PUNTO
                                       ;	
	
	estatuto: if_statement 
		      | for_statement
			  | while_statement
			  | select_statement
			  ;
	
	if_statement: IF PAR_ABIERTO expresion PAR_CERRADO DOS_PUNTOS {generate_gotoF_if_quadruple();} metodo_body else_statement END IF {fill_if();}
				;
	
	else_statement: ELSE DOS_PUNTOS {generate_goto_if_quadruple();} metodo_body | ;
	
	for_statement: FOR ID { name = yylval.str; insert_id_to_StackO(name); } IGUAL { insert_to_StackOper(EQUALS_S); } exp { generate_exp_quadruples(); remove_from_StackOper(); reset_temp_vars(); } TO { push_cont_to_stack_jumps(); } exp { insert_id_to_StackO(name); generate_for_limit_quadruple(); reset_temp_vars(); } for_step END FOR { fill_for(step_presence); reset_temp_vars(); step_presence = 1; }
				 ;
	
	for_step: DOS_PUNTOS { generate_gotoF_for_quadruple(); } metodo_body 
			  | STEP exp { insert_id_to_StackO(name); generate_step_for_quadruple(); reset_temp_vars(); } DOS_PUNTOS { generate_gotoF_for_quadruple(); } metodo_body { fill_step(); step_presence = 0; }
		    ; 
	
	while_statement: WHILE PAR_ABIERTO{push_cont_to_stack_jumps();} expresion PAR_CERRADO DOS_PUNTOS{generate_while_gotoF_quadruple();} metodo_body END WHILE {fill_while();}
				   ;
	
	select_statement: SELECT ID DOS_PUNTOS CASE DEFAULT DOS_PUNTOS metodo_body END CASE case_statement END SELECT
				   ;
	
	case_statement: case_statement_def case_statement | 
			        ;
	
	case_statement_def: CASE CTE_INTEGER DOS_PUNTOS metodo_body END CASE
				  ;
				
    // Siempre remueve al final lo que hay en la pila de operandos para que no haya información en el siguiente renglon
	default_functions: { /*remove_from_StackDimensions();*/ } default_choices PAR_ABIERTO default_function_input_def default_function_input PAR_CERRADO PUNTO { remove_from_StackOper(); remove_from_StackO(); } | readint | readline
				     ;
	
	readint: READINT { insert_to_StackOper(READINT_S); } PAR_ABIERTO ID { insert_id_to_StackO(yylval.str); generate_exp_quadruples(); }  ids PAR_CERRADO PUNTO { remove_from_StackOper(); remove_from_StackO(); }
		;

	readline: READLINE { insert_to_StackOper(READLINE_S); } PAR_ABIERTO ID { insert_id_to_StackO(yylval.str); generate_exp_quadruples(); }  ids PAR_CERRADO PUNTO { remove_from_StackOper(); remove_from_StackO(); }
        ;
	
	ids: ids_def ids | 
	   ;
	
	ids_def: COMA ID { insert_id_to_StackO(yylval.str); generate_exp_quadruples(); } 
		   ;
	 
	default_function_input: MAS default_function_input_def default_function_input | 
					      ;
					
	default_function_input_def: expresion { generate_exp_quadruples(); } | COMILLAS expresion{ generate_exp_quadruples(); }  COMILLAS
						      ;
	
	default_choices: PRINT { insert_to_StackOper(PRINT_S); } | PRINTLINE { insert_to_StackOper(PRINTLINE_S); };
	
%%
