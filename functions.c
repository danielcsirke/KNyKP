#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

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
    int i = 0;

    // Bejárja a tömböt, hogy megtalálja, melyik az utolsó eleme.
    while(str[i] != '\0')
        i++;

    // Ha a tömb nem üres, akkor az utolsó karakterét kicseréli a lezáró null karakterre. 
    if (i > 0 && str[i-1] == '\n')
        str[i-1] = '\0'; 
}