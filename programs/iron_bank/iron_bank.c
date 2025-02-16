// iron_bank
// Διαχείριση πελατών της Iron Bank of Braavos
//
// Το πρόγραμμα αυτό τυπώνει τους μεγαλύτερους οφειλέτες και πιστωτές
// της τράπεζας, καθώς και το υπόλοιπο των πελατών που περνιούνται σαν
// όρισμα.
//
//
// ΠΡΟΣΟΧΗ
//
// Το πρόγραμμα πιθανότατα έχει κάποιο bug. Οι χρήστες αναφέρουν ότι για
// κάποιους πελάτες δουλεύει, αλλά για τον "Tyrion Lannister" έχει πρόβλημα.

#include <stdio.h>

#include "customer.h"


void print_top_borrowers(Customer* customers, int size, int n) {
	printf("\nTop borrowers\n--------------\n");

	for (int i = 0; i < n && i < size; i++)
		customer_print(&customers[i]);
}

void print_top_lenders(Customer* customers, int size, int n) {
	printf("\nTop lenders\n--------------\n");

	for (int i = size-1; i > size-1-n && i > 0; i--)
		customer_print(&customers[i]);
}

int main(int argc, char* argv[]) {
	// Διαβάζουμε τη βάση δεδομένων των πελατών
	int size;
	Customer* customers = customer_read_from_file("customers.csv", &size);

	// Εκτύπωση των μεγαλύτερων
	print_top_borrowers(customers, size, 5);
	print_top_lenders(customers, size, 5);

	// Αν δοθούν ορίσματα γίνεται αναζήτηση χρηστών με τα ονόματα αυτά
	printf("\nSearch results\n--------------\n");
	
	for (int i = 1; i < argc; i++) {
		Customer* customer = customer_find(customers, size, argv[i]);
		if (customer)
			customer_print(customer);
		else
			printf("%s not found\n", argv[i]);
	}
}
