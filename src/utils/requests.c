#include <stdio.h>

int make_move(char c) {
    printf("%c\n", c);
    fflush(stdout);
    
    int value;
    scanf("%d", &value);
    fflush(stdin);

    return value;
}