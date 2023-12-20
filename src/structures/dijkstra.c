#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./grid.c"
#include "./directions.c"
#include "../algorithms/priority_queue.c"

#ifdef DEBUG
#define DEBUG_TEST true
#define MAX 11
#else
#define DEBUG_TEST false
#define MAX 300
#endif

#define debug(fmt, ...) \
        do { if (DEBUG_TEST) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

const int INF = 0x3f3f3f3f;

int distance[MAX][MAX];
point pred[MAX][MAX];
bool visited[MAX][MAX];

void dijkstra(
    int size,
    cell grid[size][size],
    point position,
    point exit,
    direction current_direction
) {
    int x = position.x, y = position.y;
    int ex = exit.x, ey = exit.y;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            distance[i][j] = INF;
            visited[i][j] = false;
            pred[i][j] = (point) {-1, -1};
        }
    }

    // We initialize the queue.
    Priority_Queue *pq = init_pq(size * size + 1);
    Item item = {position, current_direction, 0};
    pq_insert(pq, item);

    pred[x][y] = position;

    // We initialize the distance of the starting position.
    distance[x][y] = 0;

    debug("Currently at (%d, %d)\n", x, y);
    debug("Target is at (%d, %d)\n", ex, ey);

    int forward = 0;

    while (!pq_is_empty(pq)) {
        Item item = pq_top(pq);
        point coords = item.value;
        x = coords.x, y = coords.y;

        if(DEBUG_TEST)
            grid_print(size, grid, coords, item.dir);
        
        debug("x: %d, y: %d, dir: %d, distance: %d\n", x, y, item.dir, item.priority);

        // We remove the current item from the queue.
        pq_pop(pq);

        if(visited[x][y])
            continue;

        // We mark the current cell as visited.
        visited[x][y] = true;

        // We check if we have reached the exit.
        if (x == ex && y == ey)
            break;

        // We check the four directions.
        for (int i = 0; i < 4; i++) {
            direction next_direction = get_context(i, item.dir);

            point next_position = get_next_position(coords, next_direction);
            int next_x = next_position.x, next_y = next_position.y;

            // We check if we can move to the next cell.
            if (
                grid[x][y].walls[next_direction] != 0
                || visited[next_x][next_y]
                || !grid[next_x][next_y].visited
            )
                continue;

            // We check if we have already visited the next cell.
            int weight = (next_direction == item.dir) ? 0 : 1;
            int count = 0;

            if(next_direction == item.dir) {
                forward++;
            }

            if(next_direction != item.dir || next_position.x == ex && next_position.y == ey) {
                for (int i = 4; i <= 1; i--) {
                    while(forward >= i) {
                        forward -= i;
                        count++;
                    }
                }
            }

            weight += count;

            if (distance[next_x][next_y] > distance[x][y] + weight) {
                distance[next_x][next_y] = distance[x][y] + weight;
                pred[next_x][next_y] = coords;

                Item item = {next_position, next_direction, distance[next_x][next_y]};
                pq_insert(pq, item);
            }
        }
    }
}