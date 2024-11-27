#ifndef BOOKS_H
#define BOOKS_H


#include <stdio.h>
#include "functions.h"


/* Ez a header file egy könyveket tartalmazó láncolt lista műveleteihez szükséges struktúradefiníciókat, és függvényeket tartalmaz. */


// Az könyv adait tartalmazó struktúra.
typedef struct data_b {
    char *title; // A könyv címe.
    char *author; // A könyv szerzője.
    char *publisher; // A könyv kiadója.
    char *isbn; // A könyv ISBN száma.
    char *borrowed; // A könyv kikölcsönzési állapota: üres string ha nincs kikölcsönözve, egyébként a kikölcsönző azonosító számát tartalmazza.
    char *library_number; // A könyvtári rendszerben saját "házon belüli" azonosítószám helye. 
    char *genres; // A könyv műfajai, KISBETŰVEL - a keresőfüggvény nem case-szenzitív, tehát ha nagybetűvel van beírva a file-ba a műfaj, nem fogja a felhasználónak megtalálni!!
} data_b;

// A lista egy elemét definiáló struktúra.
// Az implementációhoz kétszeresen láncolt, elől-hátul strázsás listát használok.
typedef struct book_list_element {
    data_b book;
    struct book_list_element *next, *prev;
} book_list_element, *book_list_ptr;

// A listát megtestesítő struktúra, tartalmazza a lista első és utolsó strázsáját.
typedef struct {
    book_list_element *head;
    book_list_element *tail;
} blist, *blist_ptr;


// Létrehoz egy inicializást üres listát - a head és tail strázsát. A két strázsa adatmezője ki van nullázva NULL pointerekkel. 
blist create_blist(void); 

// Összefoglalja a paramétereként kapott adatokat egy data_b struktúrába.
data_b concatenate_to_data_b(char *title, char *author, char *publisher, char *isbn, char *borrowed, char *library_number, char *genres); 

// Egy megnyitott fb filepointerből beolvassa az adatokat a listába. Semmilyen szempontból nincsennek rendezve az adatok, az először beolvasott elem lesz az utolsó, az utoljára beolvasott elem lesz az első a listában.
int get_data_b(blist book_list, FILE *fb); 

// A listába bárhova be tud szúrni elemet. Nem ellenőrzi, hogy érvényes-e a prev, és next pointer, tehát abban az esetben is használható lenne, ha nem teljesen így nézne ki a lista struktúrája.
int insert_between_b(book_list_ptr prev, book_list_ptr next, data_b book); 

// Törli a teljes listát a memóriából.
void dispose_blist(blist l); 

// Paraméterként megkapott értékre keres kis és nagybetűt megkülönböztetve a könyvek szerzői között. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void search_for_author(void *list_of_books, char *author); 

// Paraméterként megkapott értékre keres kis és nagybetűt megkülönböztetve a könyvek stílusában. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void search_for_genre(void *list_of_books, char *genre); 

// Paraméterként megkapott értékekre keres kis és nagybetűt megkülönböztetve a könyvek címei között. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void search_for_title(void *list_of_books, char *title); 

// Egyetlen paraméterként megkapott data_b stuktúra minden elemét kiírja az stdout-ra.
void print_book(data_b book); 

// Törli a paraméterként kapott struktúrákban lévő stringek utolsó karatkerét, ha az newline ('\n') karakter.
void del_last_newline_from_structure_b(data_b book); 


// Definiálja a keresési logikát megvalósító függvénypointerek neveit. 
extern search_function_ptr search_for_author_ptr;
extern search_function_ptr search_for_genre_ptr;
extern search_function_ptr search_for_title_ptr;


#endif
