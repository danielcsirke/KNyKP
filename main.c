#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "config.h"
#include "customers.h"
#include "functions.h"

int main(void)
{
    clist customers = create_clist();
    blist books = create_blist();

    FILE *fc = NULL, *fb = NULL;
    if (open_files("customers.txt", "books.txt", &fc, &fb)) {
        return 1;
    }

    get_data_c(customers, fc);
    get_data_b(books, fb);

    close_files(&fc, &fb);

char query[INPUT_BUFFER];
int choice;

printf("Library Search System:\n");
printf("Enter the corresponding number to perform a search, or '0' to quit:\n");

while (1) {
    printf("\nMenu:\n");
    printf("1. Search by Customer Name\n");
    printf("2. Search by Customer ID\n");
    printf("3. Search by Customer Debt\n");
    printf("4. Search by Book Author\n");
    printf("5. Search by Book Genre\n");
    printf("0. Exit\n");
    printf("> ");
    
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number.\n");
        while (getchar() != '\n'); // Clear invalid input
        continue;
    }
    
    if (choice == 0) {
        printf("Exiting the program. Goodbye!\n");
        break;
    }

    // Clear input buffer before taking string input
    while (getchar() != '\n'); 

    printf("Enter your query: ");
    if (!fgets(query, INPUT_BUFFER, stdin)) {
        fprintf(stderr, "Error reading input.\n");
        continue;
    }
    // Remove trailing newline character from fgets
    query[strcspn(query, "\n")] = '\0';

    switch (choice) {
    case 1:
        printf("\nSearching for Customer by Name: %s\n", query);
        search_for_name(customers, query);
        break;
    case 2:
        printf("\nSearching for Customer by ID: %s\n", query);
        search_for_id(customers, query);
        break;
    case 3:
        printf("\nSearching for Customer by Debt: %s\n", query);
        search_for_debt(customers, query);
        break;
    case 4:
        printf("\nSearching for Book by Author: %s\n", query);
        search_for_author(books, query);
        break;
    case 5:
        printf("\nSearching for Book by Genre: %s\n", query);
        search_for_genre(books, query);
        break;
    default:
        printf("Invalid option. Please select a valid menu number.\n");
    }
}


    dispose_clist(customers);
    dispose_blist(books);

    return 0;
}
