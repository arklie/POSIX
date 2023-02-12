#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isDigit(char *in, int *n) {
    char *p = malloc(sizeof(char) * *n);
    if (in[strlen(in) - 1] == '\n')
        in[strlen(in) - 1] = '\0';

    sprintf(p, "%d", *n);
    if (strcmp(p, in) != 0) {
        return 0;
    }
    return 1;
}

int main() {
    char buff[80];
    int n, *res, total = 0;
    printf("Enter number of alternating series: ");
    fgets(buff, sizeof(buff), stdin);
    n = atoi(buff);

    if (!isDigit(buff, &n)) {
        return -1;
    }

    res = malloc(sizeof(int) * n);

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            res[i-1] = -i;
            total -= i;
        } else {
            res[i-1] = i;
            total += i;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", res[i]);
    }
    printf("= %d\n", total);

    return 0;
}