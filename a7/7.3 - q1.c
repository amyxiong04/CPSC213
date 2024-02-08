#include <stdio.h>

int array[10];
int* pointer = array;

void foo(int arg1, int arg2) {
    pointer[arg2] = pointer[arg2] + arg1;
}

void main() {
    int local1, local2;
    local1 = 1;
    local2 = 2;
    foo(3, 4);
    foo(local1, local2);
    for (int i = 0; i < 10; i++) {
        printf("%i\n", array[i]);
    }
}