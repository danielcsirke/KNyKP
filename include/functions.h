#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>


// A függvénypointer típusdeklarációja.
typedef void (*search_function_ptr)(void *, char *);

// Megnyitja a paraméterként kapott filenevű file-okat.
int open_files(char *file_c, char *file_b, FILE **fc, FILE **fb); 

// A megnyitott két file-t bezárja. 
void close_files(FILE **fc, FILE **fb); 

// A beolvasás során fgets() függvény által bekért utolsó newline karaktereket eltávolítja. 
void del_last_newline(char *str); 

// A bemeneten lévő hibás karakterek törlésére alkalmas függvény.
void clear_input();

// A parancssori kiírt infók törlés a jobb kinézet érdekében
void clear_screen(void); 

// A keresést elvégző függvény - paraméterként kap egy függvénypointert, és egy listát
void perform_search(search_function_ptr search_function, void *list);
 
// A menüt kiírja az stdout-ra. 
void print_menu(void); 


#endif
