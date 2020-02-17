// minmax
// Τυπώνει τον μικρότερο και το μεγαλύτερο αριθμό από αυτούς που δίνονται ως ορίσματα.

#include <stdio.h>
#include <stdlib.h>

#include "stats.h"

int main(int argc, char* argv[]) {
	// Δημιουργία array με τις παραμέτρους του προγράμματος, αφού μετατραπούν σε int
	int size = argc-1;
	int array[size];

	for(int i = 0; i < size; i++)
		array[i] = atoi(argv[i+1]);

	printf("min: %d\n", stats_find_min(array, size));
	printf("max: %d\n", stats_find_max(array, size));
}