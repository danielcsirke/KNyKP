#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdio.h>


int open_files(char *file_c, char *file_b, FILE **fc, FILE **fb); // Megnyitja a paraméterként kapott filenevű file-okat.
void close_files(FILE **fc, FILE **fb); // A megnyitott két file-t bezárja. 
void del_last_newline(char *str); // A beolvasás során fgets() függvény által bekért utolsó newline karaktereket eltávolítja. 


#endif
