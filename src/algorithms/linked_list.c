#pragma once

#include <stdlib.h>
#include "../structures/grid.c"

typedef struct node {
    point coords;
    struct node *next;
} node;

node *node_create(point coords) {
    node *n = malloc(sizeof(node));
    n->coords = coords;
    return n;
}

node *node_insert(node *n, point coords) {
    node *new = node_create(coords);
    new->next = n;
    return new;
}

node *node_pop(node *n) {
    node *next = n->next;
    free(n);
    return next;
}
