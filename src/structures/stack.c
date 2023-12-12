#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Stack {
    struct st_item *top;
    int size;
} Stack;

typedef struct st_item {
    int x, y;
    struct st_item *next;
} st_item;

bool st_empty(Stack *st) {
    return st->size == 0;
}

void st_insert(Stack *st, int x, int y) {
    st_item *vs = (st_item*) malloc(sizeof(st_item));

    vs->next = st->top;
    vs->x = x;
    vs->y = y;

    st->top = vs;
    st->size++;
}

st_item *st_top(Stack *st) {
    /*
    * Importante checar se o topo não está vazio.
    * Caso contrário, receberá um Segmentation Fault!
    */
    return st->top;
}

void st_pop(Stack *st) {
    if(st_empty(st))
        return;

    st_item *top = st->top;
    st->top = top->next;
    st->size--;
    free(top);
}

Stack *st_init() {
    Stack *st = (Stack*) malloc(sizeof(Stack));
    st->size = 0;
    st->top = NULL;

    return st;
}

st_item *st_item_insert(st_item *st, int x, int y) {
    st_item *top = (st_item*)malloc((sizeof(st_item)));

    top->x = x;
    top->y = y;
    top->next = st;

    return top;
}
