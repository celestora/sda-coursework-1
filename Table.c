#include "Table.h"

struct Table* tbl_new(char* name) {
    struct Table* table = malloc(sizeof(struct Table));
    table->name        = name;
    table->rows        = ll_new();
    table->cellLengths = ll_new();

    return table;
}

unsigned int tbl_height(struct Table* t) {
    return ll_size(t->rows);
}

unsigned int tbl_width(struct Table* t) {
    return ll_size(t->cellLengths);
}

unsigned int priv_tbl_width_chars(struct Table* t) {
    unsigned int chars = 0;
    unsigned int width = tbl_width(t);
    for(int i = 0; i < width; i++)
        chars += *((unsigned int*) ll_get(t->cellLengths, i)) + 2;

    return chars + width + 1;
}

void tbl_append(struct Table* t, unsigned int num, ...) {
    va_list valist;

    va_start(valist, num);
    struct LinkedList* row = ll_new();
    for(int i = 0; i < num; i++) {
        char* cell = va_arg(valist, char*);
        unsigned int* cellSize = malloc(sizeof(unsigned int));
        *cellSize = strlen(cell);
        if((i + 1) > ll_size(t->cellLengths)) {
            ll_append(t->cellLengths, cellSize);
        } else {
            unsigned int* currentColumnSize = ll_get(t->cellLengths, i);
            if(*cellSize > *currentColumnSize)
                ll_set(t->cellLengths, i, cellSize);
        }

        ll_append(row, cell);
    }

    ll_append(t->rows, row);
    va_end(valist);
}

void tbl_append_arr(struct Table* t, unsigned int num, char** cells) {
    struct LinkedList* row = ll_new();
    for(int i = 0; i < num; i++) {
        char* cell = cells[i];
        unsigned int* cellSize = malloc(sizeof(unsigned int));
        *cellSize = strlen(cell);
        if((i + 1) > ll_size(t->cellLengths)) {
            ll_append(t->cellLengths, cellSize);
        } else {
            unsigned int* currentColumnSize = ll_get(t->cellLengths, i);
            if(*cellSize > *currentColumnSize)
                ll_set(t->cellLengths, i, cellSize);
        }

        ll_append(row, cell);
    }

    ll_append(t->rows, row);
}

void priv_tbl_print_header(struct Table* t) {
    printf("╔");
    unsigned int chars = priv_tbl_width_chars(t) - 2;
    for(int i = 0; i < chars; i++)
        printf("═");

    printf("╗\n║");
    unsigned int spaces = (chars - strlen(t->name)) / 2;
    for(int i = 0; i < spaces; i++)
        putchar(' ');

    printf("%s", t->name);
    for(int i = 0; i < (spaces + (strlen(t->name) % 2 == 0 ? 1 : 0)); i++)
        putchar(' ');

    printf("║\n╠");
    unsigned int width = tbl_width(t);
    for(int i = 0; i < width; i++) {
        unsigned int hyphens = *((unsigned int*) ll_get(t->cellLengths, i)) + 2;
        for(int j = 0; j < hyphens; j++)
            printf("═");

        printf(i == (width - 1) ? "╣\n" : "╦");
    }
}

void priv_tbl_print_row(struct Table* t, struct LinkedList* row, bool closingBottom) {
    printf("║");

    unsigned int width  = tbl_width(t);
    for(int i = 0; i < width; i++) {
        char* cell = (char*) ll_get(row, i);
        unsigned int spaces = *((unsigned int*) ll_get(t->cellLengths, i)) - strlen(cell) + 1;
        for(int j = 0; j < spaces; j++)
            putchar(' ');

        printf("%s ║", cell);
    }

    printf("\n%s", closingBottom ? "╚" : "╠");
    for(int i = 0; i < width; i++) {
        unsigned int hyphens = *((unsigned int*) ll_get(t->cellLengths, i)) + 2;
        for(int j = 0; j < hyphens; j++)
            printf("═");

        if(i < width - 1)
            printf(closingBottom ? "╩" : "╬");
    }

    printf(closingBottom ? "╝" : "╣\n");
}

void tbl_print(struct Table* t) {
    priv_tbl_print_header(t);

    unsigned int height = tbl_height(t);
    for(int i = 0; i < height; i++) {
        struct LinkedList* row = ll_get(t->rows, i);
        priv_tbl_print_row(t, row, i == (height - 1) ? true : false);
    }

    printf("\n");
}

void tbl_destroy(struct Table* t) {
    ll_destroy(t->cellLengths);
    ll_destroy(t->rows);
    free(t);
}