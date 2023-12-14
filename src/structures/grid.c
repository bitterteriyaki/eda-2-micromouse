#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

point dir4[] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
char *symbols[] = {"↑", "→", "↓", "←"};

/*
 * This enum represents the four directions that Cleitinho can face. We will
 * use this enum to represent the direction that Cleitinho is facing.
 */
typedef enum {
    UP,
    RIGHT,
    DOWN,
    LEFT
} direction;

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
            grid[i][j] = (cell) {{false, false, false, false}, false};
}


void _print_horizontal_line(int size) {
    for (int j = 0; j < size; j++)
        printf("+---");
    printf("+\n");
}

void _print_vertical_lines(int size) {
    for (int j = 0; j < size; j++)
        printf("+   ");
    printf("+\n");
}

void _print_cells(
    int size,
    int index,
    point position,
    direction current_direction
) {
    printf("|");

    for (int j = 0; j < size; j++) {
        if (position.x == j && position.y == index - 1)
            printf(" %s ", symbols[current_direction]);
        else
            printf("   ");

        if (j != size - 1)
            printf(" ");
    }

    printf("|\n");
}

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
            _print_cells(size, i, position, current_direction);

            if (i != size)
                _print_vertical_lines(size);
        }

    printf("\n");
}
