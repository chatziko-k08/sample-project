
#include "ADTSet.h"
#include "ADTList.h"
#include "ADTMap.h"

typedef char* String;

// Πληροφορίες για μία χώρα

struct country {
	String color;			// χρώμα που έχει ανατεθεί (NULL αν είναι αχρωμάτιστη)
	Set avail_colors;		// διαθέσιμα χρώματα
	List neighbors;			// γειτονες
};
typedef struct country* Country;

// Ενα Coloring είναι ένα Map: <όνομα χώρας> (String) => "πληροφορίες για τη χώρα" (Country)
// πχ  "Greece" => <πληροφορίες για την ελλάδα>
// Κάνουμε typedef απλά για ευκολία, ώστε όταν γράφουμε "Coloring" να καταλαβαίνουμε τι τύπου Map εννοούμε.

typedef Map Coloring;


// Συνάρτηση που παίρνει έναν μερικό χρωματισμό και τον ολοκληρώνει!
// - Αν υπάρχει λύση, την αποθηκεύει στο coloring και επιστρέφει true
// - Αν ΔΕΝ υπάρχει λύση, επιστρέφει false, και αφηνει το coloring στην __ίδια κατάσταση__ που ήταν πριν!

bool tzini(Coloring coloring);

// Διαβάζει και επιστρέφει ένα χρωματισμό από την είσοδο

Coloring read_input();

// Τυπώνει ένα χρωματισμό

void print_coloring(Coloring coloring);

// Ελέγχει αν ο χρωματισμός είναι έγκυρος

bool test_coloring(Coloring coloring);
