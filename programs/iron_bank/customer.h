////////////////////////////////////////////////////////////////////////
//
// customer
//
// Module που χειρίζεται εγγραφές πελατών της Iron Bank
//
////////////////////////////////////////////////////////////////////////

#pragma once // #include το πολύ μία φορά


typedef char* String;

// Στοιχεία πελάτη

typedef struct {
	int balance;	// Το balance σε gold dragons. Αρνητικό για τους οφειλέτες.
	String name;	// Όνομα
} Customer;


// Διαβάζει τους πελάτες από το αρχείο filename και τους επιστρέφει
// σε έναν πίνακα ταξινομημένους κατά balance. Στο ret_size επιστρέφεται
// ο αριθμός των πελατών που διαβάστηκαν.

Customer* customer_read_from_file(String filename, int* ret_size);


// Αναζητεί τον πελάτη με όνομα name στον πίνακα customers μεγέθους size.
// Επιστρέφει τον πελάτη αν βρεθεί, αλλιώς NULL.

Customer* customer_find(Customer* customers, int size, String name);


// Εκτυπώνει τα στοιχεία του πελάτη customer

void customer_print(Customer* customer);
