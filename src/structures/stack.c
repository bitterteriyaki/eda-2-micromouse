#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "../utils/directions.c"

typedef struct st_item {
    axis sp;
    struct st_item *next;
} st_item;

typedef struct {
    st_item *top;
    int size;
} stack;

stack *st_init() {
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

void st_insert(stack *s, axis sp) {
    st_item *item = malloc(sizeof(st_item));
    item->sp = sp;
    item->next = s->top;
    s->top = item;
    s->size++;
}

void st_print(stack *s) {
    st_item *item = s->top;

    while (item != NULL) {
        printf("{x: %d, y: %d}", item->sp.x, item->sp.y);

        if (item->next != NULL)
            printf(" -> ");

        item = item->next;
    }

    printf("\n");
}
