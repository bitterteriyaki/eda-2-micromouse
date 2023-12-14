#pragma once

/*
 * This enum represents the four directions that Cleitinho can face.
 */
typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT
} direction;

/*
* This represents the best command to use when Cleitinho goes forward.
* The first item is ignored.
*/
const char movements[] = {'n', 'w', 'j', 'R', 's'};