#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static GHashTable *proc_table; // HashTable de procedimientos (key) leidos. (value) apunta a type_table 
char *current_function;        // Variable que mantiene el nombre de la funcion actual
char *global_function;         // Variable que mantiene el nombre del programa
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

typedef struct {
    char *type;
    int virtual_address;
}vars_memory;

// Inicializa tabla de procedimientos
void create_proc_table(){
	proc_table = g_hash_table_new(g_str_hash, g_str_equal); 
}

// Inicializa variables locales a 0 para cada nuevo procedimiento
void reset_memory_counters(){
    local_integers_count = 0, local_strings_count = 0,
    local_booleans_count = 0, local_decimals_count = 0;
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
                        printf("%d\n", global_integers_count);                    
                }
                if (strcmp(tipo, "string") == 0) {
                        address = GSTRINGS + global_strings_count;                        
                        global_strings_count++;                        
                }
                if (strcmp(tipo, "boolean") == 0) {
                        address = GBOOLEANS + global_booleans_count;                        
                        global_booleans_count++;                        
                }
                if (strcmp(tipo, "decimal") == 0) {
                        address = GDECIMALS + global_decimals_count;                        
                        global_decimals_count++;                        
                }
                v_memory->virtual_address = address;
            }                
            else {  // Si las variables son parte de un metodo
                if (strcmp(tipo, "integer") == 0) {
                        address = LINTEGERS + local_integers_count;                        
                        local_integers_count++;                        
                }
                if (strcmp(tipo, "string") == 0) {
                        address = LSTRINGS + local_strings_count;                        
                        local_strings_count++;                        
                }
                if (strcmp(tipo, "boolean") == 0) {
                        address = LBOOLEANS + local_booleans_count;                        
                        local_booleans_count++;                        
                }
                if (strcmp(tipo, "decimal") == 0) {
                        address = LDECIMALS + local_decimals_count;                        
                        local_decimals_count++;                        
                }
                v_memory->virtual_address = address;
            }     
            g_hash_table_insert(temp_t_table->h_table, (gpointer)var, (gpointer)v_memory);
        }
    } else {
        printf("Error. Procedimiento no existe\n");
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
