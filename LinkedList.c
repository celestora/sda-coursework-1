#include "LinkedList.h"

struct LinkedList* ll_new() {
    struct LinkedList* ll = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    ll->begin = NULL;
    ll->end   = NULL;
    ll->size  = 0;

    return ll;
}

unsigned int ll_size(struct LinkedList* ll) {
    return ll->size;
}

bool ll_empty(struct LinkedList* ll) {
    return ll_size(ll) == 0;
}

void ll_append(struct LinkedList* ll, void* data) {
    struct LinkedListElement* element = (struct LinkedListElement*) malloc(sizeof(struct LinkedListElement));
    element->data = data;
    element->next = NULL;

    if(ll_empty(ll)) {
        element->prev = NULL;
        ll->begin     = element;
        ll->end       = element;
    } else {
        struct LinkedListElement *last = ll->end;
        element->prev = last;
        last->next    = ll->end = element;
    }

    ll->size++;
}

void ll_destroy(struct LinkedList* ll) {
    struct LinkedListElement* el = ll->end;
    while(true) {
        struct LinkedListElement* prev = el->prev;
        free(el->data);
        free(el);

        if(prev == NULL)
            break;
        else
            el = prev;
    }

    free(ll);
}

struct LinkedListElement* priv_ll_get_internal(struct LinkedList* ll, int index) {
    if(index < 0) {
        index = ll_size(ll) + index - 1;
        if(index < 0) {
            fprintf(stderr, "[LinkedList:priv_ll_get_internal] Index %d is out of range.\n");

            return NULL;
        }
    } else if (index >= ll_size(ll)) {
        fprintf(stderr, "[LinkedList:priv_ll_get_internal] Index %d is out of range.\n");

        return NULL;
    }

    struct LinkedListElement* el = ll->begin;
    for(int i = 0; i < index; i++)
        el = el->next;

    return el;
}

void* ll_get(struct LinkedList* ll, int index) {
    struct LinkedListElement* el = priv_ll_get_internal(ll, index);

    return el->data;
}

void ll_set(struct LinkedList *ll, int index, void* data) {
    struct LinkedListElement* el = priv_ll_get_internal(ll, index);
    el->data = data;
}