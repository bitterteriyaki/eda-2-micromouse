#pragma once

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct {
    int x;
    int y;
} axis;

axis dir4[] = {
    {-1, 0}, // UP
    {1, 0},  // LEFT
    {0, -1}, // DOWN
    {0, 1}   // RIGHT
};

char *directions[] = {
    "UP",
    "DOWN",
    "LEFT",
    "RIGHT"
};

char *symbols[] = {
    "▲",
    "▼",
    "◄",
    "►"
};
