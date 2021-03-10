
#include "coloring.h"

int main(void) {
	Coloring coloring = read_input();

	tzini(coloring);

	print_coloring(coloring);
} 
