// Lab 2: Functions, Pointers, and Arrays.
// Jon Mitchell & Tom Arklie

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isDigit(char *in) { // Verify the input is a digit.
    char *p = malloc(sizeof(char) * strlen(in));
    // ^ String to hold the result of atoi for comparison later.
    // Initialized to the char count of the input char[]
    // for optimal space complexity.
    int n = atoi(in);
    // ^ Attempting to make an int from the input
    sprintf(p, "%d", n);
    // ^ Taking the value of n gotten from atoi and writing it to
    if (in[strlen(in) - 1] == '\n')
        in[strlen(in) - 1] = '\0';
    return strcmp(in, p) == 0;
}

int parseSpaceSeperated(char *in) {
    int nums[5], begin = 0, count = 0;
    // ^ We need a number array of 5, a begin index marker to mark the start of a number, and the count of numbers found
    char *p = malloc(sizeof(in));
    // ^ We need a buffer that can handle the substrings we'll make to parse the spaces in the input.

    for (int i = 0; (i < strlen(in)) && (count < 5); i++) {
        // ^ As long as i is less than the string length of the input and we haven't yet found 5 numbers, loop.
        if (in[i] == '\0')
            break;
        // ^ If we find a null term, then we end the loop with what we got. This is an assurance to stop seg faults.
        if (in[i] == ' ' || in[i] == '\n') {
            // If we find a space or newline, continue with the parsing.
            memcpy(p, &in[begin], i - begin);
            // ^ Copy from the last marked beginning point to current index
            // This is done by calculating the length of the current number by subtracting begin from the current index.
            p[(i)-begin] = '\0';
            // ^ Put a null term at the end of the found number.
            // Since we reuse the same buffer, we want to make sure we don't confuse atoi with possible chars from
            // previous numbers.
            if (!isDigit(p))
                return -1;
            // ^ If we find a non-digit, we exit the program with error code -1
            nums[count] = atoi(p);
            // ^ Add the new-found number to the number array. The index it is put in is determined by how many numbers
            // we have found so far.
            count++;
            begin = i + 1;
            // Increment count and set the new beginning point for the next number.
            if (in[i] == '\n')
                break;
            // If the found number was found by a newline, we are done. Break loop.
        }
    }
    return *nums;
}

int sum(int *array[], int *size) {

}

int findLargest(int *array[], int *size) {

}

int findSmallest(int *array[], int *size) {

}

int main() {

}
