#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
#include "config.h"
#include "customers.h"
#include "functions.h"

void close_files(FILE **fc, FILE **fb)
{
    if (fc && *fc) fclose(*fc);
    if (fb && *fb) fclose(*fb);
}

int open_files(char *file_c, char *file_b, FILE **fc, FILE **fb)
{
    *fc = fopen(file_c, "r");
    if (!*fc) {
        fprintf(stderr, "Error opening customer file: %s\n", file_c);
        return 1;
    }
    *fb = fopen(file_b, "r");
    if (!*fb) {
        fprintf(stderr, "Error opening book file: %s\n", file_b);
        fclose(*fc);
        return 2;
    }
    return 0;
}
