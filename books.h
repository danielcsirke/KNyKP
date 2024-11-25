#ifndef BOOKS_H
#define BOOKS_H

typedef struct data_b {
    char *title;
    char *author;
    char *publisher;
    char *isbn;
    char *borrowed;
    char *library_number;
    char *genres;
} data_b;

typedef struct book_list_element {
    data_b book;
    struct book_list_element *next, *prev;
} book_list_element, *book_list_ptr;

typedef struct {
    book_list_element *head;
    book_list_element *tail;
} blist, *blist_ptr;

blist create_blist(void);
void dispose_blist(blist l);
int get_data_b(blist book_list, FILE *fb);
data_b concatenate_to_data_b(char *title, char *author, char *publisher, char *isbn, char *borrowed, char *library_number, char *genres);
int insert_between_b(book_list_ptr prev, book_list_ptr next, data_b book);
void search_for_author(blist books, char *author);
void search_for_genre(blist books, char *genre);
void search_for_title(blist books, char *title);
void print_book(data_b book);


#endif
