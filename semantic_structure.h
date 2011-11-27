/*
Compilador y Máquina Virtual para el lenguaje de programación Tláloc, como proyecto académico. 

Copyright (C) 2011 Eduardo López & Abraham Kuri

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/gpl.html.
*/

void create_proc_table();
void insert_proc_to_table(char *);
void print_hash_table();
void insert_vars_to_proc_table(char *var, char *tipo, int parameter);
void print_var_table(char *proc);
void create_stacks_and_queues();
void insert_id_to_StackO(char *id);
void insert_arr_index_to_StackO(char *id);
void insert_arr2_index_to_StackO(char *id);
void insert_movement_quadruple(); 
void insert_cte_id_to_StackO(int cte_integer);
void insert_cte_string_to_StackO(char *cte_integer);
void insert_cte_decimal_to_StackO(float cte_decimal);
void insert_cte_boolean_to_StackO(char *cte_boolean);
void generate_beginning_address();
void generate_ret_action();
void generate_era_action(char *proc);
void params_semantic_validation(char *id);
void verify_non_method_presence(char *id);
void check_params_number(char *id, int params); 
void generate_gosub(char *id);
void insert_to_StackOper(int oper);
void remove_from_StackOper();
void remove_from_StackO();
void delete_StackO();
void array_in_id();
int get_var_virtual_address(char *id);
void set_var_dimension(int dimension, char *id);
void reset_temp_vars();
void generate_exp_quadruples();
void generate_add_sust_quadruple();
void generate_mult_div_quadruple();
void generate_exponential_quadruple();
void generate_relational_quadruple();
void generate_step_for_quadruple();
void generate_return_action(char *proc);
void insert_proc_as_global_var(char *tipo, char *id);
void print_globals_to_file();
void create_constants_table();
void create_quadruples_array();
void print_to_file();
void generate_gotoF_if_quadruple();
void generate_goto_if_quadruple();
void fill_if();
void fill_goto_main();
void generate_while_gotoF_quadruple();
void push_cont_to_stack_jumps();
void generate_for_limit_quadruple();
void generate_gotoF_for_quadruple();
void fill_for();
void fill_step();
void push_to_stack_type(char *name);
