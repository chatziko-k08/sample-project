// stats_alt.c - Εναλλακτική υλοποίηση του stats module

#include <stdbool.h>

#include "stats.h"

// Επιστρέφει true αν value <= array[i] για κάθε i

bool smaller_than_all(int value, int array[], int size) {
    for(int i = 0; i < size; i++)
        if(value > array[i])
            return false;
    return true;
}

// Επιστρέφει true αν value >= array[i] για κάθε i

bool larger_than_all(int value, int array[], int size) {
    for(int i = 0; i < size; i++)
        if(value < array[i])
            return false;
    return true;
}

int stats_find_min(int array[], int size) {
    for(int i = 0; i < size; i++)
        if(smaller_than_all(array[i], array, size))
            return array[i];

    return INT_MAX;     // εδώ φτάνουμε μόνο σε περίπτωση κενού array
}

int stats_find_max(int array[], int size) {
    for(int i = 0; i < size; i++)
        if(larger_than_all(array[i], array, size))
            return array[i];

    return INT_MIN;     // εδώ φτάνουμε μόνο σε περίπτωση κενού array
}