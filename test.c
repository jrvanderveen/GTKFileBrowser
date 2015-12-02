#include <stdio.h>

int main(void) {
    char str[10];
    snprintf(str, 10, "%d", 42);
    printf("number now string: %s", str);
}