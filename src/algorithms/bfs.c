#pragma once

#include <string.h>
#include "grid.c"
#include "../structures/queue.c"

typedef struct {
    int **dist;
    point **pred;
} bfs_result;

bfs_result bfs(
    int size,
    cell grid[size][size],
    point source,
    point destination
) {
    int dist[size][size];
    point pred[size][size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            dist[i][j] = -1;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            pred[i][j] = (point) {-1, -1};

    queue *q = queue_create();
    queue_push(q, source);

    dist[source.x][source.y] = 0;
    pred[source.x][source.y] = (point) {-1, -1};

    while (!queue_is_empty(q)) {
        point curr = queue_pop(q);

        int x = curr.x, y = curr.y;

        for (int i = 0; i < 4; i++) {
            point next = {x + dir4[i].x, y + dir4[i].y};

            if (grid[x][y].walls[i] != 2 || !grid[next.x][next.y].visited)
                continue;

            if (dist[next.x][next.y] != -1)
                continue;

            dist[next.x][next.y] = dist[x][y] + 1;
            pred[next.x][next.y] = (point) {x, y};

            queue_push(q, next);
        }
    }

    bfs_result result = {
        .dist = malloc(sizeof(int *) * size),
        .pred = malloc(sizeof(point *) * size)
    };

    for (int i = 0; i < size; i++) {
        result.dist[i] = malloc(sizeof(int) * size);
        result.pred[i] = malloc(sizeof(point) * size);

        memcpy(result.dist[i], dist[i], sizeof(int) * size);
        memcpy(result.pred[i], pred[i], sizeof(point) * size);
    }

    return result;
}
