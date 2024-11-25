#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "config.h"
#include "customers.h"
#include "functions.h"

clist create_clist(void)
{
    clist l;
    l.head = malloc(sizeof(customer_list_element));
    if (!l.head) return (clist){NULL, NULL};
    l.tail = malloc(sizeof(customer_list_element));
    if (!l.tail) {
        free(l.head);
        return (clist){NULL, NULL};
    }
    l.head->next = l.tail;
    l.head->prev = NULL;
    l.tail->prev = l.head;
    l.tail->next = NULL;
    return l;
}

void dispose_clist(clist l)
{
    customer_list_ptr p = l.head->next;
    while (p != l.tail) {
        customer_list_ptr temp = p;
        p = p->next;
        free(temp);
    }
    free(l.head);
    free(l.tail);
}

int get_data_c(clist customer_list, FILE *fc)
{
    char temp1[INPUT_BUFFER], temp2[INPUT_BUFFER], temp3[INPUT_BUFFER];
    while (fgets(temp1, INPUT_BUFFER, fc) && fgets(temp2, INPUT_BUFFER, fc) && fgets(temp3, INPUT_BUFFER, fc)) {
        data_c customer = concatenate_to_data_c(temp1, temp2, temp3);
        insert_between_c(customer_list.head, customer_list.head->next, customer);
    }
    return 0;
}

data_c concatenate_to_data_c(char *name, char *id, char *debt)
{
    return (data_c){strdup(name), strdup(id), strdup(debt)};
}

void insert_between_c(customer_list_ptr prev, customer_list_ptr next, data_c customer)
{
    customer_list_ptr new_element = malloc(sizeof(customer_list_element));
    new_element->customer = customer;
    new_element->prev = prev;
    new_element->next = next;
    prev->next = new_element;
    next->prev = new_element;
}

void search_for_name(clist customers, char *name)
{
    customer_list_ptr p = customers.head->next;
    while (p != customers.tail) {
        if (strstr(p->customer.name, name)) {
            printf("Found Customer: %s, ID: %s, Debt: %s\n",
                   p->customer.name, p->customer.id, p->customer.debt);
        }
        p = p->next;
    }
}

void search_for_id(clist customers, char *id)
{
    customer_list_ptr p = customers.head->next;
    while (p != customers.tail) {
        if (strstr(p->customer.id, id)) {
            printf("Found Customer: %s, ID: %s, Debt: %s\n",
                   p->customer.name, p->customer.id, p->customer.debt);
        }
        p = p->next;
    }
}

void search_for_debt(clist customers, char *debt)
{
    customer_list_ptr p = customers.head->next;
    while (p != customers.tail) {
        if (strstr(p->customer.debt, debt)) {
            printf("Found Customer: %s, ID: %s, Debt: %s\n",
                   p->customer.name, p->customer.id, p->customer.debt);
        }
        p = p->next;
    }
}


