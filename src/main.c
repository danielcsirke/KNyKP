    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "books.h"
    #include "customers.h"
    #include "functions.h"
    #include "config.h"



    int main(void)
    {
        // A parancssor tisztítása
        clear_screen();
        // A listák létrehozása - kétszeresen láncolt strázsás listák.
        clist customers = create_clist();
        blist books = create_blist();

        // A file-ok neveinek bekérése
        char books_file_name[4096], customer_file_name[4096];
        printf("Kérem adja meg az embereket tartalmazó file elérési útját!\n");
        scanf("%4095s", customer_file_name);
        printf("Kérem adja meg a könyveket tartalmazó file elérési útját!\n");
        scanf("%4095s", books_file_name);

        // A file-ok megnyitása
        FILE *fc = NULL, *fb = NULL;
        if (open_files(customer_file_name, books_file_name, &fc, &fb)) {
            perror("Nem sikerült megnyitni az egyik szükséges file-t");
            printf("A hiba miatt a program bezáródik!\n");
            dispose_blist(books);
            dispose_clist(customers);
            return -1;
        }

        // Beolvasás a file-okba.
        if (get_data_c(customers, fc) != 0){
            dispose_blist(books);
            dispose_clist(customers);
            close_files(&fc, &fb);
            printf("A hiba miatt a program bezáródik!\n");
            return -1;
        }

        if (get_data_b(books, fb) != 0){
            dispose_blist(books);
            dispose_clist(customers);
            close_files(&fc, &fb);
            printf("A hiba miatt a program bezáródik!\n");
            return -1;
        }

        // A file-ok bezárása.
        close_files(&fc, &fb);

        // Változó létrehozása a felhasználó választásához.
        int choice;
        do{
            // A menü kiíratása.
            print_menu();

            // A felhasználó megkérdezése mit akar csinálni
            if (scanf("%d", &choice) != 1) {
                printf("Érvénytelen opció! Kérem adjon meg egy számot a fent felsorolt opciók közül!");
                clear_input();
                // Érvénytelen érték adása a choice változónak. 
                choice = -1;
                continue;
            }

            // A felhasználó választásának kezelése
            switch(choice) {
                case 0: 
                    printf("Köszönjük, hogy használta a programot! Viszontlátásra!\n"); 
                    dispose_clist(customers);
                    dispose_blist(books);
                    exit(0);
                case 1: perform_search(search_for_name_ptr, (void*)&customers); break;
                case 2: perform_search(search_for_id_ptr, (void*)&customers); break;
                case 3: perform_search(search_for_debt_ptr, (void*)&customers); break;
                case 4: perform_search(search_for_title_ptr, (void*)&books); break;
                case 5: perform_search(search_for_author_ptr, (void*)&books); break;
                case 6: perform_search(search_for_genre_ptr, (void*)&books); break;
                default: 
                    printf("Érvénytelen opció! Próbálja újra!\n");
                    clear_input();
                    continue;
            }
            clear_input();
            printf("Szeretne másik keresést indítani?\nNyomjon 1-et új keresés indításához, 0-t kilépéshez.\n");
            scanf("%d", &choice);
            if (!choice){
                printf("Köszönjük, hogy használta a programot! Viszontlátásra!\n");
                break;
            }
            continue;
        }while(choice != 0);

        // A listák felszabadítása. 
        dispose_clist(customers);
        dispose_blist(books);

        return 0;
    }
