#pragma once

#include <stdio.h>
#include "directions.c"

int make_move(char c) {
    printf("%c\n", c);
    fflush(stdout);

    int value;
    scanf("%d", &value);
    fflush(stdin);

    return value;
}

int make_request(Direction source, Direction target) {
    if (
        (source == UP && target == DOWN)
        || (source == DOWN && target == UP)
        || (source == LEFT && target == RIGHT)
        || (source == RIGHT && target == LEFT)
    ) {
        make_move('l');
        make_move('l');
    } else if (
        (source == UP && target == LEFT)
        || (source == LEFT && target == DOWN)
        || (source == DOWN && target == RIGHT)
        || (source == RIGHT && target == UP)
    ) {
        make_move('l');
    } else if (
        (source == UP && target == RIGHT)
        || (source == RIGHT && target == DOWN)
        || (source == DOWN && target == LEFT)
        || (source == LEFT && target == UP)
    ) {
        make_move('r');
    }

    return make_move('w');
}
