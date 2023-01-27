#include <stdio.h>

int main() {


    return 0;
}

int sum(const int *a, const int *b) {
    return *a + *b;
}

int diff(const int *a, const int *b) {
    return *a - *b;
}

int mult(const int *a, const int *b) {
    return *a * *b;
}

int div(const int *a, const int *b) {
    if (*b == 0) {
        printf("Cannot divide by ");
        return 0;
    }
    return *a / *b;
}

int remain(const int *a, const int *b) {
    if (*b == 0) {
        printf("Cannot divide by ");
        return 0;
    }
    return *a % *b;
}