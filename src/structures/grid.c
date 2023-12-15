#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "directions.c"
#include "../utils/requests.c"

/*
 * This struct represents a cell in the grid. It is intended to be used with
 * a 2D array of cells, where each cell represents a single square in the grid
 * accessible by a single coordinate pair (x, y).
 *
 * The cell struct contains a boolean value for each of the four walls of the
 * cell, as well as a boolean value for whether or not the cell has been
 * visited.
 */
typedef struct {
    bool walls[4];
    bool visited;
    bool is_exit;
} cell;

/*
 * This struct represents a point in the grid. We will use this struct to
 * represent the current position of Cleitinho in the grid. It contains two
 * integer values, x and y, which represent the x and y coordinates of the
 * point, respectively.
 */
typedef struct {
    int x;
    int y;
} point;

/*
* We define an array of four points, where each point represents a direction
* Directions are represented as follows:
* 0: UP
* 1: LEFT
* 2: DOWN
* 3: RIGHT
*/
point dir4[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
char *symbols[] = {"↑", "←", "↓", "→"};

// This array is used for the sensors, which use the following order:
direction clockwise_positions[] = {UP, RIGHT, DOWN, LEFT};

/*
 * This function initializes the grid by setting all of the walls of each cell
 * to false (i.e. there are no walls in the grid, so Cleitinho can move freely)
 * and setting the visited value of each cell to false.
 *
 * @param size The size of the grid.
 * @param grid A 2D array of cells representing the grid.
 * @return void
 */
void grid_init(int size, cell grid[size][size]) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            grid[i][j] = (cell) {{false, false, false, false}, false, false};
}


void _print_horizontal_line(int size) {
    for (int j = 0; j < size; j++)
        printf("+---");
    printf("+\n");
}

void _print_vertical_lines(int size, int i, cell grid[size][size]) {
    for (int j = 0; j < size; j++) {
        printf("+");

        if (grid[i][j].walls[UP])
            printf("---");
        else
            printf("   ");
    }

    printf("+\n");
}

void _print_cells(
    int size,
    int i,
    cell grid[size][size],
    point position,
    direction current_direction
) {
    printf("|");

    for (int j = 0; j < size; j++) {
        if (position.x == i - 1 && position.y == j)
            printf(" %s ", symbols[current_direction]);
        else if (grid[i - 1][j].is_exit)
            printf(" 🏳️ ");
        else if (grid[i - 1][j].visited)
            printf(" ♦ ");
        else
            printf("   ");

        if (j != size - 1)
            if (grid[i - 1][j].walls[RIGHT])
                printf("|");
            else
                printf(" ");
    }

    printf("|\n");
}

/*
 * This function prints the grid in a human-readable format.
 *
 * @param size The size of the grid.
 * @param grid A 2D array of cells representing the grid.
 * @param position The current position of Cleitinho in the grid.
 * @param current_direction The current direction that Cleitinho is facing.
 * @return void
 */
void grid_print(
    int size,
    cell grid[size][size],
    point position,
    direction current_direction
) {
    for (int i = 0; i < size + 2; i++)
        if (i == 0 || i == size + 1)
            _print_horizontal_line(size);
        else {
            _print_cells(size, i, grid, position, current_direction);

            if (i != size)
                _print_vertical_lines(size, i, grid);
        }

    printf("\n");
}

/*
* Once Cleitinho is able to change directions, we need to make sure
* that he goes in the right direction according to his current direction.
*/
direction get_left(direction dir) {
    if (dir == UP) return LEFT;
    if (dir == LEFT) return DOWN;
    if (dir == DOWN) return RIGHT;
    if (dir == RIGHT) return UP;
}

direction get_right(direction dir) {
    if (dir == UP) return RIGHT;
    if (dir == RIGHT) return DOWN;
    if (dir == DOWN) return LEFT;
    if (dir == LEFT) return UP;
}

direction get_down(direction dir) {
    if (dir == UP) return DOWN;
    if (dir == DOWN) return UP;
    if (dir == LEFT) return RIGHT;
    if (dir == RIGHT) return LEFT;
}

direction get_up(direction dir) {
    return dir;
}

direction get_context(direction dir, direction curr) {
    if (dir == UP) return get_up(curr);
    if (dir == DOWN) return get_down(curr);
    if (dir == LEFT) return get_left(curr);
    if (dir == RIGHT) return get_right(curr);
}

/*
 * This function returns the direction that Cleitinho should face in order to
 * move from the source point to the target point.
 *
 * @param source The source point.
 * @param target The target point.
 */
direction get_next_direction(direction source, direction target) {
    int steps;

    if (target == UP)
        steps = 0;
    else if (target == RIGHT)
        steps = 1;
    else if (target == DOWN)
        steps = 2;
    else if (target == LEFT)
        steps = 3;

    return (direction) ((source + steps) % 4);
}

point get_next_position(point position, direction dir) {
    return (point) {position.x + dir4[dir].x, position.y + dir4[dir].y};
}
