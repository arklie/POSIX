#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    void flushStdin(FILE*);
    char letter, *p = (char*) malloc(sizeof(char)*4);
    int grade;
    do {
        grade = -1;
        char *buff = (char*) malloc(sizeof(char)*4);
        printf("Enter grade from 0 to 100:");
        fgets(buff, sizeof(char) * 4, stdin);
        grade = atoi(buff);
        if (buff[strlen(buff) - 1] == '\n')
            buff[strlen(buff) - 1] = '\0';
        flushStdin(stdin);
        sprintf(p, "%d", grade);
        if (strcmp(p, buff) != 0) {
            grade = -1;
            printf("%s was not in the range of valid integers and/or was not an integer.\n\n", buff);
        }
    } while (grade < 0 || grade > 100); // If grade is not from 0 to 100, prompt again.

    if (grade < 50) // Since we never let a value less than 0 out of the do while, there is no need to check for a 'below 0' case.
        letter = 'F';
    else if (grade < 55)
        letter = 'D';
    else if (grade < 65)
        letter = 'C';
    else if (grade < 85)
        letter = 'B';
    else // Since we never let a grade above 100 out of the do while, there is no need to check for an 'above 100' case.
        letter = 'A';

    printf("Letter Grade: %c", letter);
}

void flushStdin(FILE *fp) {
    fseek(fp, 0, SEEK_END);
}