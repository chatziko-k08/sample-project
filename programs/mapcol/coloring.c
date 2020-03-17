#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "coloring.h"

// Το αρχείο αυτό φτιάχτηκε στο live streaming: https://youtu.be/GbfzJBnBncw
//
// ΠΡΟΣΟΧΗ: είναι ελλειπής κώδικας, μπορεί να περιέχει bugs, δεν ελέγχει τη τελική λύση,
//          δεν απελευθερώνει μνήμη, κλπ.


int color_no = 4;
String colors[] = { "red", "green", "blue", "yellow" };


// Βρίσκει και επιστρέφει τη χώρα που ειναι __αχρωματιστη__ στο coloring με τα λιγότερα διαθέσιμα χρώματα
Country min_avail_colors(Coloring coloring) {
	Country result = NULL;
	int min = INT_MAX;

	for(MapNode node = map_first(coloring);
		node != MAP_EOF;
		node = map_next(coloring, node)) {

		Country country = map_node_value(coloring, node);

		// skip τις χρωματισμένες χώρες
		if(country->color != NULL)
			continue;

		int no_colors = set_size(country->avail_colors);
		if(no_colors < min) {
			result = country;
			min = no_colors;
		}
	}

	return result;
}

bool try_color(Coloring coloring, Country country, String color) {
	// Χρωμάτισε με το χρώμα αυτό
	country->color = strdup(color);

	// Αποθηκεύουμε εδώ τους γείτονες (Country struct) από τους οποίους αφαιρέθηκε __πραγματικά__ το χρώμα
	List removed = list_create(NULL);

	// Αφαίρεσε το color από το avail_colors του κάθε γείτονα
	for(ListNode node = list_first(country->neighbors);
		node != LIST_EOF;
		node = list_next(country->neighbors, node)) {

		String neighbor_name = list_node_value(country->neighbors, node);
		Country neighbor_info = map_find(coloring, neighbor_name);

		// Αφαιρώ το color από τα διαθέσιμα του γείτονα.
		// Προσοχή: μπορεί να μην υπήρχε στα διαθέσιμα. Αποθήκευση στο remove list, τους γείτονες που πραγματικά κάναμε remove.
		if(set_remove(neighbor_info->avail_colors, color))
			list_insert_next(removed, LIST_BOF, neighbor_info);
	}

	// Κάλεσε το τζίνι για να λύσει το μικρότερο πρόβλημα
	bool found = tzini(coloring);

	// Αν δεν υπάρχει λύση
	if(!found) {
		// Αναιρεση τησ αναθεσης
		country->color = NULL;

		// επαναφορά του color μόνο στους γείτονες που είναι στη λίστα removed
		for(ListNode node = list_first(removed);
			node != LIST_EOF;
			node = list_next(removed, node)) {

			Country neighbor_info = list_node_value(removed, node);
			set_insert(neighbor_info->avail_colors, color);
		}
	}

	list_destroy(removed);

	return found;
}

bool tzini(Coloring coloring) {
	// Βρες ποια χώρα θα χρωματίσουμε (αυτή με τα λιγοτερα διαθεσιμα χρωματα)
	Country country = min_avail_colors(coloring);

	// Αν όλες είναι χρωματισμένες τελειώσαμε
	if(country == NULL)
		return true;

	// Για κάθε διαθέσιμο χρώμα
	for(SetNode node = set_first(country->avail_colors);
		node != SET_EOF;
		node = set_next(country->avail_colors, node)) {

		// Δοκιμάσε το χρώμα, αν βρεθεί λύση τελειώσαμε
		String color = set_node_value(country->avail_colors, node);
		if(try_color(coloring, country, color))
			return true;
	}

	return false;
}

int compare_strings(Pointer a, Pointer b) {
	return strcmp(a, b);
}

Coloring read_input() {
	int N = 50000;
	char line[N];

	Coloring coloring = map_create(compare_strings, NULL, NULL);

	while(fgets(line, N, stdin) != NULL) {
		strtok(line, " \t\n");
		String name = strdup(strtok(NULL, " \t\n"));

		// Δημιουργώ ένα Country και το προσθέσω στο map!
		Country country = malloc(sizeof(struct country));

		country->color = NULL;

		// σύνολο από διαθέσιμα χρώματα
		country->avail_colors = set_create(compare_strings, NULL);
		for(int i = 0; i < color_no; i++)
			set_insert(country->avail_colors, colors[i]);

		// λίστα από γείτονες
		country->neighbors = list_create(NULL);

		String neighbor;
		while((neighbor = strtok(NULL, " \t\n")) != NULL)
			list_insert_next(country->neighbors, LIST_BOF, strdup(neighbor));

		// insert country στο map!
		map_insert(coloring, name, country);
	}

	return coloring;
}

void print_coloring(Coloring coloring) {
	for(MapNode node = map_first(coloring);
		node != MAP_EOF;
		node = map_next(coloring, node)) {

		String name = map_node_key(coloring, node);
		Country country = map_node_value(coloring, node);

		printf("%s  /  %s  /  ", name, country->color);

		// γείτονες
		for(ListNode node = list_first(country->neighbors);
			node != LIST_EOF;
			node = list_next(country->neighbors, node)) {

			printf("%s ", (char*)list_node_value(country->neighbors, node));
		}

		// avail colirs
		printf("  / ");
		for(SetNode node = set_first(country->avail_colors);
			node != SET_EOF;
			node = set_next(country->avail_colors, node)) {

			printf("%s ", (char*)set_node_value(country->avail_colors, node));
		}

		printf("\n");
	}
}