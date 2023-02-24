// Lab 2: Functions, Pointers, and Arrays.
// Jon Mitchell & Tom Arklie

#include <stdio.h>
#include <string.h>

int countVowels(char word[]) {
    int count = 0;
    word = strlwr(word);
    // ^ Converting word to lowercase to avoid case-sensitive related errors
    for (int i = 0; i < strlen(word); i++) {
        switch (word[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                count++;
                break;
        }
        // ^ Cases will fall through to the count++ if any are true.
    }
    return count;
}

int main () {
    char buff[80];
    printf("Enter any word: ");
    fgets(buff, sizeof(buff), stdin);
    return printf("There were %d vowels", countVowels(buff)), 0;
}