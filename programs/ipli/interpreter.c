
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ADTMap.h"
#include "interpreter.h"



// Επιστρέφει
//  n   για break n
// -n   για continue n
//  0   για οτιδήποτε άλλο
//
static int interpreter_run_program(Program prog, Runtime runtime);


static int evaluate_variable(Var var, Runtime runtime) {
	#ifndef OPTIMIZED_VARS	
	return *(int*)map_find(runtime->variables, var);
	#else
	return *var;
	#endif
}

static int evaluate_varlike(VarLike varlike, Runtime runtime) {
	if(varlike->array != NULL) {
		#ifndef OPTIMIZED_VARS	
		Vector vec = map_find(runtime->arrays, varlike->array);
		if(vec == NULL) {
			printf("array %s not allocated\n", varlike->array);
			exit(-1);
		}
		#else
		Vector vec = varlike->array;
		#endif
		return *(int*)vector_get_at(vec, evaluate_variable(varlike->variable, runtime));

	} else {
		return evaluate_variable(varlike->variable, runtime);
	}
}

static int evaluate_int_expression(VarLike var1, String oper, VarLike var2, Runtime runtime) {
	int val1 = evaluate_varlike(var1, runtime);
	int val2 = evaluate_varlike(var2, runtime);
	return
		oper[0] == '+' ? val1 + val2 :
		oper[0] == '-' ? val1 - val2 :
		oper[0] == '*' ? val1 * val2 :
		oper[0] == '/' ? val1 / val2 :
		oper[0] == '%' ? val1 % val2 :
		-1;
}

static bool evaluate_bool_expression(VarLike var1, String oper, VarLike var2, Runtime runtime) {
	int val1 = evaluate_varlike(var1, runtime);
	int val2 = evaluate_varlike(var2, runtime);
	return
		oper[0] == '=' ? val1 == val2 :
		oper[0] == '!' ? val1 != val2 :
		oper[0] == '>' && oper[1] == '=' ? val1 >= val2 :
		oper[0] == '>' && oper[1] == '=' ? val1 <= val2 :
		oper[0] == '>' ? val1 > val2 :
		oper[0] == '<' ? val1 < val2 :
		-1;
}

static void assign_to_varlike(VarLike varlike, int value, Runtime runtime) {
	#ifndef OPTIMIZED_VARS	
	if(varlike->array != NULL) {
		Vector vec = map_find(runtime->arrays, varlike->array);
		int index= evaluate_variable(varlike->variable, runtime);
		*(int*)vector_get_at(vec, index) = value;

	} else {
		int* var_memory = map_find(runtime->variables, varlike->variable);
		if(var_memory == NULL) {
			var_memory = create_int(0);
			map_insert(runtime->variables, varlike->variable, var_memory);
		}
		*var_memory = value;
	}

	#else
	if(varlike->array != NULL)
		*(int*)vector_get_at(varlike->array, *(varlike->variable)) = value;
	else
		*(varlike->variable) = value;
	#endif
}

static int run_statement(Statement stm, Runtime runtime) {
	if(runtime->verbose)
		printf("%d:\t%s", stm->line_no, stm->line);

	switch(stm->type) {
		case WRITELN:
			printf("%d\n", evaluate_varlike(stm->var1, runtime));
			return 0;

		case ASSIGN_VAR:
			assign_to_varlike(stm->var1, evaluate_varlike(stm->var2, runtime), runtime);
			return 0;

		case ASSIGN_EXP: {
			int value = evaluate_int_expression(stm->var2, stm->oper, stm->var3, runtime);
			assign_to_varlike(stm->var1, value, runtime);
			return 0;
		}

		case IF: {
			int val = evaluate_bool_expression(stm->var1, stm->oper, stm->var2, runtime);
			if(val)
				return interpreter_run_program(stm->body, runtime);
			else if(stm->else_body != NULL)
				return interpreter_run_program(stm->else_body, runtime);
			else
				return 0;
		}

		case WHILE:
			while(1) {
				int val = evaluate_bool_expression(stm->var1, stm->oper, stm->var2, runtime);
				if(!val) return 0;

				// Το τρέχων loop διακόπτεται είναι από κάποιο break, είτε και από continue >=2
				int result = interpreter_run_program(stm->body, runtime);
				if(result >= 1 || result <= -2)
					return result + (result > 0 ? -1 : 1); // μειώνουμε το level κατά 1
			}
			return 0;

		////////////////////////////

		case WRITE:
			printf("%d ", evaluate_varlike(stm->var1, runtime));
			return 0;

		case RAND:
			assign_to_varlike(stm->var1, rand(), runtime);
			return 0;

		case READ: {
			int value;
			if(scanf("%d", &value) != 1)
				exit(1);
			assign_to_varlike(stm->var1, value, runtime);
			return 0;
		}

		case BREAK:
			return stm->var1 != NULL ? evaluate_varlike(stm->var1, runtime) : 1;

		case CONTINUE:
			return -1 * (stm->var1 != NULL ? evaluate_varlike(stm->var1, runtime) : 1);


		case ARG_SIZE:
			assign_to_varlike(stm->var1, vector_size(runtime->args), runtime);
			return 0;

		case ARG: {
			int n = evaluate_varlike(stm->var1, runtime);
			assign_to_varlike(stm->var2, atoi(vector_get_at(runtime->args, n-1)), runtime);
			return 0;
		}

		case NEW: {
			int size = evaluate_varlike(stm->var1, runtime);

			#ifndef OPTIMIZED_VARS
			Vector vec = vector_create(0, NULL);
			for(int i = 0; i < size; i++)
				vector_insert_last(vec, create_int(0));
			map_insert(runtime->arrays, stm->array, vec);
			#else
			while(size > vector_size(stm->array))
				vector_insert_last(stm->array, calloc(1, sizeof(int)));
			#endif
			return 0;
		}

		case FREE: {
			#ifndef OPTIMIZED_VARS
			Vector vec = map_find(runtime->arrays, stm->array);
			map_remove(runtime->arrays, stm->array);
			vector_destroy(vec);
			#else
			while(vector_size(stm->array) > 0)
				vector_remove_last(stm->array);
			#endif
			return 0;
		}

		case SIZE: {
			#ifndef OPTIMIZED_VARS
			Vector vec = map_find(runtime->arrays, stm->array);
			assign_to_varlike(stm->var1, vector_size(vec), runtime);
			#else
			assign_to_varlike(stm->var1, vector_size(stm->array), runtime);
			#endif
			return 0;
		}
	}
	return 0;
}

static int interpreter_run_program(Program prog, Runtime runtime) {
	for(ListNode node = list_first(prog); node != LIST_EOF; node = list_next(prog, node)) {
		Statement statement = list_node_value(prog, node);
		int result = run_statement(statement, runtime);
		if(result != 0)
			return result;		// break ή continue, διακόπτεται η τρέχουσα λίστα εντολών
	}
	return 0;
}

void interpreter_run(Runtime runtime) {
	interpreter_run_program(runtime->program, runtime);
}