#include <stdbool.h>
#include "utils/directions.c"
#include "utils/grid.c"
#include "utils/requests.c"
#include "structures/stack.c"

#ifdef DEBUG
#define DEBUG_TEST true
#else
#define DEBUG_TEST false
#endif

#define MAXN 8
#define debug(fmt, ...) \
        do { if (DEBUG_TEST) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)

typedef enum {
    WALL,
    VISITED,
    EXIT,
    NOT_VISITED
} Status;

void dfs(stack *paths, axis sp, Direction direction, int grid[MAXN][MAXN]) {
    print_grid(MAXN, grid, sp, direction);
    st_print(paths);

    axis vector = dir4[direction];

    int x = sp.x + vector.x;
    int y = sp.y + vector.y;

    debug("vector: {x: %d, y: %d}\n", vector.x, vector.y);
    debug("position: {x: %d, y: %d}\n", sp.x, sp.y);
    debug("new position: {x: %d, y: %d}\n", x, y);

    // TODO: Change direction if the current direction is not possible
    // and continue the search.
    if (
        (direction == UP && x < 0)
        || (direction == DOWN && x >= MAXN)
        || (direction == LEFT && y < 0)
        || (direction == RIGHT && y >= MAXN)
    ) {
        direction = (direction + 1) % 4;
        dfs(paths, sp, direction, grid);
        return;
    }

    if (grid[x][y] == NOT_VISITED) {
        grid[x][y] = make_request(direction, direction);

        // The request was successful. Change the Cleitinho's position to the
        // discovered position and continue the search.
        if (grid[x][y] == VISITED) {
            sp = (axis) {x, y};
            st_insert(paths, sp);

            dfs(paths, sp, direction, grid);
            return;
        }
    }

    // The request was not successful. Change the direction and continue the
    // search.
    direction = (direction + 1) % 4;
    dfs(paths, sp, direction, grid);
}

int main() {
    int grid[MAXN][MAXN];

    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            grid[i][j] = NOT_VISITED;

    axis sp = {MAXN / 2, MAXN / 2};
    grid[sp.x][sp.y] = VISITED;

    stack *paths = st_init();
    st_insert(paths, sp);

    dfs(paths, sp, UP, grid);

    return 0;
}
