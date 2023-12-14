#pragma once

#include "grid.c"
#include "../utils/requests.c"

#ifdef DEBUG
#define DEBUG_TEST true
#else
#define DEBUG_TEST false
#endif

/*
 * This function performs a depth-first search on the grid to find the exit.
 *
 * @param size The size of the grid.
 * @param grid A 2D array of cells representing the grid.
 * @param position The current position of Cleitinho in the grid.
 * @param current_direction The direction that Cleitinho is facing.
 * @return void
 */
void dfs(
    int size,
    cell grid[size][size],
    point position,
    direction current_direction
) {
    if (DEBUG_TEST)
        grid_print(size, grid, position, current_direction);
}
