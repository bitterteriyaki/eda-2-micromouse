#include <stdbool.h>
#include "structures/grid.c"
#include "structures/dfs.c"

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

void solve() {
    cell grid[MAX][MAX];
    // We assume that we are facing up and that our starting position is the
    // center of the grid.
    direction current_direction = UP;
    point position = {(MAX - 1) / 2, (MAX - 1) / 2};

    // We start by initializing the grid and marking the current cell as
    // visited.
    grid_init(MAX, grid);
    grid[position.x][position.y].visited = true;

    // We perform a depth-first search on the grid to find the exit.
    node *path = dfs(MAX, grid, position, &current_direction, NULL);

    // Now that we have found the exit, we go back to the starting position.
    node *reverse_path = node_insert(NULL, path->coords);

    int last_x = path->coords.x, last_y = path->coords.y;
    path = node_pop(path);

    debug("%s", "Going back to the starting position...\n");
    while (path != NULL) {
        int x = path->coords.x, y = path->coords.y;
        reverse_path = node_insert(reverse_path, path->coords);

        point movement = {x - last_x, y - last_y};
        last_x = x, last_y = y;

        reverse_movement(&current_direction, movement);

        path = node_pop(path);

        if(DEBUG_TEST)
            grid_print(MAX, grid, position, current_direction);
    }

    // We print the path that Cleitinho took to find the exit.
    debug("%s", "Now going back to exit:\n");
    reverse_path = node_pop(reverse_path);

    while(reverse_path != NULL) {
        int x = reverse_path->coords.x, y = reverse_path->coords.y;
        point movement = {x - last_x, y - last_y};
        last_x = x, last_y = y;

        reverse_movement(&current_direction, movement);

        reverse_path = node_pop(reverse_path);

        if(DEBUG_TEST)
            grid_print(MAX, grid, position, current_direction);
    }
}

/*
* Grid example:
* [^S]
* [EW]
*/

int main() {
    solve();
    return 0;
}
