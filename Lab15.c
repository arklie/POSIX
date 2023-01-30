#include <stdio.h>
#include <stdlib.h>

int main() {
    char letter;
    int grade;
    do {
        char *buff = (char*) malloc(sizeof(char)*4);
        printf("Enter grade from 0 to 100: ");
        fgets(buff, sizeof(char) * 3, stdin);
        grade = atoi(buff);
        printf("Grade: %i\n", grade);
    } while (grade < 0 || grade > 100 || grade == '\n' || grade == '\0'); // If grade is not from 0 to 100, prompt again.

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
