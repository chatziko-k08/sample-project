
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"


bool is_number(String s) {
	return s[0] >= '0' && s[0] <= '9';
}

int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

// create variable or constant
static Var create_variable(String name, Runtime runtime) {
	int* var_memory = map_find(runtime->variables, name);
	if(var_memory == NULL) {
		var_memory = create_int(atoi(name));
		map_insert(runtime->variables, strdup(name), var_memory);
	}

	#ifndef OPTIMIZED_VARS
	return strdup(name);
	#else
	return var_memory;
	#endif
}

static Array create_array(String name, Runtime runtime) {
	#ifndef OPTIMIZED_VARS
	return strdup(name);
	#else
	Array array = map_find(runtime->arrays, name);
	if(array == NULL) {
		array = vector_create(0, NULL);
		map_insert(runtime->arrays, name, array);
	}
	return array;
	#endif
}

static VarLike create_varlike(String token, Runtime runtime) {
	VarLike varlike = malloc(sizeof(*varlike));
	varlike->array = NULL;
	varlike->variable = NULL;
	char* bracket;

	if((bracket = strstr(token, "[")) != NULL) {
		// array[index]   =>   array\0index\0
		*bracket = '\0';
		String index = bracket + 1;
		index[strlen(index)-1] = '\0';

		varlike->array = create_array(token, runtime);
		varlike->variable = create_variable(index, runtime);

	} else {
		varlike->variable = create_variable(token, runtime);
		varlike->array = NULL;
	}
	return varlike;
}

static int find_type(String tokens[], int token_n) {
	return
		strcmp(tokens[0], "writeln") == 0 ? WRITELN :
		token_n == 3 && strcmp(tokens[1], "=") == 0 ? ASSIGN_VAR :
		token_n == 5 && strcmp(tokens[1], "=") == 0 ? ASSIGN_EXP :
		strcmp(tokens[0], "while") == 0 ? WHILE :
		strcmp(tokens[0], "if") == 0 ? IF :


		strcmp(tokens[0], "write") == 0 ? WRITE :
		strcmp(tokens[0], "read") == 0 ? READ:
		strcmp(tokens[0], "random") == 0 ? RAND :
		strcmp(tokens[0], "break") == 0 ? BREAK :
		strcmp(tokens[0], "continue") == 0 ? CONTINUE :
		strcmp(tokens[0], "argument") == 0 && strcmp(tokens[1], "size") == 0 ? ARG_SIZE :
		strcmp(tokens[0], "argument") == 0 ? ARG :
		strcmp(tokens[0], "new") == 0 ? NEW :
		strcmp(tokens[0], "free") == 0 ? FREE :
		strcmp(tokens[0], "size") == 0 ? SIZE :
		-1;
}

static Statement create_statement(String tokens[], int token_n, String line, int line_no, Runtime runtime) {
	int type = find_type(tokens, token_n);
	if(type == -1) {
		printf("error in line %s\n", line);
		exit(1);
	}

	Statement stm = calloc(1, sizeof(*stm));
	stm->line = line;
	stm->line_no = line_no;
	stm->type = type;

	if(type == WRITE || type == WRITELN || type == READ || type == RAND ||
	   ((type == BREAK || type == CONTINUE) && token_n == 2)) {

		stm->var1 = create_varlike(tokens[1], runtime);

	} else if(type == ASSIGN_VAR || type == ASSIGN_EXP) {
		stm->var1 = create_varlike(tokens[0], runtime);
		stm->var2 = create_varlike(tokens[2], runtime);

		if(type == ASSIGN_EXP) {
			stm->oper = tokens[3];
			stm->var3 = create_varlike(tokens[4], runtime);
		}

	} else if(type == IF || type == WHILE) {
		stm->var1 = create_varlike(tokens[1], runtime);
		stm->oper = tokens[2];
		stm->var2 = create_varlike(tokens[3], runtime);

	///////////////////////////

	} else if(type == ARG_SIZE) {
		stm->var1 = create_varlike(tokens[2], runtime);

	} else if(type == ARG) {
		stm->var1 = create_varlike(tokens[1], runtime);
		stm->var2 = create_varlike(tokens[2], runtime);

	} else if(type == NEW) {
		stm->array = create_array(strtok(tokens[1], "[]"), runtime);
		stm->var1 = create_varlike(strtok(NULL, "[]"), runtime);

	} else if(type == FREE) {
		stm->array = create_array(tokens[1], runtime);

	} else if(type == SIZE) {
		stm->array = create_array(tokens[1], runtime);
		stm->var1 = create_varlike(tokens[2], runtime);
	}

	return stm;
}

static Vector get_nested_source(Vector source, int start) {
	Vector nested = vector_create(0, NULL);
	for(int i = start; i < vector_size(source); i++) {
		String line = vector_get_at(source, i);
		if(line[0] != '\t' && line[0] != '\0' && line[1] != '#')
			break;
		vector_insert_last(nested, line+1);
	}
	return nested;
}

static Program create_program(Vector source, Runtime runtime) {
	Program prog = list_create(NULL);

	for(int i = 0; i < vector_size(source); i++) {
		String orig_line = vector_get_at(source, i);

		// split in tokens
		String tokenized_line = strdup(orig_line);
		String tokens[50];
		int token_n = 0;
		for(String token = strtok(tokenized_line, " \t\n"); token != NULL && token[0] != '#'; token = strtok(NULL, " \t\n"))
			tokens[token_n++] = token;

		if(token_n == 0)
			continue;		// empty line

		// else branches should be inserted in the last if statement
		if(strcmp(tokens[0], "else") == 0) {
			Vector nested = get_nested_source(source, i+1);
			Statement if_st = list_node_value(prog, list_last(prog));
			if_st->else_body = create_program(nested, runtime);
			i += vector_size(nested);
			vector_destroy(nested);
			continue;
		}

		Statement statement = create_statement(tokens, token_n, orig_line, i, runtime);

		// if/while have bodies
		if(statement->type == IF || statement->type == WHILE) {
			Vector nested = get_nested_source(source, i+1);
			statement->body = create_program(nested, runtime);
			i += vector_size(nested);
			vector_destroy(nested);
		}

		// insert in list
		list_insert_next(prog, list_last(prog), statement);
	}

	return prog;
}

Runtime parser_create_runtime(Vector source, Vector args, bool verbose) {
	Runtime runtime = malloc(sizeof(*runtime));
	runtime->variables = map_create((CompareFunc)strcmp, NULL, NULL);
	runtime->arrays = map_create((CompareFunc)strcmp, NULL, NULL);
	runtime->args = args;
	runtime->verbose = verbose;
	runtime->program = create_program(source, runtime);
	return runtime;
}

void parser_destroy_program(Program prog) {

}