#ifndef COURSEWORK_LINKEDLIST_H
#define COURSEWORK_LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct LinkedListElement {
    struct LinkedListElement* prev;
    struct LinkedListElement* next;

    void* data;
};

struct LinkedList {
    struct LinkedListElement* begin;
    struct LinkedListElement* end;
    unsigned int size;
};

struct LinkedList* ll_new();
unsigned int ll_size(struct LinkedList* ll);
bool ll_empty(struct LinkedList* ll);
void ll_append(struct LinkedList* ll, void* data);
void ll_destroy(struct LinkedList* ll);
void* ll_get(struct LinkedList* ll, int index);
void ll_set(struct LinkedList* ll, int index, void* data);

#endif //COURSEWORK_LINKEDLIST_H