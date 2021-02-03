#include <stdlib.h>

#include "numberstack.h"
#include "global.h"


numberstack* numbers;


// Allocate and set up numberstack
numberstack * create_numberstack(int max_size) {

    numberstack* s;
    if (!(s = malloc(sizeof (numberstack)))) 
        exit_pcalc(0xa0);

    if (!(s->elements = malloc(max_size * sizeof(long long)))) 
        exit_pcalc(0xa1);

    s->size = 0;
    s->max_size = max_size;
    return s;
}

static numberstack * resize_numberstack(numberstack* s) {

    s->max_size *= 2;

    void *srealloc;
    if ((srealloc = realloc(s->elements, s->max_size * sizeof(long long))))
        s->elements = srealloc;
    else
        return NULL;

    return s;

}

// Pop element from the top of the stack (return and remove element)
long long * pop_numberstack(numberstack* s) {

    if (s->size == 0)
        return NULL;

    return &s->elements[--s->size];
}

// Return the element at the top of the stack without removing it
long long * top_numberstack(numberstack* s) {

    if (s->size == 0)
        return NULL;

    return &s->elements[s->size-1];
}

// Push number to the top of the stack
void push_numberstack(numberstack* s, long long value) {

    if (s->size == s->max_size)
        if (!resize_numberstack(s))
            exit_pcalc(0xa2);

    s->elements[s->size++] = value;
}

// Clear the stack
void clear_numberstack(numberstack* s) {

    s->size = 0;
}

void free_numberstack(numberstack *s) {

    free(s->elements);
    free(s);

}
