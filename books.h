#ifndef BOOKS_H
#define BOOKS_H


#include <stdio.h>
#include "functions.h"


/* Ez a header file egy könyveket tartalmazó láncolt lista műveleteihez szükséges struktúradefiníciókat, és függvényeket tartalmaz. */


// Az könyv adait tartalmazó struktúra 
typedef struct data_b {
    char *title; // A könyv címe
    char *author; // A könyv szerzője
    char *publisher; // A könyv kiadója
    char *isbn; // A könyv ISBN száma
    char *borrowed; // A kikölcsönzés státusza: üres string/egyetlen newline-t tartalmaz ha nincs kikölcsönözve, ha pedig kivan, a kikölcsönző olvasószámát.
    char *library_number; // A könyvtári rendszerben saját "házon belüli" azonosítószám helye. 
    char *genres; // A könyv műfajai, KISBETŰVEL - a keresőfüggvény nem case-szenzitív, tehát ha nagybetűvel van beírva a file-ba a műfaj, nem fogja a felhasználónak megtalálni!!
} data_b;

// A lista egy elemét definiáló struktúra
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


blist create_blist(void); // Létrehoz egy inicializást üres listát - a head és tail strázsát. A két strázsa adatmezője ki van nullázva NULL pointerekkel. 
void dispose_blist(blist l); // Törli a teljes listát a memóriából.
int get_data_b(blist book_list, FILE *fb); // Egy megnyitott fb filepointerből beolvassa az adatokat a listába. Semmilyen szempontból nincsennek rendezve az adatok, az először beolvasott elem lesz az utolsó, az utoljára beolvasott elem lesz az első a listában
data_b concatenate_to_data_b(char *title, char *author, char *publisher, char *isbn, char *borrowed, char *library_number, char *genres); // Összefoglalja a paramétereként kapott adatokat egy data_b struktúrába.
int insert_between_b(book_list_ptr prev, book_list_ptr next, data_b book); // A listába bárhova be tud szúrni elemet. Nem ellenőrzi, hogy érvényes-e a prev, és next pointer, tehát abban az esetben is használható lenne, ha nem teljesen így nézne ki a lista struktúrája.
void search_for_author(blist books, char *author); // Paraméterként megkapott értékre keres kis és nagybetűt megkülönböztetve a könyvek szerzői között. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void search_for_genre(blist books, char *genre); // Paraméterként megkapott értékre keres kis és nagybetűt megkülönböztetve a könyvek stílusában. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void search_for_title(blist books, char *title); // Paraméterként megkapott értékekre keres kis és nagybetűt megkülönböztetve a könyvek címei között. Listáz minden olyan találatot ahol a keresési paraméter teljesen megtaláltató, nem csak teljes egyezés esetén ad eredményt.
void print_book(data_b book); // Egyetlen paraméterként megkapott data_b stuktúra minden elemét kidobja az stdio-ra.
void del_last_newline_from_structure_b(data_b book); // Törli a paraméterként kapott struktúra utolsó elemét, ha az newline ('\n') karakter. Ciklussal, nem rekurzióval működik. 

search_function_ptr search_for_author_ptr = search_for_author;
search_function_ptr search_for_genre_ptr = search_for_genre;
search_function_ptr search_for_title_ptr = search_for_title;

#endif
