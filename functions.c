#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "config.h"

// Megnyitja a paraméterként kapott filenevű file-okat.
int open_files(char *file_c, char *file_b, FILE **fc, FILE **fb)
{
    *fc = fopen(file_c, "r");
    if (!*fc) {
        perror("Hiba az olvasók adatait tartalmazó file megnyitása esetében");
        return -1;
    }

    *fb = fopen(file_b, "r");
    if (!*fb) {
        perror("Hiba a könyveket tartalmazó file megnyitása közben");
        fclose(*fc);
        return -1;
    }

    return 0;
}

// A megnyitott két file-t bezárja. 
void close_files(FILE **fc, FILE **fb)
{
    if (fc != NULL) 
        fclose(*fc);

    if (fb != NULL) 
        fclose(*fb);
}

// A beolvasás során fgets() függvény által bekért utolsó newline karaktereket eltávolítja. 
void del_last_newline(char *str)
{
    // A kapott pointer ellenőrzése. 
    if (!str) 
        return;

    int i = 0;

    // Bejárja a tömböt, hogy megtalálja, melyik az utolsó eleme.
    while(str[i] != '\0')
        i++;

    // Ha a tömb nem üres, akkor az utolsó karakterét kicseréli a lezáró null karakterre. 
    if (i > 0 && str[i-1] == '\n')
        str[i-1] = '\0'; 
}

// A felhasználóval való kommunikációhoz szükséges menü kiíratása az kimenetre. 
void print_menu(void)
{
    printf("\n---- Menü ----\n");
    printf("--------------\n");
    printf("1. Keresés személy nevére\n");
    printf("2. Keresés személy azonosító számára\n");
    printf("3. Keresés adott összegű tartozáshoz tartozó személyre\n");
    printf("4. Keresés könyv címére\n");
    printf("5. Keresés könyv írójára\n");
    printf("6. Keresés stílusokra\n");
    printf("0. Kilépés\n");
    printf("--------------\n");
}

// A bemenet törlése - a fflush(stdin) csak kimeneti stream-eken működik, azért kell ehhez a módhoz folyamodni

void clear_input_stream(void)
{
    // Törli a paraméterként kapott file pointer helyen található adatokat. 
    char c;
    //while ((c = getchar()) != '\n' && c != EOF );
    while(scanf("%c",&c)==1);
}

// A parancssori eddig kiírt infók törlése a képernyőről
void clear_screen(void)
{
    int check;
    #ifdef _WIN32
        check = system("cls");
    #else
        check = system("clear");
    #endif

    if (check != 0)
        printf("A képernyő törlése nem sikerült! Folytatás...\n");
}

// A függvény egy általános keresési művelet végrehajtására szolgál.
// A keresési logikát egy függvénypointeren keresztül adjuk át. 
// Az adatokat egy általános pointerként kapja meg, amit majd a keresési műveletet megvalósító függvény fog értelmezni. 
void perform_search(search_function_ptr search_function, void *list)
{
    // Ideiglenes string létrehozása a keresési kulcs tárolására.
    char *temp = (char*)malloc(INPUT_BUFFER);

    if (!temp) {
        perror("Nem sikerült a memóriafoglalás a keresés közben");
        return;
    }

    // A keresési kulcs bekérése a felhasználótól.
    printf("Kérem adja meg a keresési kulcsot! Ügyeljen a kis- és nagybetűk helyes használatára!\n");

    if(fgets(temp, INPUT_BUFFER, stdin) == NULL) {
        perror("Nem sikerült olvasni a keresés során");
        free(temp);

        return;
    }

    // Eltávolítjuk az fgets által hozzáadot newline ('\n') karaktert
    del_last_newline(temp);

    printf("Adat keresése...\n");
    search_function(list, temp);

    free(temp);
}