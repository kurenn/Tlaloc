#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Bloque de identificacion de tokens
enum symbols {PRINT=213, PRINTLINE=228, READINT=215, READLINE=216, RETURN=224, AND=197, OR=198, ABS=212, COS=214, SIN=225,
	 		  LOG=211, TAN=226, SQRT=231, RET=166, __TRUE=217, __FALSE=203, GOTOF=205, GOTO=206, GOSUB=209, ERA=999,
	 		  EQUALS=61, SAME=122, LT=60, GT=62, DIFF=123, TIMES=42, PLUS=43, MINUS=45, DIV=47, EXP=94, VER=100, PARAM=900,
	  		  POINTER=107, G_EQUAL_T=124, L_EQUAL_T=125, OPEN_BRACKET=91, GOTOWHILE=207, GOTOFOR=208, STEP=666, INDEX=500, ARRAY=501};

static GHashTable *proc_table; // HashTable de procedimientos (key) leidos. (value) apunta a type_table
static GHashTable *constants_table;  //HashTable con las constantes usadas en todo el programa
/**Bloque para declaracion de pilas **/
static GQueue *StackO;
static GQueue *StackOper;
static GQueue *StackTypes;
static GQueue *Quadruples;
static GQueue *StackJumps; 
static GQueue *StackDimensions;// Pila de dimensiones para que pueda imprimir el desplazamiento default_functions 
static GQueue *StackSteps;     // Pila para el control de steps en fors
/**Bloque para declaracion de pilas **/

char *current_function;        // Variable que mantiene el nombre de la funcion actual
char *global_function;         // Variable que mantiene el nombre del programa
int quadruple_index = 0;       // Contador de cuadruplos
FILE *middle_code;			   //Archivo de cuadruplos
static GPtrArray *QuadruplesList; //lista de cuadruplosarray_function_dimension

int array_function_dimension = 0; // Guarda el valor por el cual se multiplicara la matriz (funcion para el desplazamiento)

// Inicio de bloques de memoria para cada tipo de variables
enum memory_blocks {GINTEGERS=5000, GSTRINGS=10000, GBOOLEANS=15000, GDECIMALS=20000, 
                    LINTEGERS=25000, LSTRINGS=30000, LBOOLEANS=35000, LDECIMALS=40000,
                    TINTEGERS=45000, TSTRINGS=50000, TBOOLEANS=55000, TDECIMALS=60000, 
                    CINTEGERS=65000, CSTRINGS=70000, CBOOLEANS=75000, CDECIMALS=80000};


// Contadores que controlan el incremento de las direcciones virtuales para las variables
int global_integers_count = 0, global_strings_count = 0,
    global_booleans_count = 0, global_decimals_count = 0, 
    local_integers_count = 0, local_strings_count = 0,
    local_booleans_count = 0, local_decimals_count = 0,
    temp_integers_count = TINTEGERS, temp_strings_count = TSTRINGS,
    temp_booleans_count = TBOOLEANS, temp_decimals_count = TDECIMALS,
    const_integers_count = CINTEGERS, const_strings_count = CSTRINGS,
    const_booleans_count = CBOOLEANS, const_decimals_count = CDECIMALS;

// type_table: tabla que guarda el tipo de valor de retorno de la funcion leia en programa
typedef struct {
	char *method_type;          // Tipo de retorno del metodo
    int beginning_address;      // Cuadruplo de inicio del procedimiento (cont: quadruple_index)
    int params_declared;        // Numero de parametros declarados (para el workspace en ejecucion)
    int local_vars_declared;    // Numero de variables locales definidas (para el workspace en ejecucion)
    GQueue *ParamsTypes;         // Guarda los tipos de valor de los parametros
    GHashTable *params_table;   // Parametros que recibe la funcion 
	GHashTable *h_table;        // Tabla de variables del metodo
}type_table;


// vars_memory: almacena el tipo de dato de la variable y su direccion virtual. 
// Key de la hash table que apunta type_table
typedef struct {
    char *type;
    int virtual_address;
    int var_dimension;      // Primera dimension, en caso de ser un arreglo unidimensional
    int mat_dimension;      // Segunda dimension, en caso de ser una matriz
}vars_memory;

//Estructura para la insercion del cuadruplo en el arreglo de apuntadores
typedef struct {
	char* operator;
	char* first_oper;
	char* second_oper;
	char* result;
}quad_struct;

quad_struct *step_struct;   // Estructura que almacena la exp step del for para agregarla al final de los cuadruplos

/**
#Nombre: create_proc_table
#Descripcion: Inicializa la tabla de hashing de procedimientos
#Parametros: -
#Salida: void
**/
void create_proc_table(){
	proc_table = g_hash_table_new(g_str_hash, g_str_equal); 
}

/**
#Nombre: create_constants_table
#Descripcion: Inicializa la tabla de constantes para todo el programa
#Parametros: -
#Salida: void
**/
void create_constants_table(){
	constants_table = g_hash_table_new(g_str_hash, g_str_equal); // key: constante | value: vars_memory(struct)
}

/**
#Nombre: create_quadruples_array
#Descripcion: Inicializa un arreglo de apuntadores para el almacenamiento de los cuadruplos
#Parametros: -
#Salida: void
**/
void create_quadruples_array(){
	QuadruplesList = g_ptr_array_new();
    insert_quadruple_to_array(GOTO, 0, 0, 0);   // Genera el primer cuadruplo que va directo a la funcion main	
}

/**
#Nombre: valid_var_types
#Descripcion: Devuelve un valor que se reconoce posteriormente sobre los tipos de operaciones 
			  que se pueden llevar a cabo en el programa con distintos tipos de datos
#Parametros: char *first_type, char *second_type
#Salida: int option
**/
int valid_var_types(char *first_type, char *second_type){
	// Opcion es 0 con tipos incompatibles. Opcion es 1 por default ya que los demas son validos. 
    int option;
    if (strcmp(first_type,"integer") == 0 && strcmp(second_type,"boolean") == 0
        || strcmp(first_type,"string") == 0 && strcmp(second_type,"boolean") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"decimal") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"integer") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"string") == 0
        || strcmp(first_type,"decimal") == 0 && strcmp(second_type,"boolean") == 0) 
        option = 0;
    else if (strcmp(first_type,"integer") == 0 && strcmp(second_type,"integer") == 0)
        option = 1;
    else if (strcmp(first_type,"integer") == 0 && strcmp(second_type,"string") == 0
        || strcmp(first_type,"string") == 0 && strcmp(second_type,"decimal") == 0
        || strcmp(first_type,"string") == 0 && strcmp(second_type,"integer") == 0
        || strcmp(first_type,"decimal") == 0 && strcmp(second_type,"string") == 0
        || strcmp(first_type,"string") == 0 && strcmp(second_type,"string") == 0)
        option = 2;
    else if (strcmp(first_type,"integer") == 0 && strcmp(second_type,"decimal") == 0
        || strcmp(first_type,"decimal") == 0 && strcmp(second_type,"integer") == 0
        || strcmp(first_type,"decimal") == 0 && strcmp(second_type,"decimal") == 0)
        option = 4;
    else if (strcmp(first_type,"boolean") == 0 && strcmp(second_type,"boolean") == 0)
        option = 3;
    
    return option;
}

/**
#Nombre: create_stacks_and_queues
#Descripcion: Inicializa todas las pilas a utilizar durante la generacion de cuadruplos
#Parametros: -
#Salida: void
**/
void create_stacks_and_queues(){
	StackO = g_queue_new(); 
    StackOper = g_queue_new(); 
    StackTypes = g_queue_new(); 
    Quadruples = g_queue_new(); 
	StackJumps = g_queue_new();
    StackSteps = g_queue_new();
    StackDimensions = g_queue_new();
}

/**
#Nombre: reset_temp_vars
#Descripcion: Inicializa variables temporales para las operaciones dentro de cada funcion
#Parametros: -
#Salida: void
**/
void reset_temp_vars(){
    temp_integers_count = TINTEGERS, temp_strings_count = TSTRINGS,
    temp_booleans_count = TBOOLEANS, temp_decimals_count = TDECIMALS;
}

/**
#Nombre: reset_memory_counters
#Descripcion: Inicializa variables locales a 0 para cada nuevo procedimiento
#Parametros: -
#Salida: void
**/
void reset_memory_counters(){
    local_integers_count = 0, local_strings_count = 0,
    local_booleans_count = 0, local_decimals_count = 0;
}

/**
#Nombre: get_var_virtual_address
#Descripcion: Obtiene la direccion virtual de la tabla de hashing de un determinado id
#Parametros: char *id
#Salida: int address
**/
int get_global_virtual_address(char *id){
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
    vars_memory *v_table = g_slice_new(vars_memory);
    v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    int address = v_table->virtual_address;
    return address;
}

/**
#Nombre: get_var_virtual_address
#Descripcion: Obtiene la direccion virtual de la tabla de hashing de un determinado id
#Parametros: char *id
#Salida: int address
**/
int get_var_virtual_address(char *id){
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
    vars_memory *v_table = g_slice_new(vars_memory);
    v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    if (v_table == NULL){   // Si no encuentra en locales, busca en globales
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    }
    if (v_table == NULL){
        printf("Variable '%s' no reconocida en locales ni globales\n", id);
        exit(0);
    }
    int address = v_table->virtual_address;
    return address;
}

/**
#Nombre: get_var_type
#Descripcion: Devuelve el tipo de dato de una variable almacenada en su tabla de hashing
#Parametros: char *id
#Salida: char *this_type
**/
char *get_var_type(char *id){
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
    vars_memory *v_table = g_slice_new(vars_memory);
    v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    if (v_table == NULL){   // Si no encuentra en locales, busca en globales
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    }
    if (v_table == NULL){
        printf("Variable '%s' no reconocida en locales ni globales\n", id);
        exit(0);
    }
    char *this_type = v_table->type;
    return this_type;
}

/**
#Nombre: get_var_dimension
#Descripcion: Obtiene la dimension de una variable (principalmente para el manejo de arreglos)
#Parametros: char *id
#Salida: int dimension
**/
int get_var_dimension(char *id) {
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
    vars_memory *v_table = g_slice_new(vars_memory);
    v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    if (v_table == NULL){   // Si no encuentra en locales, busca en globales
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    }
    if (v_table == NULL){
        printf("Variable '%s' no reconocida en locales ni globales\n", id);
        exit(0);
    }
    int dimension = v_table->var_dimension;
    return dimension;
}

// get_mat_dimension: devuelve la segunda dimension de una variable que es matriz
int get_mat_dimension(char *id) {
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
    vars_memory *v_table = g_slice_new(vars_memory);
    v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    if (v_table == NULL){   // Si no encuentra en locales, busca en globales
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    }
    if (v_table == NULL){
        printf("Variable '%s' no reconocida en locales ni globales\n", id);
        exit(0);
    }
    int dimension = v_table->mat_dimension;
    return dimension;
}

/**
#Nombre: set_var_dimension
#Descripcion: Establece la dimension para una variable (0 en caso de no ser arreglo)
#Parametros: int dimension, char *id
#Salida: void
**/
void set_var_dimension(int dimension, char *id){
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
    vars_memory *v_table = g_slice_new(vars_memory);
    v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    if (v_table == NULL){   // Si no encuentra en locales, busca en globales
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    }
    v_table->var_dimension = dimension - 1;     // Asigna la dimension a la variable que es arreglo
    if (v_table == NULL){
        printf("Variable '%s' no reconocida en locales ni globales\n", id);
        exit(0);
    }
}

// set_mat_dimension: asigna la dimension que le corresponde a la matriz
void set_mat_dimension(int dimension1, int dimension2, char *id){
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
    vars_memory *v_table = g_slice_new(vars_memory);
    v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    if (v_table == NULL){   // Si no encuentra en locales, busca en globales
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        v_table = g_hash_table_lookup(temp_t_table->h_table, (gpointer)id);
    }
    v_table->var_dimension = dimension1 - 1;     // Asigna la dimension1 a la matriz
    v_table->mat_dimension = dimension2 - 1;     // Asigna la dimension2 a la matriz
    if (v_table == NULL){
        printf("Variable '%s' no reconocida en locales ni globales\n", id);
        exit(0);
    }
}

/**
#Nombre: insert_proc_to_table
#Descripcion: Inserta el procedimiento en la tabla de hashing de procedimientos
#Parametros: char *proc, char *tipo
#Salida: void
**/
void insert_proc_to_table(char *proc, char *tipo){
	if (g_hash_table_lookup(proc_table, (gpointer)proc) != NULL){
		printf("El metodo '%s' ya esta dado de alta\n", proc);
		exit(0);
	} else {
		type_table *t_table = g_slice_new(type_table); //Creamos tabla de hashing para los tipos 1x2
		t_table->method_type = tipo;
		t_table->h_table = g_hash_table_new(g_str_hash, g_str_equal); //Tabla de variables inicializada
        t_table->params_table = g_hash_table_new(g_str_hash, g_str_equal); //Tabla de parametros inicializada
        t_table->ParamsTypes = g_queue_new(); 
		g_hash_table_insert(proc_table, (gpointer)proc, (gpointer)t_table);
		current_function = proc;
        reset_memory_counters();    // Reinicia contadores locales de memoria a 0 para nueva metodo
        if (strcmp(tipo, "global") == 0) {
            global_function = proc;
        }
	}
}

/**
#Nombre: insert_vars_to_proc_table
#Descripcion: Inserta las variables a la tabla de hashing de variables que corresponde a cada procedimiento
#Parametros: char *var, char *tipo, int dimension
#Salida: void
**/
void insert_vars_to_proc_table(char *var, char *tipo, int dimension, int parameter){
	 if (g_hash_table_lookup(proc_table, (gpointer)current_function) != NULL) {
		type_table *temp_t_table = g_slice_new(type_table);

        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        if (g_hash_table_lookup(temp_t_table->h_table, (gpointer)var) != NULL ||
            g_hash_table_lookup(temp_t_table->params_table, (gpointer)var) != NULL) {
			printf("La variable '%s' ya esta declarada como global\n", var);
			exit(0);
        }
		temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
        if (g_hash_table_lookup(temp_t_table->h_table, (gpointer)var) != NULL ||
            g_hash_table_lookup(temp_t_table->params_table, (gpointer)var) != NULL) {
			printf("La variable '%s' ya esta declarada en el metodo\n", var);
			exit(0);
		}
        if (dimension < 0) {
			printf("Index out of bounds in %s\n", var);
			exit(0);
		}        
        else {    // Variable no declarada y agregada en la tabla de variables
            vars_memory *v_memory = g_slice_new(vars_memory);
            v_memory->type = tipo;
            v_memory->var_dimension = 0;    // Se inicializan en 0 para evitar futuros conflictos
            v_memory->mat_dimension = 0;    // con variables que nos son ni arreglos ni matrices
            int address;
            if (strcmp(current_function, global_function) == 0) {   // Si las variables son globales
                if (strcmp(tipo, "integer") == 0) {
                        address = GINTEGERS + global_integers_count + dimension;                        
                        global_integers_count = global_integers_count + 1 + dimension;  
                }
                if (strcmp(tipo, "string") == 0) {
                        address = GSTRINGS + global_strings_count + dimension;                        
                        global_strings_count = global_strings_count + 1 + dimension;                        
                }
                if (strcmp(tipo, "boolean") == 0) {
                        address = GBOOLEANS + global_booleans_count + dimension;                        
                        global_booleans_count = global_booleans_count + 1 + dimension;                        
                }
                if (strcmp(tipo, "decimal") == 0) {
                        address = GDECIMALS + global_decimals_count + dimension;                        
                        global_decimals_count = global_decimals_count + 1 + dimension;                        
                }
                v_memory->virtual_address = address;
            }                
            else {  // Si las variables son parte de un metodo
                if (strcmp(tipo, "integer") == 0) {
                        address = LINTEGERS + local_integers_count + dimension;                        
                        local_integers_count = local_integers_count + 1 + dimension;                    
                }
                if (strcmp(tipo, "string") == 0) {
                        address = LSTRINGS + local_strings_count + dimension;                        
                        local_strings_count = local_strings_count + 1 + dimension;                      
                }
                if (strcmp(tipo, "boolean") == 0) {
                        address = LBOOLEANS + local_booleans_count + dimension;                        
                        local_booleans_count = local_booleans_count + 1 + dimension;                         
                }
                if (strcmp(tipo, "decimal") == 0) {
                        address = LDECIMALS + local_decimals_count + dimension;                        
                        local_decimals_count = local_decimals_count + 1 + dimension;                        
                }
                v_memory->virtual_address = address;
            }
            if (parameter == 0) {  
                g_hash_table_insert(temp_t_table->h_table, (gpointer)var, (gpointer)v_memory);
                temp_t_table->local_vars_declared = temp_t_table->local_vars_declared + 1;
            } else { 
                g_hash_table_insert(temp_t_table->params_table, (gpointer)var, (gpointer)v_memory);
                temp_t_table->params_declared = temp_t_table->params_declared + 1;                
                g_queue_push_tail(temp_t_table->ParamsTypes, tipo);
            }        
        }
    } else {
        printf("Error. Procedimiento no existe\n");
        exit(0);
    }
}

void insert_proc_as_global_var(char *tipo, char *id){
    type_table *temp_t_table = g_slice_new(type_table);    
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
    if (g_hash_table_lookup(temp_t_table->h_table, (gpointer)id) != NULL) {
		printf("La funcion '%s' ya esta declarada como variable\n", id);
		exit(0);
    } else {    // Variable no declarada y agregada en la tabla de variables globales
        vars_memory *v_memory = g_slice_new(vars_memory);
        v_memory->type = tipo;
        v_memory->var_dimension = 0;    // Se inicializan en 0 para evitar futuros conflictos
        v_memory->mat_dimension = 0;    // con variables que nos son ni arreglos ni matrices
        int address;
        if (strcmp(tipo, "integer") == 0) {
                address = GINTEGERS + global_integers_count;                        
                global_integers_count = global_integers_count + 1; 
                
        }
        if (strcmp(tipo, "string") == 0) {
                address = GSTRINGS + global_strings_count;                        
                global_strings_count = global_strings_count + 1;                        
        }
        if (strcmp(tipo, "boolean") == 0) {
                address = GBOOLEANS + global_booleans_count;                        
                global_booleans_count = global_booleans_count + 1;                        
        }
        if (strcmp(tipo, "decimal") == 0) {
                address = GDECIMALS + global_decimals_count;                        
                global_decimals_count = global_decimals_count + 1;                        
        }
        v_memory->virtual_address = address;
        g_hash_table_insert(temp_t_table->h_table, (gpointer)id, (gpointer)v_memory);  
    }
}

// Agrega el contador de cuadruplo a la estructura de control del procedimiento para saber donde empieza la funcion
void generate_beginning_address(){
    if (g_hash_table_lookup(proc_table, (gpointer)current_function) != NULL) {
		type_table *temp_t_table = g_slice_new(type_table);
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
        temp_t_table->beginning_address = quadruple_index + 1;  //+1 para dejar listo el siguiente cuadruplo a empezar
    } else {
        printf("Error. Procedimiento no existe\n");
        exit(0);
    }
}

// Genera el cuadruplo de retorno a la funcion original donde se hizo el llamado
void generate_ret_action(){
    insert_quadruple_to_array(RET, 0, 0, 0);
}

// Genera el cuadruplo que retorna un parametro a la funcion original donde se hizo el llamado (return var)
void generate_return_action(char *id){
    insert_quadruple_to_array(RETURN, g_queue_pop_tail(StackO), 0, get_global_virtual_address(id));   
}

// Verifica que una funcion llamada dentro de otra, exista en la tabla de procedimientos
void verify_non_method_presence(char *id){
    if (g_hash_table_lookup(proc_table, (gpointer)id) == NULL) {
        printf("Error. Metodo no declarado en el programa\n");
        exit(0);
    }
}

void generate_era_action() {
    insert_quadruple_to_array(ERA, 0, 0, 0);
}

/**
#Nombre: insert_id_to_StackO
#Descripcion: Inserta el id o variable a la pila de operandos
#Parametros: char *id
#Salida: void
**/
void insert_id_to_StackO(char *id){
    if(id != NULL){     // Control de entrada. Al final de funciones entra el id como nulo, lo omite.
        g_queue_push_tail(StackO, (gpointer)get_var_virtual_address(id));
        g_queue_push_tail(StackTypes, (gpointer)get_var_type(id)); 
    }        
}
 
/**
#Nombre: insert_arr_index_to_StackO
#Descripcion: Genera cuadruplo de verificacion y da push a variables a utilizar para asignacion de arreglo
#Parametros: char *id
#Salida: void
**/
void insert_arr_index_to_StackO(char *id) {
    if(id != NULL){     // Control de entrada. Al final de funciones entra el id como nulo, lo omite.
        int array_index, array_base_address, array_translation;
        array_index = g_queue_pop_tail(StackO);  // Saca de la pila de operandos la variable temporal que guarda exp
        g_queue_push_tail(StackDimensions, (gpointer)get_var_virtual_address(id)); // Mete id a sacar a la hora de impresion
        insert_quadruple_to_array(VER, array_index, 0, get_var_dimension(id)); // cuadruplo de verificacion | * * linf lsup
        array_function_dimension = array_index;
        // Mete a pila de StackO la dir del arreglo en su pos inicial
        g_queue_push_tail(StackO, (gpointer)array_index);           // Mete direccion que guarda la posicion del arr a indexar
        //g_queue_push_tail(StackTypes, (gpointer)get_var_type(id));  // Mete el tipo para que no haya conflicto al generar quads.
        g_queue_push_tail(StackDimensions, (gpointer)get_var_virtual_address(id)); // Mete id a sacar a la hora de impresion
    }
}

// Genera el segundo cuadruplo de verificacion para una matriz y da push a variables a utilizar para la asignacion
void insert_arr2_index_to_StackO(char *id) {
    if(id != NULL){     // Control de entrada. Al final de funciones entra el id como nulo, lo omite.
        int array_index, array_base_address, array_translation;
        array_index = g_queue_pop_tail(StackO);  // Saca de la pila de operandos la variable temporal que guarda exp

        insert_quadruple_to_array(VER, array_index, 0, get_mat_dimension(id)); // cuadruplo de verificacion2 | * * linf lsup
        insert_quadruple_to_array(TIMES, array_function_dimension, get_mat_dimension(id)+1, temp_integers_count); // funcion de despl.
        insert_quadruple_to_array(PLUS, array_index, temp_integers_count, temp_integers_count+1); // acumula desplazamientos de ambas dimensiones
        // Mete a pila de StackO la dir del arreglo en su pos inicial 
        temp_integers_count++;       
        g_queue_push_tail(StackO, (gpointer)temp_integers_count);   // Mete direccion que guarda el desplazamiento de la matriz
        //g_queue_push_tail(StackTypes, (gpointer)"integer");  // Mete el tipo para que no haya conflicto al generar quads.
        g_queue_push_tail(StackDimensions, (gpointer)get_var_virtual_address(id)); // Mete id a sacar a la hora de impresion
        array_function_dimension = 0;
    }
}

// Genera el desplazamiento al tener el corrimiento de los arreglos
void insert_movement_quadruple(char *id){
    insert_quadruple_to_array(501, get_var_virtual_address(id), g_queue_pop_tail(StackO), ++temp_integers_count);
    g_queue_push_tail(StackO, (gpointer)(temp_integers_count*-1));   // Mete direccion que guarda el desplazamiento de la matriz
    g_queue_push_tail(StackTypes, (gpointer)"integer");  // Mete el tipo para que no haya conflicto al generar quads.
    temp_integers_count++;
}

/**
#Nombre: insert_cte_int_to_StackO
#Descripcion: Inserta una constante entera a la pila de operandos
#Parametros: int cte
#Salida: void
**/
void insert_cte_int_to_StackO(int cte){
//    if(cte != NULL){ 
        char *cte_integer = (char *)malloc(sizeof(int));
        sprintf (cte_integer, "%d", cte);
        vars_memory *temp_memory = g_slice_new(vars_memory);
        if (g_hash_table_lookup(constants_table, (gpointer)cte_integer) != NULL) { // ya existe la constante
            temp_memory = g_hash_table_lookup(constants_table, (gpointer)cte_integer);
        } else {
            temp_memory->type = "integer";
            temp_memory->virtual_address = const_integers_count;
            g_hash_table_insert(constants_table, (gpointer)cte_integer, (gpointer)temp_memory);
        }
        g_queue_push_tail(StackO, (gpointer)temp_memory->virtual_address);
        g_queue_push_tail(StackTypes, (gpointer)"integer"); 
        const_integers_count = const_integers_count + 1;    
//    }        
}

/**
#Nombre: insert_arr_decimal_to_StackO
#Descripcion: Inserta una constante decimal a la pila de operandos
#Parametros: float cte
#Salida: void
**/
void insert_cte_decimal_to_StackO(float cte){
//    if(cte != NULL){ 
        char *cte_decimal = (char *)malloc(sizeof(float));
        sprintf (cte_decimal, "%f", cte);
        vars_memory *temp_memory = g_slice_new(vars_memory);
        if (g_hash_table_lookup(constants_table, (gpointer)cte_decimal) != NULL) { // ya existe la constante
            temp_memory = g_hash_table_lookup(constants_table, (gpointer)cte_decimal);
        } else {
            temp_memory->type = "decimal";
            temp_memory->virtual_address = const_decimals_count;
            g_hash_table_insert(constants_table, (gpointer)cte_decimal, (gpointer)temp_memory);
        }
        g_queue_push_tail(StackO, (gpointer)temp_memory->virtual_address);
        g_queue_push_tail(StackTypes, (gpointer)"decimal"); 
        const_decimals_count = const_decimals_count + 1;    
    }      
//}

/**
#Nombre: insert_arr_string_to_StackO
#Descripcion: Inserta una constante string a la pila de operandos
#Parametros: char *cte_string
#Salida: void
**/
void insert_cte_string_to_StackO(char *cte_string){
//    if(c_string != NULL){
        printf("%s\n", cte_string);
        vars_memory *temp_memory = g_slice_new(vars_memory);
        if (g_hash_table_lookup(constants_table, (gpointer)cte_string) != NULL) { // ya existe la constante
            temp_memory = g_hash_table_lookup(constants_table, (gpointer)cte_string);
        } else {
            temp_memory->type = "string";
            temp_memory->virtual_address = const_strings_count;
            g_hash_table_insert(constants_table, (gpointer)cte_string, (gpointer)temp_memory);
        }
        g_queue_push_tail(StackO, (gpointer)temp_memory->virtual_address);
        g_queue_push_tail(StackTypes, (gpointer)"string"); 
        const_strings_count = const_strings_count + 1;    
//    }         
}

/**
#Nombre: insert_arr_string_to_StackO
#Descripcion: Inserta una constante string a la pila de operandos
#Parametros: char *cte_string
#Salida: void
**/
void insert_cte_boolean_to_StackO(char *cte_string){
//    if(c_string != NULL){
        vars_memory *temp_memory = g_slice_new(vars_memory);
        if (g_hash_table_lookup(constants_table, (gpointer)cte_string) != NULL) { // ya existe la constante
            temp_memory = g_hash_table_lookup(constants_table, (gpointer)cte_string);
        } else {
            temp_memory->type = "boolean";
            temp_memory->virtual_address = const_booleans_count;
            g_hash_table_insert(constants_table, (gpointer)cte_string, (gpointer)temp_memory);
        }
        g_queue_push_tail(StackO, (gpointer)temp_memory->virtual_address);
        g_queue_push_tail(StackTypes, (gpointer)"boolean"); 
        const_booleans_count = const_booleans_count + 1;    
//    }         
}

// Saca la expresion en pilas y verifica semantica con el parametro de la funcion
void params_semantic_validation(char *id, int counter){
    int param;
    if (g_hash_table_lookup(proc_table, (gpointer)id) != NULL) {
		type_table *temp_t_table = g_slice_new(type_table);
        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)id);
        char *method_var_type = g_queue_pop_head(temp_t_table->ParamsTypes);
        char *parameter_var_type = g_queue_pop_tail(StackTypes);
        if (strcmp(method_var_type, parameter_var_type) == 0) {
            param = g_queue_pop_tail(StackO);
            insert_quadruple_to_array(PARAM, param, 0, (counter+1));     // Genera cuadruplo para el parametro congruente
            g_queue_push_tail(temp_t_table->ParamsTypes, method_var_type);
        } else {
            printf("Error. Parametro mandado en funcion no es del mismo tipo\n");
            exit(0);
        }
    } else {
        printf("Error. Procedimiento no existe\n");
        exit(0);
    }
}

// Verifica que el numero de parametros en la funcion sean los mismos al llamado
void check_params_number(char *id, int params){
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)id);
    int method_params = temp_t_table->params_declared;
    if (method_params != params){   // Si el numero de parametros no son los mismos, truena.
        printf("Numero de parametros no coincide con el llamado\n");
        exit(0);
    }
}

// Genera cuadruplo GoSub para ir a la direccion de inicio de un procedimiento
void generate_gosub(char *id){
    type_table *temp_t_table = g_slice_new(type_table);
    temp_t_table = g_hash_table_lookup(proc_table, (gpointer)id);
    int beginning_address = temp_t_table->beginning_address;    // Direccion en la que empieza el procedimiento ID
    insert_quadruple_to_array(GOSUB, beginning_address, 0, 0);
}

/**
#Nombre: insert_to_StackOper
#Descripcion: Inserta operador en pila de operadores para la jerarquía de operaciones
#Parametros: int oper
#Salida: void
**/
void insert_to_StackOper(int oper){
    g_queue_push_tail(StackOper, (gpointer)oper);
}

/**
#Nombre: remove_from_StackOper
#Descripcion: Saca el operador de fondo falso al terminar un parentesis en expresion
#Parametros: -
#Salida: void
**/
void remove_from_StackOper(){
    g_queue_pop_tail(StackOper);
}

// Saca el arreglo o matriz que se guardo en el Stack de dimensiones
void remove_from_StackDimensions(){
    g_queue_clear(StackDimensions);
}

/**
#Nombre: remove_from_StackO
#Descripcion: Saca el id de la pila de operandos en caso de que en la definicion no se le asigne un valor
#Parametros: -
#Salida: void
**/
void remove_from_StackO(){
    g_queue_pop_tail(StackO);
}

/**
#Nombre: generate_add_sust_quadruple
#Descripcion: Agrega a la pila de operadores la suma o resta segun corresponda
#Parametros: -
#Salida: void
**/
void generate_add_sust_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == PLUS || (int)g_queue_peek_tail(StackOper) == MINUS) // '+' o '-'
        generate_exp_quadruples();
}

/**
#Nombre: generate_exp_quadruples
#Descripcion: Agrega a la pila de operadores la multiplicacion o division segun corresponda
#Parametros: -
#Salida: void
**/
void generate_mult_div_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == TIMES || (int)g_queue_peek_tail(StackOper) == DIV) // '*' o '/'
        generate_exp_quadruples();
}

/**
#Nombre: generate_exponential_quadruple
#Descripcion: Agrega a la pila de operadores el exponencial
#Parametros: -
#Salida: void
**/
void generate_exponential_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == EXP) // '^'
        generate_exp_quadruples();
}

/**
#Nombre: generate_relational_quadruple
#Descripcion: Agrega a la pila de operadores la el operador relacional segun corresponda 'and', 'or', '<', '>', '!', <>, >=, <= 
#Parametros: -
#Salida: void
**/
void generate_relational_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == AND || (int)g_queue_peek_tail(StackOper) == OR ||
        (int)g_queue_peek_tail(StackOper) == LT || (int)g_queue_peek_tail(StackOper) == GT ||
        (int)g_queue_peek_tail(StackOper) == 33 || (int)g_queue_peek_tail(StackOper) == DIFF ||
		(int)g_queue_peek_tail(StackOper) == G_EQUAL_T || (int)g_queue_peek_tail(StackOper) == L_EQUAL_T ||
        (int)g_queue_peek_tail(StackOper) == SAME)        
        generate_exp_quadruples();
}

/**
#Nombre: generate_gotoF_if_quadruple
#Descripcion: Funcion para la generacion de un gotoF para el estatuto if
#Parametros: -
#Salida: void
**/
void generate_gotoF_if_quadruple(){
	char *aux = g_queue_pop_tail(StackTypes);
	int result;
	if(strcmp(aux, "boolean") != 0){
		printf("error semantico, operador logico faltante\n");
		exit(0);
	}else{
	    result = g_queue_pop_tail(StackO);
		insert_quadruple_to_array(GOTOF, result, 0, 0);
		g_queue_push_tail(StackJumps, (gpointer)(quadruple_index - 1));    

	}
}

/**
#Nombre: generate_goto_if_quadruple
#Descripcion: Funcion para la generacion de un goto para el estatuto if
#Parametros: -
#Salida: void
**/
void generate_goto_if_quadruple(){
	insert_quadruple_to_array(GOTO, 0, 0, 0);
	fill_if();
	g_queue_push_tail(StackJumps, (gpointer)(quadruple_index - 1));
}

/**
#Nombre: fill_if
#Descripcion: Funcion para el rellenado de saltos del estatuto if (goto - gotoF)
#Parametros: -
#Salida: void
**/
void fill_if(){
	int temp_count;
	char *t_count = (char *)malloc(sizeof(int));
	temp_count = g_queue_pop_tail(StackJumps);
	quad_struct *t_quadruple = g_slice_new(quad_struct);
	sprintf(t_count, "%d", (quadruple_index + 1));
	t_quadruple = g_ptr_array_index(QuadruplesList,temp_count);
	t_quadruple->result = t_count;

}

// Rellena el primer cuadruplo con la direccion de la funcion main
void fill_goto_main(){
    quad_struct *qs = g_slice_new(quad_struct);
    qs = g_ptr_array_index(QuadruplesList, 0);
	char *ba = (char *)malloc(sizeof(int));
    sprintf (ba, "%d", (quadruple_index + 1));
    qs->result = ba;
}

/**
#Nombre: push_cont_to_stack_jumps
#Descripcion: Mete a pila de saltos el cuadruplo al que saltara (para seguir haciendo el ciclo) y rellenar con el salto de direccion
			  Guarda a posicion del cuadruplo al cual ira Goto - Mantiene ciclo vivo
#Parametros: -
#Salida: void
**/
void push_cont_to_stack_jumps(){
	g_queue_push_tail(StackJumps, (gpointer)(quadruple_index + 1));
}

/**
#Nombre: generate_for_limit_quadruple
#Descripcion: Genera el cuadruplo para el maximo de saltos del estatuto for
#Parametros: -
#Salida: void
**/
void generate_for_limit_quadruple(){
    int exp_address, id;
    id = g_queue_pop_tail(StackO);
    exp_address = g_queue_pop_tail(StackO);
    insert_quadruple_to_array(L_EQUAL_T, id, exp_address, const_booleans_count);   // Guardamos en constantes booleanas
    g_queue_push_tail(StackO, (gpointer)id);                                // ya que la comparacion devolvera un boolean
    g_queue_push_tail(StackO, (gpointer)const_booleans_count);              // Se agrega resultado y su tipo a las pilas
    const_booleans_count = const_booleans_count + 1;                        
}

/**
#Nombre: generate_step_for_quadruple
#Descripcion: Genera el cuadruplo para los 'pasos' a dar por cada vuelta que el for da
#Parametros: -
#Salida: void
**/
void generate_step_for_quadruple(){
    int exp_address, id;
    id = g_queue_pop_tail(StackO);
    exp_address = g_queue_pop_tail(StackO);
    step_struct = g_slice_new(quad_struct);

	char *c_operator = (char *)malloc(sizeof(int));
	char *c_first_oper = (char *)malloc(sizeof(int));
	char *c_second_oper = (char *)malloc(sizeof(int));
    sprintf (c_operator, "%d", STEP);
	sprintf (c_first_oper, "%d", id);
	sprintf (c_second_oper, "%d", exp_address);  

    step_struct->operator=c_operator;
    step_struct->first_oper=c_second_oper;
    step_struct->second_oper=c_first_oper;
    step_struct->result=c_first_oper;
    
    g_queue_push_tail(StackSteps, (gpointer)step_struct);
}

/**
#Nombre: generate_gotoF_for_quadruple
#Descripcion: Genera el cuadruplo para el gotoF del estatuto for
#Parametros: -
#Salida: void
**/
void generate_gotoF_for_quadruple(){
	int result;
    result = g_queue_pop_tail(StackO);
    insert_quadruple_to_array(GOTOF, result, 0, 0); //GOTOF
    g_queue_push_tail(StackJumps, (gpointer)(quadruple_index - 1)); // Guarda la posicion del cuadruplo al cual ira GotoF
}

/**
#Nombre: generate_while_gotoF_quadruple
#Descripcion: Genera el cuadruplo para el gotoF del estatuo while
#Parametros: -
#Salida: void
**/
void generate_while_gotoF_quadruple() {
	int temp_count;
	int result;
	char *t_count = (char *)malloc(sizeof(int));
	char *aux = g_queue_pop_tail(StackTypes);
	
	if(strcmp(aux, "boolean") != 0) {
		printf("error semantico, operador logico faltante\n");
		exit(0);
	}else{
		result = g_queue_pop_tail(StackO);
		insert_quadruple_to_array(GOTOF, result, 0, 0); //GOTOF
		g_queue_push_tail(StackJumps, (gpointer)(quadruple_index - 1)); // Guarda la posicion del cuadruplo al cual ira GotoF
	}
	
}

/**
#Nombre: fill_step
#Descripcion: Rellena el numero de saltos para los 'pasos' del estatuto for por cada vuelta
#Parametros: -
#Salida: void
**/
void fill_step(){
    quad_struct *qs = g_queue_pop_tail(StackSteps);
    g_ptr_array_add(QuadruplesList, (gpointer)qs);     // Agrega estructura para el step
    ++quadruple_index;  // Necesario incrementar despues de haber insertado una estructura
}

/**
#Nombre: fill_for
#Descripcion: Genera direccion a ir del gotoF y genera cuadruplo para goto
#Parametros: -
#Salida: void
**/
void fill_for(int step){
    int __return, id;
	int __false;
	char *t_return = (char *)malloc(sizeof(int));
	char *t_false = (char *)malloc(sizeof(int));
	__false = g_queue_pop_tail(StackJumps);
	__return = g_queue_pop_tail(StackJumps);
    id = g_queue_pop_tail(StackO);
	sprintf(t_return, "%d", __return);
	insert_quadruple_to_array(GOTOFOR, 0, step, __return); //GOTOFOR con valor a agregar a result, es decir, step
	quad_struct *t_quadruple = g_slice_new(quad_struct);
	
	sprintf(t_false, "%d", (quadruple_index + 1));
	t_quadruple = g_ptr_array_index(QuadruplesList,__false);
	t_quadruple->result = t_false;
}

/**
#Nombre: fill_while
#Descripcion: Rellena el numero de saltos a dar para el estatuto while
#Parametros: -
#Salida: void
**/
void fill_while(){
	int __return;
	int __false;
	char *t_return = (char *)malloc(sizeof(int));
	char *t_false = (char *)malloc(sizeof(int));
	__false = g_queue_pop_tail(StackJumps);
	__return = g_queue_pop_tail(StackJumps);
	sprintf(t_return, "%d", __return);
	insert_quadruple_to_array(GOTO, 0, 0, __return); //GOTO
	quad_struct *t_quadruple = g_slice_new(quad_struct);
	
	sprintf(t_false, "%d", (quadruple_index + 1));
	t_quadruple = g_ptr_array_index(QuadruplesList,__false);
	t_quadruple->result = t_false;
}

/**
#Nombre: insert_quadruple_to_array
#Descripcion: Se inserta cuadruplo en forma de estructura en el arreglo de cuadruplos, para su impresion posterior al archivo
#Parametros: -
#Salida: void
**/
void insert_quadruple_to_array(int operator, int second_oper, int first_oper, int *count){
	quad_struct *quadruple = g_slice_new(quad_struct);
	char *c_operator = (char *)malloc(sizeof(int));
	char *c_second_oper = (char *)malloc(sizeof(int));
	char *c_first_oper = (char *)malloc(sizeof(int));
	char *c_count = (char *)malloc(sizeof(int));
    sprintf (c_operator, "%d", operator);
	sprintf (c_second_oper, "%d", second_oper);
	sprintf (c_first_oper, "%d", first_oper);
	sprintf (c_count, "%d", count);

	quadruple->operator = c_operator;
	quadruple->first_oper = c_first_oper;
	quadruple->second_oper = c_second_oper;
	quadruple->result = c_count;
	g_ptr_array_add(QuadruplesList, (gpointer)quadruple); 
    ++quadruple_index;  // Incrementa en 1 el contador de cuadruplos para control interno en compilación
}

// Funcion que genera los cuadruplos para las expresiones
/**
#Nombre: insert_quadruple_to_array
#Descripcion: Genera los cuadruplos de las expresiones
#Parametros: -
#Salida: void
**/
void generate_exp_quadruples(){
    char *first_type, *second_type;  // Top y Top-1 de la pila de tipos
    char *temp_type;                 // Tipo de dato de la variable temporal
    int *temp_count;
    int first_oper, second_oper, operator, valid_type;

    operator = (int)g_queue_pop_tail(StackOper);    // Saca primer operador de la pila de operadores
    first_oper = g_queue_pop_tail(StackO);          // Solo sacamos el primer_oper en caso de que sea math_function
	
    if (operator == INDEX) {      // Si llega index de arreglos, mete para generar verificacion y meter desplazamiento
        g_queue_push_tail(StackO, first_oper);  
    } else if (operator == ABS || operator == COS || operator == SIN || // 'as' 'cs' 'sn'    // Generacion de Math_function
        operator == LOG || operator == TAN || operator == SQRT) { // 'lg' 'tn' 'st'
		insert_quadruple_to_array(operator, first_oper, 0, temp_decimals_count);
        g_queue_push_tail(StackO, (gpointer)temp_decimals_count);   // Se da push al temp que guarda el valor de la fn
        g_queue_push_tail(StackTypes, (gpointer)"decimal");         // Se da push al tipo decimal que sera igual para todos
        temp_decimals_count = temp_decimals_count + 1;              // Se incrementa en uno el temp de decimales
    } else if (operator == PRINT || operator == PRINTLINE || operator == READINT || operator == READLINE) {  
        //default_functions     
        insert_quadruple_to_array(operator, first_oper, 0, 0); // El pop es 0 cuando no es arr
        g_queue_push_tail(StackOper, (gpointer)operator);
    } else {    // Genera cuadruplos para asignacion o el resto de tipo de cuadruplos (que no son math_functions)
        second_oper = g_queue_pop_tail(StackO);         // Saca el siguiente operando para hacer las operaciones
        first_type = g_queue_pop_tail(StackTypes);      // Saca primer operando
        second_type = g_queue_pop_tail(StackTypes);     // Saca siguiente operando
        valid_type = valid_var_types(first_type, second_type); // Obtiene el tipo de valor al cual se casteara la operacion
        if (valid_type != 0){ // Si es valido, se genera el cuadruplo
			// if(operator == RETURN){
			// 			printf("EDOOOOO\n");
			// 			insert_quadruple_to_array(RETURN, first_oper, 0, second_oper);
			// 			g_queue_clear(StackOper);
			// 			g_queue_clear(StackO);
			// 		}
            if (operator == EQUALS) { // || operator == 65) {   // '='  Igual para math_choices.
				insert_quadruple_to_array(operator, second_oper, 0, first_oper);
            //} else if (operator == ARRAY) { // En caso de ser un arreglo, la asignacion es a un temp o a lo que se asigne
            //    if (g_queue_peek_tail(StackOper) == 0) {   
            //        printf("ARRAY: %d\n", g_queue_peek_tail(StackO));             
            //        insert_quadruple_to_array(operator, g_queue_pop_tail(StackDimensions), second_oper, first_oper);
            //    }
            } else {    // Asigna el tipo de dato a la variable que guardara el resultado de la operacion
                if (valid_type == 1) { temp_count = &temp_integers_count; temp_type = "integer"; }
                if (valid_type == 2) { temp_count = &temp_strings_count; temp_type = "string"; }
                if (valid_type == 3) { temp_count = &temp_booleans_count; temp_type = "boolean"; }
                if (valid_type == 4) { temp_count = &temp_decimals_count; temp_type = "decimal"; }
				insert_quadruple_to_array(operator, second_oper, first_oper, *temp_count);
                // Mete el temporal a la pila para incluirse en las operaciones
                g_queue_push_tail(StackO, (gpointer)*temp_count);  
                g_queue_push_tail(StackTypes, (gpointer)temp_type);
				//Si es un operador logico, mete un tipo booleano a la pila de tipos
				if(operator == LT || operator == GT || operator == G_EQUAL_T ||
                   operator == L_EQUAL_T || operator == SAME || operator == DIFF ||
                   operator == AND || operator == OR) {
					g_queue_push_tail(StackTypes, (gpointer)"boolean");
                    g_queue_push_tail(StackTypes, (gpointer)"boolean");
				}
                *temp_count = *temp_count + 1;
            }   
        } else { // Error semantico, tipos incompatibles (var_type == 0)
            printf("Error al hacer la operacion entre los tipos de dato\n");
            exit(0);
        }
    }
}


/*
Bloque de impresión
*/

/**
#Nombre: print_hash
#Descripcion: Imprime los valores de la tabla de hashing
#Parametros: char *key, type_table *value, gpointer user_data
#Salida: void
#Dependencias: print_has_table
**/
static void print_hash(char *key, type_table *value, gpointer user_data){
	printf("%s : %s\n", key, value->method_type);
}

/**
#Nombre: print_hash_table
#Descripcion: Manda llamar la funcion print_has para imprimir la tabla de hashing
#Parametros: -
#Salida: void
**/
void print_hash_table(){
	g_hash_table_foreach(proc_table, (GHFunc)print_hash, NULL);
}

/**
#Nombre: print_constants
#Descripcion: Imprime la tabla de constantes al archivo de codigo objeto
#Parametros: char *key, vars_memory *value, gpointer user_data
#Salida: void
#Dependencias: print_constants_table
**/
static void print_constants(char *key, vars_memory *value, gpointer user_data){
	if (middle_code = fopen("tlaloc.txt", "a+")){
		fprintf(middle_code, "%s\t%s\t%d\n", key, value->type, value->virtual_address);
		fclose(middle_code);
	}else{
		printf("Error al abrir tlaloc.txt\n");
        exit(0);
	}
}

/**
#Nombre: print_constants_table
#Descripcion: Manda llamar la funcion print_constants para imprimir la tabla de constantes
#Parametros: -
#Salida: void
**/
void print_constants_table(){
	g_hash_table_foreach(constants_table, (GHFunc)print_constants, NULL);
}

/**
#Nombre: print_hash_var_table
#Descripcion: Imprime los valores de la tabla de hashing de variables
#Parametros: char *key, vars_memory *value, gpointer user_data
#Salida: void
#Dependencias: print_var_table
**/
void print_hash_var_table(char *key, vars_memory *value, gpointer user_data){
	printf("\t%s : %s : %d : %d : %d\n", key, value->type, value->virtual_address, value->var_dimension, value->mat_dimension);
}

/**
#Nombre: print_var_table
#Descripcion: Manda llamar la funcion print_hash_var_table que imprime la tabla de hashing de variables
#Parametros: char *key, vars_memory *value, gpointer user_data
#Salida: void
**/
void print_var_table(char *function){
	printf("%s\n", function);
	type_table *temp_t_table = g_slice_new(type_table);
	temp_t_table = g_hash_table_lookup(proc_table, (gpointer)function);
    printf("Locales: %d\t Params: %d\n", temp_t_table->local_vars_declared, temp_t_table->params_declared);
    printf("\nVariables locales:\n");
	g_hash_table_foreach(temp_t_table->h_table, (GHFunc)print_hash_var_table, NULL);
    printf("\nParametros:\n");
    g_hash_table_foreach(temp_t_table->params_table, (GHFunc)print_hash_var_table, NULL);
}

/**
#Nombre: print_array
#Descripcion: Imprime el arreglo de los cuadruplos en el archivo objeto
#Parametros: quad_struct *quadruple, gpointer user_data
#Salida: void
**/
static void print_array(quad_struct *quadruple, gpointer user_data){
	
	if (middle_code = fopen("tlaloc.txt", "a+")){
		fprintf(middle_code, "%s\t%s\t%s\t%s\n", quadruple->operator, quadruple->second_oper, quadruple->first_oper, quadruple->result);
		fclose(middle_code);
	}else{
		printf("Error al abrir tlaloc.txt\n");
        exit(0);
	}
}

void print_globals(char *key, vars_memory *value, gpointer user_data){
	if (middle_code = fopen("tlaloc.txt", "a+")){
		fprintf(middle_code, "%s\t%s\t%d\n", key, value->type, value->virtual_address);
		fclose(middle_code);
	}else{
		printf("Error al abrir tlaloc.txt\n");
        exit(0);
	}
}


void print_globals_to_file(){
    type_table *temp_t_table = g_slice_new(type_table);
	temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
    
    g_hash_table_foreach(temp_t_table->h_table, (GHFunc)print_globals, NULL);

}

/**
#Nombre: print_to_file
#Descripcion: Manda llamar las funciones para imprimir tanto en consola como archivo objeto 
#Parametros: -
#Salida: void
#Dependencias: print_array, print_constants_table
**/
void print_to_file(){
	printf("---\n");
    middle_code = fopen("tlaloc.txt", "w"); // Abrimos el archivo en modo de escritura
    fclose(middle_code);                    // Cerramos el archivo inmediatamente para borrar su contenido    
    print_globals_to_file();
    middle_code = fopen("tlaloc.txt", "a+");
	fprintf(middle_code, "$$$\n");
	fclose(middle_code);
    print_constants_table();
	middle_code = fopen("tlaloc.txt", "a+");
	fprintf(middle_code, "$\n");
	fclose(middle_code);	
    g_ptr_array_foreach(QuadruplesList, (GFunc)print_array, NULL);
	middle_code = fopen("tlaloc.txt", "a+");
	fprintf(middle_code, "$$");
	fclose(middle_code);
	printf("END\n");
}
