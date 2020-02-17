//////////////////////////////////////////////////////////////////
//
// Unit tests για το stats module
// Οποιαδήποτε υλοποίηση οφείλει να περνάει όλα τα tests.
//
//////////////////////////////////////////////////////////////////

#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "stats.h"


void test_find_min(void) {
	int array[] = { 3, 1, -1, 50 };

	TEST_CHECK(stats_find_min(array, 4) == -1);
	TEST_CHECK(stats_find_min(array, 3) == -1);
	TEST_CHECK(stats_find_min(array, 2) == 1);
	TEST_CHECK(stats_find_min(array, 1) == 3);
	TEST_CHECK(stats_find_min(array, 0) == INT_MAX);
}

void test_find_max(void) {
	int array[] = { 3, 1, -1, 50 };

	TEST_CHECK(stats_find_max(array, 4) == 50);
	TEST_CHECK(stats_find_max(array, 3) == 3);
	TEST_CHECK(stats_find_max(array, 2) == 3);
	TEST_CHECK(stats_find_max(array, 1) == 3);
	TEST_CHECK(stats_find_max(array, 0) == INT_MIN);
}

// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "find_min", test_find_min },
	{ "find_max", test_find_max },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};