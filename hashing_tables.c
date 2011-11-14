#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static GHashTable *proc_table; // HashTable de procedimientos (key) leidos. (value) apunta a type_table
static GQueue *StackO;
static GQueue *StackOper;
static GQueue *StackTypes;
static GQueue *Quadruples; 
char *current_function;        // Variable que mantiene el nombre de la funcion actual
char *global_function;         // Variable que mantiene el nombre del programa

// Contadores que controlan el incremento de las direcciones virtuales para las variables
int global_integers_count = 0, global_strings_count = 0,
    global_booleans_count = 0, global_decimals_count = 0, 
    local_integers_count = 0, local_strings_count = 0,
    local_booleans_count = 0, local_decimals_count = 0;

// Inicio de bloques de memoria para cada tipo de variables
enum memory_blocks {GINTEGERS=5000, GSTRINGS=10000, GBOOLEANS=15000, GDECIMALS=20000, 
                    LINTEGERS=25000, LSTRINGS=30000, LBOOLEANS=35000, LDECIMALS=40000 };

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
}vars_memory;

// Inicializa tabla de procedimientos
void create_proc_table(){
	proc_table = g_hash_table_new(g_str_hash, g_str_equal); 
}

// Tabla de validacion de tipos de datos
// Opcion es 0 con tipos incompatibles. Opcion es 1 por default ya que los demas son validos. 
int valid_var_types(char *first_type, char *second_type){
    int option = 1;
    if (strcmp(first_type,"integer") == 0 && strcmp(second_type,"boolean") == 0
        || strcmp(first_type,"string") == 0 && strcmp(second_type,"boolean") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"decimal") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"integer") == 0
        || strcmp(first_type,"boolean") == 0 && strcmp(second_type,"string") == 0
        || strcmp(first_type,"decimal") == 0 && strcmp(second_type,"boolean") == 0) // Combinaciones invalidas
        option = 0;
    
    return option;
}


// Inicializa filas y pilas
void create_stacks_and_queues(){
	StackO = g_queue_new(); 
    StackOper = g_queue_new(); 
    StackTypes = g_queue_new(); 
    Quadruples = g_queue_new(); 
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
                        local_decimals_count = local_decimals_count + 1 + dimension; ;                        
                }
                v_memory->virtual_address = address;
            }     
            g_hash_table_insert(temp_t_table->h_table, (gpointer)var, (gpointer)v_memory);
        }
    } else {
        printf("Error. Procedimiento no existe\n");
    }
}

void insert_to_StackO(char *id){
    if(id != NULL){     // Control de entrada. Al final de funciones entra el id como nulo, lo omite.
        g_queue_push_head(StackO, (gpointer)get_var_virtual_address(id));
        g_queue_push_head(StackTypes, (gpointer)get_var_type(id)); 
    }        
}

void insert_to_StackOper(int oper){
    printf("%c\n", oper);
    g_queue_push_head(StackOper, (gpointer)oper);
}

void generate_quadruple(){
    char *first_type;   // Top de la pila de tipos
    char *second_type;  // Top-1 de la pila de tipos
    char *first_id;
    char *second_id;
    int first_oper;
    int second_oper;
    int operator = (int)g_queue_peek_tail(StackOper);   
    if (operator == 43 || operator == 45) { // '+' o '-'
        first_type = g_queue_peek_tail(StackTypes);
        second_type = g_queue_peek_nth(StackTypes, g_queue_get_length(StackTypes)-1);
        if (valid_var_types(first_type, second_type) != 0){ // Si es valido, se genera el cuadruplo
            operator = (int)g_queue_pop_tail(StackOper); 
            first_oper = g_queue_pop_tail(StackO);
            second_oper = g_queue_pop_tail(StackO);
            printf("Cuadruplo: %c\t %d\t %d\t Resultado\n", operator, first_oper, second_oper);
        }   
    }
    if (operator == 61) {   // '='
        first_type = g_queue_peek_tail(StackTypes);
        second_type = g_queue_peek_nth(StackTypes, g_queue_get_length(StackTypes)-1);
        if (valid_var_types(first_type, second_type) != 0){ // Si es valido, se genera el cuadruplo
            operator = (int)g_queue_pop_tail(StackOper); 
            first_oper = g_queue_pop_tail(StackO);
            //second_oper = g_queue_pop_tail(StackO);
            printf("Cuadruplo: %c\t %d\t\t Resultado\n", operator, first_oper);
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

void print_hash_var_table(char *key, vars_memory *value, gpointer user_data){
	printf("\t%s : %s : %d\n", key, value->type, value->virtual_address);
}

void print_var_table(char *function){
	printf("%s\n", function);
	type_table *temp_t_table = g_slice_new(type_table);
	temp_t_table = g_hash_table_lookup(proc_table, (gpointer)function);
	g_hash_table_foreach(temp_t_table->h_table, (GHFunc)print_hash_var_table, NULL);
}
