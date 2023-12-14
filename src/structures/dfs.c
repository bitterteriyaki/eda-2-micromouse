#pragma once

#include "grid.c"
#include "../utils/requests.c"
#include "../algorithms/linked_list.c"
#include <stdbool.h>

#ifdef DEBUG
#define DEBUG_TEST true
#else
#define DEBUG_TEST false
#endif

#define debug(fmt, ...) \
        do { if (DEBUG_TEST) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

void reverse_movement(direction *curr_dir, point movement, bool forward_enabled) {    
    for (int i = 0; i < 4; i++)
        if (dir4[i].x == movement.x && dir4[i].y == movement.y) {
            rotate_and_forward(*curr_dir, (direction) i, forward_enabled);
            *curr_dir = (direction) i;
            break;
        }
}

/*
 * This function performs a depth-first search on the grid to find the exit.
 *
 * @param size The size of the grid.
 * @param grid A 2D array of cells representing the grid.
 * @param position The current position of Cleitinho in the grid.
 * @param current_direction The direction that Cleitinho is facing.
 * @return void
 */
node *dfs(
    int size,
    cell grid[size][size],
    point position,
    direction *current_direction,
    node *path
) {
    if (DEBUG_TEST)
        grid_print(size, grid, position, *current_direction);
    
    int x = position.x, y = position.y;
    path = node_insert(path, position);
    
    // If we are at the exit, then we are done.
    if (grid[x][y].is_exit)
        return path;
    
    node *exit = NULL;

    /*
    * We give priority to moving forward. Then, we go to the other directions.
    * Once our direction may be changed, we try to move four times.
    */
    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j <= 3; j++) {
            direction next_direction = get_context(j, *current_direction);
            point next_position = get_next_position(position, next_direction);

            /*
            * If we already visited this cell or if there is a wall in front of
            * us, then we cannot move.
            */

            if(grid[x][y].walls[next_direction])
                debug("Wall found at (%d, %d). Cannot move to (%d, %d). Current Direction: %s. Next Direction: %s\n", x, y, next_position.x, next_position.y, symbols[*current_direction], symbols[next_direction]);

            if (grid[next_position.x][next_position.y].visited ||
                grid[x][y].walls[next_direction]) 
                continue;

            // Now we try to visit.
            debug("Currently at (%d, %d)\n", x, y);
            debug(
                "Trying to visit (%d, %d). Current direction: %s. Next direction: %s\n",
                next_position.x,
                next_position.y,
                symbols[*current_direction],
                symbols[next_direction]
            );
            
            int response = rotate_and_forward(*current_direction, next_direction, true);
            *current_direction = next_direction;

            if (DEBUG_TEST)
                grid_print(size, grid, position, *current_direction);

            if (response == FAILED) {
                direction opposite = get_down(next_direction);
                grid[x][y].walls[next_direction] = true;
                grid[next_position.x][next_position.y].walls[opposite] = true;

                debug("Set wall at (%d, %d) in direction %s\n", x, y, symbols[next_direction]);
                debug("Set wall at (%d, %d) in direction %s\n", next_position.x, next_position.y, symbols[opposite]);

                if (DEBUG_TEST)
                    grid_print(size, grid, position, *current_direction);

                continue;
            }

            grid[next_position.x][next_position.y].visited = true;

            if (response == EXIT) {
                grid[next_position.x][next_position.y].is_exit = true;
                debug("%s\n", "Exit found.");
            }

            exit = dfs(size, grid, next_position, current_direction, path);

            if (exit != NULL) 
                return exit;
        }
    }

    // If we reach this point, then we are stuck. We need to backtrack.
    debug("%s\n", "Stuck. Backtracking...");
    path = node_pop(path);
    debug("Stuck at (%d, %d). Going back to (%d, %d).\n", x, y, path->coords.x, path->coords.y);

    point movement = (point) { path->coords.x - x, path->coords.y - y };
    reverse_movement(current_direction, movement, true);

    return NULL;
}
