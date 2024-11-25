#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>


void close_files(FILE **fc, FILE **fb);
int open_files(char *file_c, char *file_b, FILE **fc, FILE **fb);

#endif
