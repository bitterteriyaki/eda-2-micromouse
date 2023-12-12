#include <stdio.h>
#include "utils/directions.c"
#include "utils/grid.c"
#include "structures/stack.c"

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define debug(fmt, ...) \
        do { if (DEBUG_TEST) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)  

#define MAXN 300

enum Status {
    WALL,
    VISITED,
    EXIT,
    NOT_VISITED
};

int grid[MAXN][MAXN];

st_item *dfs(axis sp, enum Direction *curr_dir, st_item *path) {
    if (grid[sp.x][sp.y] == (int) WALL)
        return NULL;
    
    path = st_item_insert(path, sp.x, sp.y);

    if (grid[sp.x][sp.y] == EXIT)
        return path;

    debug("currently direction: %s\n", directions[(int) *curr_dir]);
    
    
    // Firstly, we give priority to FORWARD.
    int x = dir4[(int) *curr_dir].x + sp.x;
    int y = dir4[(int) *curr_dir].y + sp.y;

    st_item *st = NULL;
    enum Direction original_direction = *curr_dir;

    if (grid[x][y] == NOT_VISITED) {
        debug("[first] asking forward %s\n", directions[(int) *curr_dir]);
        grid[x][y] = make_request(*curr_dir, *curr_dir);
        st = dfs((axis){x, y}, curr_dir, path);
    }

    if (st != NULL)
        return st;
    
    // Now, we make the other requests. 
    for (int i = 0; i < 4; i++) {
        x = dir4[i].x + sp.x, y = dir4[i].y + sp.y;

        if (grid[x][y] == NOT_VISITED) {
            debug("[second] asking %s to %s\n", directions[(int) *curr_dir], directions[i]);
            debug("movement: %d %d\n", dir4[i].x, dir4[i].y);
            grid[x][y] = make_request(*curr_dir, i);
            *curr_dir = i;

            st = dfs((axis){x, y}, curr_dir, path);

            if (st != NULL)
                return st;
        }
    }
    
    /*
    * Once we already visited all the possible paths, we need to go back.
    */
    
    st_item old_path = *path->next;
    int old_x = old_path.x, old_y = old_path.y;

    axis movement = (axis) {old_x - sp.x, old_y - sp.y};

    debug("[back] movement: %d %d\n", movement.x, movement.y);
    reverse_movement(curr_dir, movement);
    debug("[back] current direction: %s\n", directions[(int) *curr_dir]);

    return NULL;
}

/*
* [S^]
* [WE]
*/

int main() {
    enum Direction current_direction = UP;

    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            grid[i][j] = (int) NOT_VISITED;


    axis sp = (axis) {MAXN / 2, MAXN / 2};
    grid[sp.x][sp.y] = VISITED;
    
    // print_grid(MAXN, grid, sp);

    st_item *path = dfs(sp, &current_direction, NULL);
    Stack *reverse_path = init_stack();

    int last_x = path->x, last_y = path->y;
    st_insert(reverse_path, last_x, last_y);
    
    path = path->next;
    debug("[reversing] current direction: %s\n", directions[(int) current_direction]);

    while (path != NULL) {
        int x = path->x, y = path->y;
        st_insert(reverse_path, x, y);

        axis movement = (axis) {x - last_x, y - last_y};
        last_x = x, last_y = y;
        reverse_movement(&current_direction, movement);
        debug("current direction: %s\n", directions[(int) current_direction]);

        path = path->next;
    }

    debug("%s", "now printing the reverse path\n");
    st_pop(reverse_path);

    while (!st_empty(reverse_path)) {
        st_item *top = st_top(reverse_path);
        int x = top->x, y = top->y;

        axis movement = (axis) {x - last_x, y - last_y};
        last_x = x, last_y = y;
        debug("current direction: %s\n", directions[(int) current_direction]);
        reverse_movement(&current_direction, movement);
        st_pop(reverse_path);
    }

    return 0;
}
