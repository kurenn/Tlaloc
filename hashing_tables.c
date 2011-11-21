#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum symbols {PRINT=213, PRINTLINE=228, READINT=215, READLINE=216, RETURN=224, AND=197, OR=198, ABS=212, COS=214, SIN=225,
	 		  LOG=211, TAN=226, SQRT=231, RET=166, __TRUE=217, __FALSE=203, GOTOF=205, GOTO=206,
	 		  EQUALS=61, SAME=122, LT=60, GT=62, DIFF=123, TIMES=42, PLUS=43, MINUS=45, DIV=47, EXP=94, VER=100,
	  		  POINTER=107, G_EQUAL_T=124, L_EQUAL_T=125, OPEN_BRACKET=91, GOTOWHILE=207, GOTOFOR=208, STEP=666, INDEX=500, ARRAY=501};

static GHashTable *proc_table; // HashTable de procedimientos (key) leidos. (value) apunta a type_table
static GHashTable *constants_table;  //HashTable con las constantes usadas en todo el programa
static GQueue *StackO;
static GQueue *StackOper;
static GQueue *StackTypes;
static GQueue *Quadruples;
static GQueue *StackJumps; 
static GQueue *StackSteps;     // Pila para el control de steps en fors
char *current_function;        // Variable que mantiene el nombre de la funcion actual
char *global_function;         // Variable que mantiene el nombre del programa
int quadruple_index = 0;       // Contador de cuadruplos
FILE *middle_code;			   //Archivo de cuadruplos
static GPtrArray *QuadruplesList; //lista de cuadruplos

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
	GHashTable *h_table;        // Tabla de variables del metodo
}type_table;

// vars_memory: almacena el tipo de dato de la variable y su direccion virtual. 
// Key de la hash table que apunta type_table
typedef struct {
    char *type;
    int virtual_address;
    int var_dimension;
}vars_memory;

//Estructura para la insercion del cuadruplo en el arreglo de apuntadores
typedef struct {
	char* operator;
	char* first_oper;
	char* second_oper;
	char* result;
}quad_struct;

quad_struct *step_struct;   // Estructura que almacena la exp step del for para agregarla al final de los cuadruplos

// Inicializa tabla de procedimientos
void create_proc_table(){
	proc_table = g_hash_table_new(g_str_hash, g_str_equal); 
}

// Inicializa tabla de constantes del programa
void create_constants_table(){
	constants_table = g_hash_table_new(g_str_hash, g_str_equal); // key: constante | value: vars_memory(struct)
}

void create_quadruples_array(){
	QuadruplesList = g_ptr_array_new();
	
}

// Tabla de validacion de tipos de datos
// Opcion es 0 con tipos incompatibles. Opcion es 1 por default ya que los demas son validos. 
int valid_var_types(char *first_type, char *second_type){
    int option;
    //printf("Entre valido, %s, %s\n", first_type, second_type);
    if (strcmp(first_type,"integer") == 0 && strcmp(second_type,"boolean") == 0
        || strcmp(first_type,"string") == 0 && strcmp(second_type,"boolean") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"decimal") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"integer") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"string") == 0
        || strcmp(first_type,"decimal") == 0 && strcmp(second_type,"boolean") == 0) // Combinaciones invalidas
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
        || strcmp(first_type,"decimal") == 0 && strcmp(second_type,"decimal") == 0) // Combinaciones invalidas
        option = 4;
    else if (strcmp(first_type,"boolean") == 0 && strcmp(second_type,"boolean") == 0) // Combinaciones invalidas
        option = 3;
    
    return option;
}

// Inicializa filas y pilas
void create_stacks_and_queues(){
	StackO = g_queue_new(); 
    StackOper = g_queue_new(); 
    StackTypes = g_queue_new(); 
    Quadruples = g_queue_new(); 
	StackJumps = g_queue_new();
    StackSteps = g_queue_new();
}

// Inicializa variables temporales para operaciones dentro de cada funcion
void reset_temp_vars(){
    temp_integers_count = TINTEGERS, temp_strings_count = TSTRINGS,
    temp_booleans_count = TBOOLEANS, temp_decimals_count = TDECIMALS;
}

// Inicializa variables locales a 0 para cada nuevo procedimiento
void reset_memory_counters(){
    local_integers_count = 0, local_strings_count = 0,
    local_booleans_count = 0, local_decimals_count = 0;
}

// get_var_virtual_address: devuelve direccion virtual de una variable (id) que viene de sintaxis
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

// get_var_type: devuelve tipo de dato de una variable (id) que viene de sintaxis
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

// get_var_dimension: devuelve la dimension de una variable que es arreglo
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

// set_var_dimension: asigna la dimension que le corresponde al arreglo (o ID)
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

/*
@Method - insert_proc_to_table
@Type - void
@params - char *proc, char *tipo
*/
void insert_proc_to_table(char *proc, char *tipo){
	if (g_hash_table_lookup(proc_table, (gpointer)proc) != NULL){
		printf("El metodo '%s' ya esta dado de alta\n", proc);
		exit(0);
	} else {
		type_table *t_table = g_slice_new(type_table); //Creamos tabla de hashing para los tipos 1x2
		t_table->method_type = tipo;
		t_table->h_table = g_hash_table_new(g_str_hash, g_str_equal); //Tabla de variables inicializada
		g_hash_table_insert(proc_table, (gpointer)proc, (gpointer)t_table);
		current_function = proc;
        reset_memory_counters();    // Reinicia contadores locales de memoria a 0 para nueva metodo
        if (strcmp(tipo, "global") == 0) {
            global_function = proc;
        }
	}
}


/*
@Method - insert_vars_to_proc_table
@Type - void
@params - char *proc, char *tipo
*/
void insert_vars_to_proc_table(char *var, char *tipo, int dimension){
	 if (g_hash_table_lookup(proc_table, (gpointer)current_function) != NULL) {
		type_table *temp_t_table = g_slice_new(type_table);

        temp_t_table = g_hash_table_lookup(proc_table, (gpointer)global_function);
        if (g_hash_table_lookup(temp_t_table->h_table, (gpointer)var) != NULL) {
			printf("La variable '%s' ya esta declarada como global\n", var);
			exit(0);
        }
		temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
        if (g_hash_table_lookup(temp_t_table->h_table, (gpointer)var) != NULL) {
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
                //v_memory->var_dimension = dimension;
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
                //v_memory->var_dimension = dimension;
            }     
            g_hash_table_insert(temp_t_table->h_table, (gpointer)var, (gpointer)v_memory);
        }
    } else {
        printf("Error. Procedimiento no existe\n");
    }
}


/* Bloque para agregar constantes
    Agrega todas las constantes que encuentra en expresiones a la HashTable de constantes.
    Si la variable ya existe, toma la direccion que ya le fue asignadas
*/
void insert_id_to_StackO(char *id){
    if(id != NULL){     // Control de entrada. Al final de funciones entra el id como nulo, lo omite.
        g_queue_push_tail(StackO, (gpointer)get_var_virtual_address(id));
        g_queue_push_tail(StackTypes, (gpointer)get_var_type(id)); 
    }        
}

// Genera cuadruplo de verificacion y da push a variables a utilizar para asignacion de arreglo
void insert_arr_index_to_StackO(char *id) {
    if(id != NULL){     // Control de entrada. Al final de funciones entra el id como nulo, lo omite.
        int array_index, array_base_address, array_translation;
        array_index = g_queue_pop_tail(StackO);  // Saca de la pila de operandos la variable temporal que guarda exp

        insert_quadruple_to_array(VER, array_index, 0, get_var_dimension(id)); // cuadruplo de verificacion | * * linf lsup

        // Mete a pila de StackO la dir del arreglo en su pos inicial
        g_queue_push_tail(StackO, (gpointer)array_index);           // Mete direccion que guarda la posicion del arr a indexar
        g_queue_push_tail(StackTypes, (gpointer)get_var_type(id));  // Mete el tipo para que no haya conflicto al generar quads.
    }
}

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

// Inserta operador en pila de operadores para la jerarquía de operaciones
void insert_to_StackOper(int oper){
    g_queue_push_tail(StackOper, (gpointer)oper);
}

// Saca el operador de fondo falso al terminar un parentesis en expresion
void remove_from_StackOper(){
    g_queue_pop_tail(StackOper);
}

// Saca el id de la pila de operandos en caso de que en la definicion no se le asigne un valor
void remove_from_StackO(){
    g_queue_pop_tail(StackO);
}

/* Bloque de validación jerarquico
    Verifica los operadores en la pila de tipos para aplicar su jerarquia
 */
void generate_add_sust_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == PLUS || (int)g_queue_peek_tail(StackOper) == MINUS) // '+' o '-'
        generate_exp_quadruples();
}

void generate_mult_div_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == TIMES || (int)g_queue_peek_tail(StackOper) == DIV) // '*' o '/'
        generate_exp_quadruples();
}

void generate_exponential_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == EXP) // '^'
        generate_exp_quadruples();
}

void generate_relational_quadruple() {
    if ((int)g_queue_peek_tail(StackOper) == AND || (int)g_queue_peek_tail(StackOper) == OR ||
        (int)g_queue_peek_tail(StackOper) == LT || (int)g_queue_peek_tail(StackOper) == GT ||
        (int)g_queue_peek_tail(StackOper) == 33 || (int)g_queue_peek_tail(StackOper) == DIFF ||
		(int)g_queue_peek_tail(StackOper) == G_EQUAL_T || (int)g_queue_peek_tail(StackOper) == L_EQUAL_T) // 'ad', 'or', '<', '>', '!', <>, >=, <=        
        generate_exp_quadruples();
}

//Funcion para la generacion de cuadruplos para IF
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

void generate_goto_if_quadruple(){
	insert_quadruple_to_array(GOTO, 0, 0, 0);
	fill_if();
	g_queue_push_tail(StackJumps, (gpointer)(quadruple_index - 1));
}

void fill_if() {
	int temp_count;
	char *t_count = (char *)malloc(sizeof(int));
	temp_count = g_queue_pop_tail(StackJumps);
	quad_struct *t_quadruple = g_slice_new(quad_struct);
	sprintf(t_count, "%d", (quadruple_index + 1));
	t_quadruple = g_ptr_array_index(QuadruplesList,temp_count);
	t_quadruple->result = t_count;

}

// Mete a pila de saltos el cuadruplo al que saltara (para seguir haciendo el ciclo) y rellenar con el salto de direccion
void push_cont_to_stack_jumps(){
	g_queue_push_tail(StackJumps, (gpointer)(quadruple_index + 1)); // Guarda a posicion del cuadruplo al cual ira Goto - Mantiene ciclo vivo
}

void generate_for_limit_quadruple(){
    int exp_address, id;
    id = g_queue_pop_tail(StackO);
    exp_address = g_queue_pop_tail(StackO);
    insert_quadruple_to_array(L_EQUAL_T, id, exp_address, const_booleans_count);   // Guardamos en constantes booleanas
    g_queue_push_tail(StackO, (gpointer)id);                                // ya que la comparacion devolvera un boolean
    g_queue_push_tail(StackO, (gpointer)const_booleans_count);              // Se agrega resultado y su tipo a las pilas
    const_booleans_count = const_booleans_count + 1;                        
}

void generate_step_for_quadruple(){
    int exp_address, id;
    id = g_queue_pop_tail(StackO);
    printf("ID: %d\n", id);
    exp_address = g_queue_pop_tail(StackO);
    printf("EXP: %d\n", exp_address);
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

void generate_gotoF_for_quadruple(){
	int result;
    result = g_queue_pop_tail(StackO);
    insert_quadruple_to_array(GOTOF, result, 0, 0); //GOTOF
    g_queue_push_tail(StackJumps, (gpointer)(quadruple_index - 1)); // Guarda la posicion del cuadruplo al cual ira GotoF
}

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

void fill_step(){
    quad_struct *qs = g_queue_pop_tail(StackSteps);
    g_ptr_array_add(QuadruplesList, (gpointer)qs);     // Agrega estructura para el step
    ++quadruple_index;  // Necesario incrementar despues de haber insertado una estructura
}

// Genera direccion a ir del gotoF y genera cuadruplo para goto
void fill_for(int step){
    int __return, id;
	int __false;
	char *t_return = (char *)malloc(sizeof(int));
	char *t_false = (char *)malloc(sizeof(int));
	__false = g_queue_pop_tail(StackJumps);
	__return = g_queue_pop_tail(StackJumps);
    id = g_queue_pop_tail(StackO);
	sprintf(t_return, "%d", __return);
	insert_quadruple_to_array(GOTOFOR, id, step, __return); //GOTOFOR con valor a agregar a result, es decir, step
	quad_struct *t_quadruple = g_slice_new(quad_struct);
	
	sprintf(t_false, "%d", (quadruple_index + 1));
	t_quadruple = g_ptr_array_index(QuadruplesList,__false);
	t_quadruple->result = t_false;
}

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

// Se inserta cuadruplo en forma de estructura en el arreglo de cuadruplos
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
    } else if (operator == PRINT || operator == PRINTLINE || operator == READINT || operator == READLINE) {  //default_functions
        insert_quadruple_to_array(operator, first_oper, g_queue_pop_tail(StackO), 0); // El pop es 0 para cuando no es arreglo     
        g_queue_push_tail(StackOper, (gpointer)operator);
    } else {    // Genera cuadruplos para asignacion o el resto de tipo de cuadruplos (que no son math_functions)
        second_oper = g_queue_pop_tail(StackO);         // Saca el siguiente operando para hacer las operaciones
        first_type = g_queue_pop_tail(StackTypes);      // Saca primer operando
        second_type = g_queue_pop_tail(StackTypes);     // Saca siguiente operando
        valid_type = valid_var_types(first_type, second_type); // Obtiene el tipo de valor al cual se casteara la operacion
        if (valid_type != 0){ // Si es valido, se genera el cuadruplo
            if (operator == EQUALS) { // || operator == 65) {   // '='  Igual para math_choices.
				insert_quadruple_to_array(operator, second_oper, 0, first_oper);
            } else if (operator == ARRAY) { // En caso de ser un arreglo, la asignacion es diferente
                insert_quadruple_to_array(operator, g_queue_pop_tail(StackO), second_oper, first_oper);
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
				if(operator == LT || operator == GT || operator == G_EQUAL_T || operator == L_EQUAL_T) {
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
static void print_hash(char *key, type_table *value, gpointer user_data){
	printf("%s : %s\n", key, value->method_type);
}

void print_hash_table(){
	g_hash_table_foreach(proc_table, (GHFunc)print_hash, NULL);
}

static void print_constants(char *key, vars_memory *value, gpointer user_data){
	if (middle_code = fopen("tlaloc.txt", "a+")){
		fprintf(middle_code, "%s\t%s\t%d\n", key, value->type, value->virtual_address);
		fclose(middle_code);
	}else{
		printf("Error al abrir tlaloc.txt\n");
	}
}

void print_constants_table(){
	g_hash_table_foreach(constants_table, (GHFunc)print_constants, NULL);
}

void print_hash_var_table(char *key, vars_memory *value, gpointer user_data){
	printf("\t%s : %s : %d : %d\n", key, value->type, value->virtual_address, value->var_dimension);
}

void print_var_table(char *function){
	printf("%s\n", function);
	type_table *temp_t_table = g_slice_new(type_table);
	temp_t_table = g_hash_table_lookup(proc_table, (gpointer)function);
	g_hash_table_foreach(temp_t_table->h_table, (GHFunc)print_hash_var_table, NULL);
}

static void print_array(quad_struct *quadruple, gpointer user_data){
	
	if (middle_code = fopen("tlaloc.txt", "a+")){
		fprintf(middle_code, "%s\t%s\t%s\t%s\n", quadruple->operator, quadruple->second_oper, quadruple->first_oper, quadruple->result);
		fclose(middle_code);
	}else{
		printf("Error al abrir tlaloc.txt\n");
	}
}

void print_to_file(){
	printf("---\n");
    middle_code = fopen("tlaloc.txt", "w"); // Abrimos el archivo en modo de escritura
    fclose(middle_code);                    // Cerramos el archivo inmediatamente para borrar su contenido
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
