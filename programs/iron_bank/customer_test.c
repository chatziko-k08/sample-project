//
// Unit tests για το customer.h module
//

#include <string.h>

#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "customer.h"


void test_customer_read_from_file(void) {
	int size;
	Customer* customers = customer_read_from_file("customers.csv", &size);

	TEST_ASSERT(customers != NULL);
	TEST_ASSERT(size == 163);

	// έλεγχος ότι ο πίνακας είναι ταξινομημένος
	for (int i = 1; i < size; i++)
		TEST_ASSERT(customers[i-1].balance <= customers[i].balance);

}

void test_customer_find(void) {
	int size;
	Customer* customers = customer_read_from_file("customers.csv", &size);

	Customer* customer = customer_find(customers, size, "Jon Snow");

	TEST_ASSERT(customer != NULL);
	TEST_ASSERT(strcmp(customer->name, "Jon Snow") == 0);
	TEST_ASSERT(customer->balance == -687);
}

// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "test_customer_read_from_file", test_customer_read_from_file },
	{ "test_customer_find", test_customer_find },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};
