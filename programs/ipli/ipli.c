///////////////////////////////////////////////////////////////
//
// ipli
//
// Υλοποίηση ενός interpreter για τη γλώσσα IPL
// Πληροφορίες στο iphw2021_4.pdf
//
///////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "parser.h"
#include "interpreter.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int first_arg = 1;
	bool verbose = false;
	if(strcmp(argv[first_arg], "-v") == 0) {
		verbose = true;
		first_arg++;
	}

	// read source
	String filename = argv[first_arg];
	FILE* file = fopen(filename, "r");
	if(!file) {
		fprintf(stderr, "invalid file\n");
		return -1;
	}
	Vector source = vector_create(0, NULL);

	int N = 100;
	char line[N];

	while(fgets(line, N, file) != NULL)
		vector_insert_last(source, strdup(line));
	fclose(file);

	// collect args
	Vector args = vector_create(0, NULL);
	for(int i = first_arg + 1; i < argc; i++)
		vector_insert_last(args, argv[i]);

	// create program and run
	Runtime runtime = parser_create_runtime(source, args, verbose);
	interpreter_run(runtime);
}