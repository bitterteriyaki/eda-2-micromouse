#include <stdio.h>

void flush() {
    fflush(stdout);
}

int read() {
    int value;
    scanf("%d", &value);

    return value;
}

int make_move(char c) {
    printf("%c\n", c);
    
    int value = read();
    flush();

    return value;
}