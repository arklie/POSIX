#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isDigit(char *in) {
    char *p = malloc(sizeof(in));
    int num = atoi(in);
    sprintf(p, "%d", num);
    return strcmp(in, p) == 0;
}

int main() {
    char buff[40];
    int n, sum = 0, i = 1;
    printf("Enter a positive Integer: ");
    fgets(buff, sizeof(buff), stdin);
    n = atoi(buff);
    if (buff[strlen(buff)-1] == '\n')
        buff[strlen(buff)-1] = '\0';
    if (!isDigit(buff))
        return -1;

    while ((float) i <= ((float)n/2)) {
        if (n % i == 0)
            sum += i;
        i++;
    }
    if (sum == n)
        printf("%d is perfect", n);
    else
        printf("%d is not perfect", n);

    return 0;
}