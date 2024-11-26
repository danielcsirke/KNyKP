#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "functions.h"
#include "config.h"

// Létrehozza a könyvlista alapvető struktúráját (head és tail elemekkel).
blist create_blist(void)
{
    // Memóriafoglalás a lista fejének.
    blist l;
    l.head = malloc(sizeof(book_list_element));
    if (!l.head){ 
        // Ha a memóriafoglalás sikertelen, hibaüzenetet ír ki.
        perror("Hiba memóriafoglalás közben a create_blist() függvényben");
        return (blist){NULL, NULL};
    }
    // Memóriafoglalás a lista végének.
    l.tail = malloc(sizeof(book_list_element));
    if (!l.tail) {
        // Ha a tail foglalása sikertelen, a már lefoglalt head-et felszabadítjuk.
        perror("Hiba memóriafoglalás közben a create_blist() függvényben");
        free(l.head);
        return (blist){NULL, NULL};
    }
    // A head és tail elemek inicializálása.
    l.head->book = (data_b){NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    l.head->next = l.tail;
    l.head->prev = NULL;
    l.tail->book = (data_b){NULL, NULL, NULL, NULL, NULL, NULL, NULL};
    l.tail->prev = l.head;
    l.tail->next = NULL;
    return l;
}

// A listát felszabadító függvény.
void dispose_blist(blist l)
{
    book_list_ptr p = l.head->next;
    while (p != l.tail) {
        // Az aktuális elem felszabadítása, majd lépés a következőre.
        book_list_ptr temp = p;
        p = p->next;
        free(temp);
    }
    // A head és tail elemek felszabadítása.
    free(l.head);
    free(l.tail);
    l.head = NULL;
    l.tail = NULL;
}

void del_last_newline_from_structure_b(data_b book)
{
        del_last_newline(book.title);
        del_last_newline(book.author);
        del_last_newline(book.publisher);
        del_last_newline(book.isbn);
        del_last_newline(book.borrowed);
        del_last_newline(book.library_number);
        del_last_newline(book.genres);
}

// Adatok beolvasása egy file-ból, és azok hozzáadása a könyvlistához.
int get_data_b(blist book_list, FILE *fb)
{
    if (!fb) {
        // Hibaüzenet, ha hibás filepointert kapott a függvény. 
        perror("Nem sikerült a könyvek file-jának beolvasása");
        return -1;
    }
    // Ideiglenes változók a fájlból olvasott adatok tárolására.
    char temp_title[INPUT_BUFFER], temp_author[INPUT_BUFFER], temp_publisher[INPUT_BUFFER], temp_isbn[INPUT_BUFFER], temp_borrowed[INPUT_BUFFER], temp_library_number[INPUT_BUFFER], temp_genres[INPUT_BUFFER];
    // Beolvasás soronként, amíg minden adatot sikeresen olvasunk.
    while (fgets(temp_title, INPUT_BUFFER, fb) != NULL && fgets(temp_author, INPUT_BUFFER, fb) != NULL && fgets(temp_publisher, INPUT_BUFFER, fb) != NULL && fgets(temp_isbn, INPUT_BUFFER, fb) != NULL && fgets(temp_borrowed, INPUT_BUFFER, fb) != NULL && fgets(temp_library_number, INPUT_BUFFER, fb) != NULL && fgets(temp_genres, INPUT_BUFFER, fb) != NULL) {
        // Az olvasott adatok összefűzése egy könyvadat-struktúrába.
        data_b book = concatenate_to_data_b(temp_title, temp_author, temp_publisher, temp_isbn, temp_borrowed, temp_library_number, temp_genres);
        // Az utolsó newline karakterek törlése a fileból. 
        del_last_newline_from_structure_b(book);
        // Az összefűzött adatok hozzáadása a listához.
        if (insert_between_b(book_list.head, book_list.head->next, book) != 0) {
            perror("Hiba a get_data_b() függvényben, az insert_between() függvény hibát adott");
            return -1;
        }
    }
    return 0;
}

// Az olvasott karakterláncokat összefűzi egy könyv-adatstruktúrába.
data_b concatenate_to_data_b(char *title, char *author, char *publisher, char *isbn, char *borrowed, char *library_number, char *genres)
{
    data_b book;
    // A struktúra feltöltése adatokkal.
    book.title = title;
    book.author = author;
    book.publisher = publisher;
    book.isbn = isbn;
    book.borrowed = borrowed;
    book.library_number = library_number;
    book.genres = genres;
    return book;
}

// Új könyvlista elem beszúrása két meglévő elem közé.
int insert_between_b(book_list_ptr prev, book_list_ptr next, data_b book)
{
    // Memóriafoglalás az új elemhez.
    book_list_ptr p = malloc(sizeof(book_list_element));
    if (!p){
        perror("Hibás file pointer az insert_between_b() függvényben");
        return -1;
    }
    // Az új elem feltöltése adatokkal, és a listához kapcsolása.
    p->book = book;
    p->prev = prev;
    p->next = next;
    prev->next = p;
    next->prev = p;
    return 0;
}

// Egy könyv adatainak kiíratása.
void print_book(data_b book)
{
    printf("Cím: %s\nÍró: %s\nKiadó: %s\nISBN: %s\nKölcsönzés állapota: %s\nKönyvtári azonosító: %s\nMűfaj: %s\n\n", book.title, book.author, book.publisher, book.isbn, book.borrowed, book.library_number, book.genres);
}

// Az összes olyan könyv keresése, amelynek szerzője tartalmazza a megadott karakterláncot. Nem mindegy a nagy és kisbetűk használata.
void search_for_author(blist books, char *author)
{
    book_list_ptr p = books.head->next;
    while (p != books.tail) {
        if (strstr(p->book.author, author))
            print_book(p->book);
        p = p->next;
    }
}

// Az összes olyan könyv keresése, amelynek műfaja tartalmazza a megadott karakterláncot. Nem mindegy a nagy és kisbetűk használata.
void search_for_genre(blist books, char *genre)
{
    book_list_ptr p = books.head->next;
    while (p != books.tail) {
        if (strstr(p->book.genres, genre))
            print_book(p->book);
        p = p->next;
    }
}

// Az összes olyan könyv keresése, amelynek címe tartalmazza a megadott karakterláncot. Nem mindegy a nagy és kisbetűk használata.
void search_for_title(blist books, char *title)
{
    book_list_ptr p = books.head->next;
    while (p != books.tail) {
        if (strstr(p->book.title, title))
            print_book(p->book);
        p = p->next;
    }
}

