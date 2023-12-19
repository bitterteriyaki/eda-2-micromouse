#include <stdbool.h>
#include "algorithms/grid.c"
#include "algorithms/dfs.c"
#include "algorithms/bfs.c"
#include "structures/queue.c"

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

    bfs_result result = bfs(MAX, grid, position, (point) {last_x, last_y});

    // Use the BFS result to find the shortest path back to the starting
    // position.

    while (result.pred[last_x][last_y].x != -1) {
        int x = result.pred[last_x][last_y].x;
        int y = result.pred[last_x][last_y].y;
        reverse_path = node_insert(reverse_path, (point) {x, y});

        point movement = {x - last_x, y - last_y};
        last_x = x, last_y = y;

        reverse_movement(&current_direction, movement, false);
        int forward = 1;

        while (result.pred[last_x][last_y].x != -1) {
            int xt = result.pred[last_x][last_y].x;
            int yt = result.pred[last_x][last_y].y;
            point movementt = {xt - last_x, yt - last_y};

            if (movementt.x == movement.x && movementt.y == movement.y) {
                forward++;
                last_x = xt, last_y = yt;
                reverse_path = node_insert(reverse_path, (point) {xt, yt});
            }
            else
                break;
        }

        for (int i = 4; i >= 1; i--)
            while (forward >= i) {
                ask(movements[i]);
                forward -= i;
            }

        if (DEBUG_TEST)
            grid_print(MAX, grid, position, current_direction);
    }
}

int main() {
    solve();
    return 0;
}
