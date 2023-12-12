#pragma once

#include <stdio.h>
#include "directions.c"

void print_grid(int size, int grid[size][size], axis sp, Direction current_direction) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i == sp.x) && (j == sp.y)) {
                printf("%s", symbols[current_direction]);
                continue;
            }

            switch (grid[i][j]) {
                case 0:
                    printf("█");
                    break;
                case 1:
                    printf(" ");
                    break;
                case 2:
                    printf("○");
                    break;
                case 3:
                    printf("░");
                    break;
                default:
                    printf("?");
                    break;
            }
        }

        printf("\n");
    }
}
