#ifndef COURSEWORK_TABLE_H
#define COURSEWORK_TABLE_H
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

struct Table {
    char* name;
    struct LinkedList* rows;
    struct LinkedList* cellLengths;
};

struct Table* tbl_new(char* name);
unsigned int tbl_height(struct Table* t);
unsigned int tbl_width(struct Table* t);
void tbl_append(struct Table* t, unsigned int num, ...);
void tbl_append_arr(struct Table* t, unsigned int num, char** cells);
void tbl_print(struct Table* t);
void tbl_destroy(struct Table* t);

#endif //COURSEWORK_TABLE_H