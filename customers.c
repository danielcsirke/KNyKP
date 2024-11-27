#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customers.h"
#include "functions.h"
#include "config.h"

// A függvénypointerek értékadása. Deklaráció a books.h file-ban.
search_function_ptr search_for_name_ptr = search_for_name;
search_function_ptr search_for_id_ptr = search_for_id;
search_function_ptr search_for_debt_ptr = search_for_debt;

// Létrehozza az embereket tartalmazó láncolt lista alapvető struktúráját (strázsákkal (head, tail)).
clist create_clist(void)
{
    // Memóriafoglalás a lista fejének.
    clist l;
    l.head = malloc(sizeof(customer_list_element));

    if (!l.head){
        // Ha a memóriafoglalás sikertelen, hibaüzenetet ír ki.
        perror("Nem sikerült memóriát foglalni az embereket tartalmazó lista feltöltése során");

        return (clist){NULL, NULL};
    }

    // Memóriafoglalás a lista végének. 
    l.tail = malloc(sizeof(customer_list_element));
    if (!l.tail) {
        // Ha a tail foglalása sikertelen, a már lefoglalt head-et felszabadítjuk.
        perror("Nem sikerült memóriát foglalni az embereket tartalmazó lista feltöltése során");
        free(l.head);

        return (clist){NULL, NULL};
    }

    // A head és tail elemek inicializálása.
    l.head->next = l.tail;
    l.head->prev = NULL;
    l.tail->prev = l.head;
    l.tail->next = NULL;

    return l;
}

// A listát felszabadító függvény.
void dispose_clist(clist l)
{
    customer_list_ptr p = l.head->next;
    while (p != l.tail) {
        // Az aktuális elem felszabadítása, majd lépés a következőre.
        customer_list_ptr temp = p;
        p = p->next;

        // A struktúrán belül tárolt stringek felszabadítása. 
        free(temp->customer.name);
        free(temp->customer.id);
        free(temp->customer.debt);

        // A listaelem felszabadítása.
        free(temp);
    }

    // A head és tail elemek felszabadítása.
    // Itt nem kell a head és tail elemekben lévő "hasznos", adatrészeken lévő pointerekkel bajlódni, mivel az őket létrehozó függvény már NULL pointerrel inicializálta azon részeket. 
    free(l.head);
    free(l.tail);

    // A későbbi véletlen felhasználás megakadályozása érdekében a pointerek értékét NULL-ra állítom.
    l.head = NULL;
    l.tail = NULL;

}

void del_last_newline_from_structure_c(data_c customer)
{
    // A kapott pointerek ellenőrzése, ha hibás, akkor a függvényből való kilépés.
    if (!customer.name || !customer.id || !customer.debt) {
        perror("Az újsor karakterek ('\\n') törlése nem sikerült");

        return;
    }

    // A törlés művelete stringenként.
    del_last_newline(customer.name);
    del_last_newline(customer.id);
    del_last_newline(customer.debt);
}

// Adatok beolvasása egy file-ból, és azok hozzáadása a könyvlistához. 
int get_data_c(clist customer_list, FILE *fc)
{
    //A paraméterként kapott pointer ellenőrzése, hogy tényleg megfelelő-e.
    if (!fc) {
        // Hibaüzenet, ha hibás filepointert kapott a függvény.
        perror("Nem sikerült az emberek file-jának beolvasása");

        return -1;
    }

    // Ideiglenes változók a file-ból olvasott adatok tárolására.
    char temp1[INPUT_BUFFER], temp2[INPUT_BUFFER], temp3[INPUT_BUFFER];

    // Beolvasás soronként, amíg minden adatot sikeresen olvasunk. 
    while (fgets(temp1, INPUT_BUFFER, fc) && fgets(temp2, INPUT_BUFFER, fc) && fgets(temp3, INPUT_BUFFER, fc)) {
        // Az olvasott adatok összefűzése egy könyvadat struktúrába. 
        data_c customer = concatenate_to_data_c(temp1, temp2, temp3);

        //Az összefűzés sikerességének ellenőrzése.
        if (!customer.name || !customer.id || !customer.debt) {
            perror("Az adatok másolása nem sikerült az emberek listájában");

            return -1;
        }

        // Az utolsó newline karakterek törlése a struktúrából. 
        del_last_newline_from_structure_c(customer);

        // Az összefűzött adatok hozzáadása a listához. 
        if(insert_between_c(customer_list.head, customer_list.head->next, customer) != 0)
            return -1;
    }

    return 0;
}

// Az olvasott karakterláncokat összefűzi egy könyv-adatstruktúrába. 
data_c concatenate_to_data_c(char *name, char *id, char *debt)
{
    data_c customer;

    // A struktúra feltöltése adatokkal.
    customer.name = strdup(name);
    customer.id = strdup(id);
    customer.debt = strdup(debt);

    // A strdup függvény NULL pointert ad vissza, ha nem sikerült memóriát foglalnia. Ebben az esetben egy teljesen üres struktúrát adok vissza, hogy jelezzem, baj történt. 
    if (!customer.name || !customer.id || !customer.debt)
        return (data_c){NULL, NULL, NULL};
    
    return customer;
}

// Új emberlistaelem beszúrása két meglévő elem közé.
int insert_between_c(customer_list_ptr prev, customer_list_ptr next, data_c customer)
{
    // Memóriafoglalás az új elemhez. 
    customer_list_ptr p = malloc(sizeof(customer_list_element));

    // Memóriafoglalás ellenőrzése, hogy sikeres-e. 
    if (!p) {
        perror("Nem sikerült memóriát foglalni az embereket tartalmazó listába beszúrás során");

        return -1;
    }

    // Az új elem feltöltése adatokkal, és a listához kapcsolása. 
    p->customer = customer;
    p->prev = prev;
    p->next = next;
    prev->next = p;
    next->prev = p;

    return 0;
}

// Egy olvasó adatainak kiíratása.
void print_customer(data_c customer)
{
    // Ellenőrzöm, hogy érvényes pointereket kaptam-e hogy ne történjen segfault a printf miatt.
    if (!customer.name || !customer.id || !customer.debt) {
        perror("Nullpointer a struktúra valamely elemében! Nem írható ki");

        return;
    }

    // Adatok kiíratása megfelelő pointerek esetén.
    printf("Név: %s\n", customer.name);
    printf("Azonosító: %s\n", customer.id);
    printf("Tartozás: %s ft\n\n", customer.debt);
}

// Az összes olyan ember keresése akinek a nevében megtalálható a megadott karakterlánc. 
void search_for_name(clist customers, char *name)
{
    if (!name) {
        perror("Hibás keresési kulcs (NULL pointer)");

        return;
    }

    customer_list_ptr p = customers.head->next;

    while (p != customers.tail) {
        if (strstr(p->customer.name, name))
            print_customer(p->customer);
        p = p->next;
    }
}

// Az összes olyan ember keresése, amelynek azonosítószáma tartalmazza a megadott karatkerláncot. 
void search_for_id(clist customers, char *id)
{
    // A pointerek leelenőrzése a segfault elkerülése érdekében.
    if (!id) {
        perror("Hibás keresési kulcs (NULL pointer)");

        return;
    }

    customer_list_ptr p = customers.head->next;

    while (p != customers.tail) {
        if (strstr(p->customer.id, id)) 
            print_customer(p->customer);
        p = p->next;
    }
}

// Az összes olyan ember keresése, akinek a tartozása megegyezik a megadott értékkel.
void search_for_debt(clist customers, char *debt)
{
    // A pointerek leelenőrzése a segfault elkerülése érdekében.
    if (!debt) {
        perror("Hibás keresési kulcs (NULL pointer)");

        return;
    }

    customer_list_ptr p = customers.head->next;

    while (p != customers.tail) {
        if (strcmp(p->customer.debt, debt) == 0)
            print_customer(p->customer);
        p = p->next;
    }
}


