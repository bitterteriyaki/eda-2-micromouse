#pragma once

#include <stdio.h>
#include "../structures/grid.c"
#include "../structures/directions.c"

typedef enum {
    FAILED,
    SUCCESS,
    EXIT
} status;

/*
 * This function asks the judge for the value returned by the server.
 *
 * @param request The request to send to the server.
 * @return The value returned by the server.
 */
int ask(char request) {
    int response;

    printf("%c\n", request);
    fflush(stdout);

    scanf("%d", &response);
    fflush(stdin);

    return response;
}

/*
 * This function asks the judge to move Cleitinho forward.
 *
 * @return The value returned by the server. If the value is 1, then Cleitinho
 * was able to move forward. If the value is 0, then Cleitinho was not able to
 * move forward (there is a wall in front of him).
 */
status forward() {
    return ask('w');
}

status rotate_and_forward(direction source, direction target) {
    if((source == UP && target == DOWN) || (source == DOWN && target == UP) || (source == LEFT && target == RIGHT) || (source == RIGHT && target == LEFT)) {
        ask('l');
        ask('l');
    }
    else if((source == UP && target == LEFT) || (source == LEFT && target == DOWN) || (source == DOWN && target == RIGHT) || (source == RIGHT && target == UP)) {
        ask('l');
    }
    else if((source == UP && target == RIGHT) || (source == RIGHT && target == DOWN) || (source == DOWN && target == LEFT) || (source == LEFT && target == UP)) {
        ask('r');
    }

    return forward();
}