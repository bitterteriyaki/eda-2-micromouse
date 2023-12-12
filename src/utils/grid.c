#include "stdio.h"
// #include "directions.c"

void print_grid(int size, int grid[size][size], axis sp) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            switch (grid[i][j])
            {
            case 0:
                printf("W");
                break;
            case 1:
                printf("V");
                break;
            case 2:
                printf("E");
                break;
            case 3:
                printf("N");
                break;
            default:
                printf("?");
                break;
            }

            if (j + 1 == size)
                printf("\n");
        }
    }
}
