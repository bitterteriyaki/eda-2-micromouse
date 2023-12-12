#include <stdio.h>
#include "requests.c"

enum Direction { // clockwise
    UP, // ^
    LEFT, // <
    DOWN, // v
    RIGHT // >
};

typedef struct axis {
    int x, y;
} axis;

// UP, LEFT, DOWN, RIGHT
axis dir4[] = {(axis){0, -1}, (axis){1, 0}, (axis){0, 1}, (axis){-1, 0}};

char *directions[] = {"UP ^", "LEFT <", "DOWN v", "RIGHT >"};

void swap_directions(enum Direction *a, enum Direction *b) {
    enum Direction tmp = *a;
    *a = *b;
    *b = tmp;
}

int make_request(enum Direction source, enum Direction target) {
    if((source == UP && target == DOWN) || (source == DOWN && target == UP) || (source == LEFT && target == RIGHT) || (source == RIGHT && target == LEFT)) {
        make_move('l');
        make_move('l');
    }
    else if((source == UP && target == LEFT) || (source == LEFT && target == DOWN) || (source == DOWN && target == RIGHT) || (source == RIGHT && target == UP)) {
        make_move('l');
    }
    else if((source == UP && target == RIGHT) || (source == RIGHT && target == DOWN) || (source == DOWN && target == LEFT) || (source == LEFT && target == UP)) {
        make_move('r');
    }


    int value = make_move('w');
    return value;
}

void reverse_movement(enum Direction *curr_dir, axis movement) {
    for(int i = 0; i < 4; i++) {
        if(dir4[i].x == movement.x && dir4[i].y == movement.y) {
            make_request(*curr_dir, (enum Direction) i);
            *curr_dir = (enum Direction) i;
            break;
        }
    }
}