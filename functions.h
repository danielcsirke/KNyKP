#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef void (*search_function_ptr)(void *list, char* key);

int open_files(char *file_c, char *file_b, FILE **fc, FILE **fb); // Megnyitja a paraméterként kapott filenevű file-okat.
void close_files(FILE **fc, FILE **fb); // A megnyitott két file-t bezárja. 
void del_last_newline(char *str); // A beolvasás során fgets() függvény által bekért utolsó newline karaktereket eltávolítja. 
void clear_input_stream(FILE *stream); // Mivel a c szabványban a fflush(stdin) nincs definiálva (forrás: cppreference.com) ezért 
void clear_screen(void); // A parancssori kiírt infók törlés a jobb kinézet érdekében
void perform_search(search_function_ptr search_function, void *list);


#endif
