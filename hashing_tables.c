#include <glib.h>
#include <stdio.h>
#include <string.h>

static GHashTable *proc_table;

typedef struct {
	char *method_type;
	GHashTable *h_table;
}type_table;

void create_proc_table(){
	proc_table = g_hash_table_new(g_str_hash, g_str_equal); 
} 

void insert_proc_to_table(char *proc, char *tipo){
	if(g_hash_table_lookup(proc_table, (gpointer)proc) != NULL){
		printf("El metodo ya esta dado de alta");
	}else{
		type_table *t_table = g_slice_new(type_table); //Creamos tabla de hashing para los tipos 1x2
		t_table->method_type = tipo;
		g_hash_table_insert(proc_table, (gpointer)proc, (gpointer)t_table);
	}
}

static void print_hash(char *key, type_table *value, gpointer user_data){
	printf("%s : %s\n", key, value->method_type);
}

void print_hash_table(){
	g_hash_table_foreach(proc_table, (GHFunc)print_hash, NULL);
}