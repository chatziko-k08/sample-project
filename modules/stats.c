// stats.c - Υλοποίηση του stats module

#include "stats.h"

int stats_find_min(int array[], int size) {
	int min = INT_MAX;          // "default" τιμή, μεγαλύτερη από όλες

	for(int i = 0; i < size; i++)
		if(array[i] < min)
			min = array[i];     // βρέθηκε νέο ελάχιστο
	
	return min;
}

int stats_find_max(int array[], int size) {
	int max = INT_MIN;			// "default" τιμή, μικρότερη από όλες

	for(int i = 0; i < size; i++)
		if(array[i] > max)
			max = array[i];		// βρέθηκε νέο μέγιστο
	
	return max;
}