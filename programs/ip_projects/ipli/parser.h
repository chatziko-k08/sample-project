
#pragma once

#include <ADTList.h>
#include <ADTVector.h>
#include <ADTMap.h>


// Το OPTIMIZED_VARS flag καθορίζει τον τύπο που έχουν μεταβλητές και πίνακες
// όταν τελειώσει το parsing.
//
// - Αν το OPTIMIZED_VARS δεν είναι defined, τότε μια μεταβλητή foo είναι αποθηκευμένη
//   απλά σαν το string "foo", και η τιμή της γίνεται resolve κατά το execution
//   μέσω του Map variables.
// 
// - Αν το OPTIMIZED_VARS είναι defined, τότε κατά το parsing δεσμεύεται μνήμη για τη
//   μεταβλητή, και αντί για το string "foo" αποθηκεύουμε έναν pointer προς τη θέση
//   μνήμης, γλιτώνοντας το επαναλλαμβανόμενο map_find κατά το runtime. Παρομοίως, ένας
//   πίνακας array αποθηκεύεται ως Vector, αντί για το string "array".
//
// Το flag μπορούμε να το ορίσουμε με το παρακάτω #define, είτε τρέχοντας
// make CFLAGS=-DOPTIMIZED_VARS
//
// #define OPTIMIZED_VARS


typedef char* String;

#ifndef OPTIMIZED_VARS
typedef String Var;
typedef String Array;
#else
typedef int* Var;
typedef Vector Array;
#endif

typedef List Program;	// List of Statement

typedef enum {
	WRITELN,		// writeln <var1>
	ASSIGN_VAR,		// <var1> = <var2>
	ASSIGN_EXP,		// <var1> = <var2> <op> <var3>
	WHILE,			// while <var1> <op> <var2>  \n<body>
	IF,				// if <var1> <op> <var2>  \n<body>  \nelse  \n<body>

	WRITE,			// write <var1>
	READ,			// read <var1>
	RAND,			// random <var1>
	ARG_SIZE,		// argument size <var1>
	ARG,			// argument <var1> <var2>
	BREAK,			// break <var1>
	CONTINUE,		// continue <var1>
	NEW,			// new <array>[var1]
	FREE,			// free <array>
	SIZE,			// size <array> <var1>
} StatementType;

// <int> | <var> | <array>[<var>]
typedef struct {
	Var variable;	// also used for cosntants
	Array array;	// if non-NULL, variable is the index
}* VarLike;

typedef struct {
	StatementType type;
	Program body, else_body;
	VarLike var1, var2, var3;
	Array array;
	String oper;
	String line;
	int line_no;
}* Statement;

typedef struct {
	Program program;
	Map variables;		// name => int
	Map arrays;			// name => Vector of int
	Vector args;		// vec of Strings
	bool verbose;
}* Runtime;


// Parses a source file (vector of strings) into a program

Runtime parser_create_runtime(Vector source, Vector args, bool verbose);

void parser_destroy_runtime(Runtime prog);

int* create_int(int value);