#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "functions.h"
#include "config.h"


// A függvénypointerek értékadása. Deklaráció a books.h file-ban.
search_function_ptr search_for_author_ptr = search_for_author;
search_function_ptr search_for_genre_ptr = search_for_genre;
search_function_ptr search_for_title_ptr = search_for_title;


// Létrehozza a könyveket tartalmazó lista alapvető struktúráját (head és tail elemekkel).
blist create_blist(void)
{
    // Memóriafoglalás a lista fejének.
    blist l;
    l.head = malloc(sizeof(book_list_element));

    if (!l.head) { 
        // Ha a memóriafoglalás sikertelen, hibaüzenetet ír ki.
        perror("Nem sikerült memóriát foglalni a könyveket tartalmazó lista feltöltése során");

        return (blist){NULL, NULL};
    }

    // Memóriafoglalás a lista végének.
    l.tail = malloc(sizeof(book_list_element));
    if (!l.tail) {
        // Ha a tail foglalása sikertelen, a már lefoglalt head-et felszabadítjuk.
        perror("Nem sikerült memóriát foglalni a könyveket tartalmazó lista feltöltése során");
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

        // A struktúrákon belül tárolt stringek felszabadítása.
        free(temp->book.title);
        free(temp->book.author);
        free(temp->book.publisher);
        free(temp->book.isbn);
        free(temp->book.borrowed);
        free(temp->book.library_number);
        free(temp->book.genres);

        // A listaelem felszabadítása
        free(temp);
    }

    // A head és tail elemek felszabadítása.
    // Itt nem kell a head és tail elemekben lévő "hasznos" adatrészen lévő pointerekkel foglalkozni, mivel azok a létrehozó függvényben már NULL pointerré voltak átírva.
    free(l.head);
    free(l.tail);

    // A későbbi véletlen felhasználás megakadályozása érdekében a pointerek értékét NULL-ra változtatjuk. 
    l.head = NULL;
    l.tail = NULL;
}

// Egy book struktúrából törli a stringek utolsó karakterét, ha az újsor ('\n') karakter.
void del_last_newline_from_structure_b(data_b book)
{
    // A kapott pointerek ellenőrzése, ha hibás akkor a függvényből való kilépés.
    if (!book.title || !book.author || !book.publisher || !book.isbn || !book.borrowed || !book.library_number || !book.genres) {
        perror("Az újsor karakterek ('\\n') törlése nem sikerült");

        return;
    }

    // A törlés művelete stringenként.
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
    // A paraméterként kapott pointer ellenőrzése, hogy tényleg megfelő-e. 
    if (!fb) {
        // Hibaüzenet, ha hibás filepointert kapott a függvény. 
        perror("Nem sikerült a könyvek file-jának beolvasása");

        return -1;
    }

    // Ideiglenes változók a file-ból olvasott adatok tárolására.
    char temp_title[INPUT_BUFFER], temp_author[INPUT_BUFFER], temp_publisher[INPUT_BUFFER], temp_isbn[INPUT_BUFFER], temp_borrowed[INPUT_BUFFER], temp_library_number[INPUT_BUFFER], temp_genres[INPUT_BUFFER];

    // Beolvasás soronként, amíg minden adatot sikeresen olvasunk.
    while (fgets(temp_title, INPUT_BUFFER, fb) != NULL && fgets(temp_author, INPUT_BUFFER, fb) != NULL && fgets(temp_publisher, INPUT_BUFFER, fb) != NULL && fgets(temp_isbn, INPUT_BUFFER, fb) != NULL && fgets(temp_borrowed, INPUT_BUFFER, fb) != NULL && fgets(temp_library_number, INPUT_BUFFER, fb) != NULL && fgets(temp_genres, INPUT_BUFFER, fb) != NULL) {
        // Az olvasott adatok összefűzése egy könyvadat-struktúrába.
        data_b book = concatenate_to_data_b(temp_title, temp_author, temp_publisher, temp_isbn, temp_borrowed, temp_library_number, temp_genres);

        // Az összefűzés sikerességének ellenőrzése.
        if (!book.title || !book.author || !book.publisher || !book.isbn || !book.borrowed || !book.library_number || !book.genres) {
            perror("Az adatok másolása nem sikerült a könyvek listájában");

            return -1;
        }

        // Az utolsó newline karakterek törlése a struktúrából. 
        del_last_newline_from_structure_b(book);

        // Az összefűzött adatok hozzáadása a listához.
        if (insert_between_b(book_list.head, book_list.head->next, book) != 0)
            return -1;
    }

    return 0;
}

// Az olvasott karakterláncokat összefűzi egy könyv-adatstruktúrába.
data_b concatenate_to_data_b(char *title, char *author, char *publisher, char *isbn, char *borrowed, char *library_number, char *genres)
{
    data_b book;

    // A struktúra feltöltése adatokkal.
    book.title = strdup(title);
    book.author = strdup(author);
    book.publisher = strdup(publisher);
    book.isbn = strdup(isbn);
    book.borrowed = strdup(borrowed);
    book.library_number = strdup(library_number);
    book.genres = strdup(genres);

    // A strdup függvény NULL pointert ad vissza, ha nem sikerült memóriát foglalnia. Ebben az esetben egy teljesen üres struktúrát adok vissza, hogy jelezzem, baj történt. 
    if (!book.title || !book.author || !book.publisher || !book.isbn || !book.borrowed || !book.library_number || !book.genres)
        return (data_b){NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    return book;
}

// Új könyvlistaelem beszúrása két meglévő elem közé.
int insert_between_b(book_list_ptr prev, book_list_ptr next, data_b book)
{
    // Memóriafoglalás az új elemhez.
    book_list_ptr p = malloc(sizeof(book_list_element));

    // Memóriafoglalás ellenőrzése, hogy sikeres-e.
    if (!p) {
        perror("Nem sikerült memóriát foglalni a könyveket tartalmazó listába beszúrás során");

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
    // Ellenőrzöm, hogy érvényes pointereket kaptam-e hogy ne történjen segfault a printf miatt.
    if (!book.title || !book.author || !book.publisher || !book.isbn || !book.borrowed || !book.library_number || !book.genres) {
        perror("Nullpointer a struktúra valamely elemében! Nem írható ki");

        return;
    }

    // Adatok kiíratása megfelelő pointerek esetén.
    printf("Cím: %s\n", book.title);
    printf("Író: %s\n", book.author);
    printf("Kiadó: %s\n", book.publisher);
    printf("ISBN: %s\n", book.isbn);
    if (strcmp("", book.borrowed) == 0)
        printf("Kölcsönzés állapota: Nincs kikölcsönözve\n");
    else 
        printf("Ki van kölcsönözve, a kölcsönző azonosító száma: %s\n", book.borrowed);
    printf("Könyvtári azonosító: %s\n", book.library_number);
    printf("Műfaj: %s\n\n", book.genres);
}

// Az összes olyan könyv keresése, amelynek szerzője tartalmazza a megadott karakterláncot. Nem mindegy a nagy és kisbetűk használata.
void search_for_author(void *list_of_books, char *author)
{   
    // A függvény helyes működéséhez típuskonverzió 
    blist *books = (blist*)list_of_books;

    // A pointerek leelenőrzése a segfault elkerülése érdekében. 
    if (!author) {
        perror("Hibás keresési kulcs (NULL pointer)");

        return;
    }

    book_list_ptr p = books->head->next;

    while (p != books->tail) {
        if (strstr(p->book.author, author))
            print_book(p->book);
        p = p->next;
    }
}

// Az összes olyan könyv keresése, amelynek műfaja tartalmazza a megadott karakterláncot. Nem mindegy a nagy és kisbetűk használata.
void search_for_genre(void *list_of_books, char *genre)
{
    // A függvény helyes működéséhez típuskonverzió
    blist *books = (blist*)list_of_books;

    // A pointerek leelenőrzése a segfault elkerülése érdekében.
    if (!genre) {
        perror("Hibás keresési kulcs (NULL pointer)");

        return;
    }

    book_list_ptr p = books->head->next;

    while (p != books->tail) {
        if (strstr(p->book.genres, genre))
            print_book(p->book);
        p = p->next;
    }
}

// Az összes olyan könyv keresése, amelynek címe tartalmazza a megadott karakterláncot. Nem mindegy a nagy és kisbetűk használata.
void search_for_title(void *list_of_books, char *title)
{
    // A függvény helyes működéséhez típuskonverzió
    blist *books = (blist*)list_of_books;

    // A pointerek leelenőrzése a segfault elkerülése érdekében.
    if (!title) {
        perror("Hibás keresési kulcs (NULL pointer)");

        return;
    }

    book_list_ptr p = books->head->next;

    while (p != books->tail) {
        if (strstr(p->book.title, title))
            print_book(p->book);
        p = p->next;
    }
}

