#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static GHashTable *proc_table; // HashTable de procedimientos (key) leidos. (value) apunta a type_table 
char *current_function;        // Variable que mantiene el nombre de la funcion actual

// type_table: tabla que guarda el tipo de valor de retorno de la funcion leia en programa
typedef struct {
	char *method_type;          // Nombre del metodo
	GHashTable *h_table;        // Tabla de variables del metodo
}type_table;

// Inicializa tabla de procedimientos
void create_proc_table(){
	proc_table = g_hash_table_new(g_str_hash, g_str_equal); 
}


void insert_proc_to_table(char *proc, char *tipo){
	if(g_hash_table_lookup(proc_table, (gpointer)proc) != NULL){
		printf("El metodo '%s' ya esta dado de alta\n", proc);
		exit(0);
	}else{
		type_table *t_table = g_slice_new(type_table); //Creamos tabla de hashing para los tipos 1x2
		t_table->method_type = tipo;
		t_table->h_table = g_hash_table_new(g_str_hash, g_str_equal); //Tabla de variables declarada
		g_hash_table_insert(proc_table, (gpointer)proc, (gpointer)t_table);
		current_function = proc;

	}
}

void insert_vars_to_proc_table(char *var, char *tipo){
	 if(g_hash_table_lookup(proc_table, (gpointer)current_function) != NULL){
		type_table *temp_t_table = g_slice_new(type_table);
		temp_t_table = g_hash_table_lookup(proc_table, (gpointer)current_function);
		if(g_hash_table_lookup(temp_t_table->h_table, (gpointer)var) != NULL){
			printf("La variable %s ya esta declarada", var);
			exit(0);
		}else{
			g_hash_table_insert(temp_t_table->h_table, (gpointer)var, (gpointer)tipo);
			
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

void print_hash_var_table(char *key, char *value, gpointer user_data){
	printf("\t%s : %s\n", key, value);
}

void print_var_table(char *function){
	printf("%s\n", function);
	type_table *temp_t_table = g_slice_new(type_table);
	temp_t_table = g_hash_table_lookup(proc_table, (gpointer)function);
	g_hash_table_foreach(temp_t_table->h_table, (GHFunc)print_hash_var_table, NULL);
}
