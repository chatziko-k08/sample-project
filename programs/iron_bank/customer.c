#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "customer.h"

#define MAX_ARRAY_SIZE 1000
#define MAX_NAME_SIZE 100


// Σύγκριση πελατών με βάση το balance τους

static int compare_customers(Customer* a, Customer* b) {
	if (a->balance < b->balance)
		return -1;
	else if (a->balance > b->balance)
		return 1;
	else
		return 0;
}

// Διαβάζει τους πελάτες από το αρχείο filename και τους επιστρέφει
// σε έναν πίνακα ταξινομημένους κατά balance. Στο ret_size επιστρέφεται
// ο αριθμός των πελατών που διαβάστηκαν.

Customer* customer_read_from_file(String filename, int* ret_size) {
	FILE* file = fopen(filename, "r");

	// hard-coded μέγιστος αριθμός πελατών. Στο μέλλον θα μπορούσαμε
	// να βάλουμε μια δομή που να μεγαλώνει.
	//
	Customer* customers = malloc(MAX_ARRAY_SIZE * sizeof(Customer));
	int size = 0;

	// διαβάζουμε όλες τις γραμμές του αρχείου
	while (true) {
		// διαβάζουμε το balance, τερματισμός στο τέλος του αρχείου
		int balance;
		if (fscanf(file, "%d,", &balance) == EOF)
			break;

		// έχουμε νέα γραμμή, έλεγχος μεγέθους
		if(size == MAX_ARRAY_SIZE)
			break;
		size++;

		// διαβάζουμε το όνομα, αφαιρώντας το newline (\n) από το τέλος
		char name[MAX_NAME_SIZE];
		fgets(name, MAX_NAME_SIZE, file);
		name[strlen(name) - 1] = '\0';

		// προσθήκη στον πίνακα
		customers[size].balance = balance;
		customers[size].name = strdup(name);
	}
	fclose(file);

	// ταξινόμηση κατά balance
	qsort(customers, size, sizeof(Customer), (void*)compare_customers);

	*ret_size = size;
	return customers;
}

// Αναζητεί τον πελάτη με όνομα name στον πίνακα customers μεγέθους size.
// Επιστρέφει τον πελάτη αν βρεθεί, αλλιώς NULL.

Customer* customer_find(Customer* customers, int size, String name) {
	// Σειριακή αναζήτηση, γιατί οι πελάτες είναι τακινομημένοι κατά balance, όχι
	// κατά όνομα! Στο μέλλον θα μπορούσαμε να κάνουμε κάτι καλύτερο.
	//
	for (int i = 0; i < size; i++)
		if (strcmp(name, customers[i].name) == 0)
			return &customers[i];

	return NULL;
}

void customer_print(Customer* customer) {
	printf("%d %s\n", customer->balance, customer->name);
}
