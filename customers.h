#ifndef CUSTOMERS_H
#define CUSTOMERS_H


#include <stdio.h>
#include "functions.h"


/* Ez a header file egy embereket tartalmazó láncolt lista műveleteihez szükséges struktúradefiníciókat és függvényeket tartalmaz. */


// Az ember adatait tartalmazó struktúra.
typedef struct data_c {
    char *name; // Az ember neve.
    char *id; // Az ember könyvtári azonosító száma.
    char *debt; // Az ember tartozása a könyvtár felé forintban kifejezve
} data_c;

// A lista egy elemét definiáló struktúra.
// Az implementációhoz kétszeresen láncolt, elöl-hátul strázsás listát használok.
typedef struct customer_list_element {
    data_c customer;
    struct customer_list_element *next, *prev;
} customer_list_element, *customer_list_ptr;

// A listát megtestesítő struktúra, tartalmazza a lista első és utolsó strázsáját.
typedef struct {
    customer_list_element *head;
    customer_list_element *tail;
} clist, *clist_ptr;


// Létrehoz egy inicializást üres listát - a head és tail strázsát. A két strázsa adatmezője ki van nullázva NULL pointerekkel. 
clist create_clist(void);

// Összefoglalja a paramétereként kapott adatokat egy data_c struktúrába.
data_c concatenate_to_data_c(char *name, char *id, char *debt);

// Egy megnyitott fb filepointerből beolvassa az adatokat a listába. Semmilyen szempontból nincsennek rendezve az adatok, az először beolvasott elem lesz az utolsó, az utoljára beolvasott elem lesz az első a listában.
int get_data_c(clist customer_list, FILE *fc);

// A listába bárhova be tud szúrni elemet. Nem ellenőrzi, hogy érvényes-e a prev, és next pointer, tehát abban az esetben is használható lenne, ha nem teljesen így nézne ki a lista struktúrája.
int insert_between_c(customer_list_ptr prev, customer_list_ptr next, data_c customer);

// Törli a teljes listát a memóriából.
void dispose_clist(clist l);

// Paraméterként megkapott értékre keres kis és nagybetűt megkülönböztetve az emberek nevei között. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void search_for_name(void *list_of_customers, char *name);

// Paraméterként megkapott értékre keres kis és nagybetűt megkülönböztetve az emberek azonosító számai között. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void search_for_id(void *list_of_customers, char *id);

// Paraméterként megkapott értékre keres kis és nagybetűt megkülönböztetve az emberek tartozásai között. Csak olyan találatot listáz, ahol teljes eredmény van.
void search_for_debt(void *list_of_customers, char *debt);

// Egyetlen paraméterként megkapott data_c struktúra minden elemét kiírja az stdout-ra.
void print_customer(data_c customer);

// Törli a paraméterként kapott struktúrában lévő stringek utolsó karatkerét, ha az newline karater ('\n').
void del_last_newline_from_structure_c(data_c customer);


// Definiálja a keresési logikát megvalósító függvénypointerek neveit. 
extern search_function_ptr search_for_name_ptr;
extern search_function_ptr search_for_id_ptr;
extern search_function_ptr search_for_debt_ptr;


#endif
