#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "config.h"
#include "customers.h"
#include "functions.h"

typedef struct data_c {
    char *name;
    char *id;
    char *debt;
} data_c;

typedef struct customer_list_element {
    data_c customer;
    struct customer_list_element *next, *prev;
} customer_list_element, *customer_list_ptr;

typedef struct {
    customer_list_element *head;
    customer_list_element *tail;
} clist, *clist_ptr;

clist create_clist(void);
void dispose_clist(clist l);
int get_data_c(clist customer_list, FILE *fc);
data_c concatenate_to_data_c(char *name, char *id, char *debt);
void insert_between_c(customer_list_ptr prev, customer_list_ptr next, data_c customer);
void search_for_name(clist customers, char *name);
void search_for_id(clist customers, char *id);
void search_for_debt(clist customers, char *debt);

#endif
