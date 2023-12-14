#pragma once

#include <stdbool.h>
#include "linked_list.c"
#include "../structures/grid.c"

typedef struct {
    int size;
    node *head;
    node *tail;
} queue;

queue *queue_create() {
    queue *q = malloc(sizeof(queue));
    q->size = 0;
    q->head = NULL;
    return q;
}

void queue_push(queue *q, point coords) {
    if (q->size == 0) {
        q->head = node_create(coords);
        q->tail = q->head;
    }
    else {
        q->tail->next = node_create(coords);
        q->tail = q->tail->next;
    }

    q->size++;
}

point queue_pop(queue *q) {
    point coords = q->head->coords;
    q->head = node_pop(q->head);
    q->size--;
    return coords;
}

bool queue_empty(queue *q) {
    return q->size == 0;
}

point queue_peek(queue *q) {
    return q->head->coords;
}

void queue_print(queue *q) {
    node *n = q->head;

    while (n != NULL) {
        printf("(%d, %d) ", n->coords.x, n->coords.y);

        if (n->next != NULL)
            printf("-> ");

        n = n->next;
    }

    printf("\n");
}
