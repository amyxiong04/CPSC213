#include <stdio.h>

int main() {
    char *words[] = {"Amy", "Shawn", "Alice", "Steven"};
    char **ptr = words;

    // Iterate through the array using the pointer
    for (; *ptr != NULL; ptr++) {
        printf("%s ", *ptr);
    }
    return 0;
}
