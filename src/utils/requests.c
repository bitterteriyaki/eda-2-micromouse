#pragma once

#include <stdio.h>

typedef enum {
    SUCCESS,
    FAILED
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
    int a = (source - target + 4) % 4;
    int b = (target - source + 4) % 4;

    // If the directions are the same, then we just move forward.
    if (a == b)
        return forward();

    // If it is "cheaper" to rotate left, then we rotate left. Otherwise, we
    // rotate right.
    if (a < b)
        for (int i = 0; i < a; i++)
            ask('l');
    else
        for (int i = 0; i < b; i++)
            ask('r');

    return forward();
}

