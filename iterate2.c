#include <stdio.h>

int main() {
    char *words[] = {"Amy", "Shawn", "Alice", "Steven"};
    int num_words = sizeof(words) / sizeof(words[0]);

    // Iterate through the array using the pointer
    for (int i = 0; i < num_words; i++) {
        char *ptr = words[i]
        printf("%s ", *ptr);
    }
    return 0;
}
