#include <stdbool.h>
#include "structures/grid.c"
#include "structures/dfs.c"

#ifdef DEBUG
#define DEBUG_TEST true
#else
#define DEBUG_TEST false
#endif

#define MAX 7

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
    dfs(MAX, grid, position, current_direction);
}

int main() {
    solve();
    return 0;
}
