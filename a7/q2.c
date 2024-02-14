#include <stdio.h>

int x[8] = {1, 2, 3, -1, -2, 0, 184, 340057058};
int y[8];

int f(int arg1) {
    int r0 = 0; // return value
    while (arg1 != 0) {
        if (arg1 & 0x80000000) {
            r0++;
        }
        arg1 = arg1 << 1;
    }
    return r0;
}

void main() {
    for (int i = 8; i != 0; i--) {
        y[i] = f(x[i]);
    }

    for (int j = 0; j < 8; j++) {
        printf("%i\n", x[j]);
    }

    for (int k = 0; k < 8; k++) {
        printf("%i\n", y[k]);
    }
}