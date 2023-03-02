#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Turnover time, set the arrival time to the time unit that the process starts. Default set to -1. If AT > -1, it has been started.
 */

typedef struct {
    int PID;
    int ARRIVAL_TIME;
    int REMANING_TIME;
    // ^ This is initially the burst time before it's first cycle. There is no need to waste memory keeping the
} Process;
// ^ The struct representing the faux process.

Process initProcess(int PID, int AT, int RT) {
    Process p;
    p.PID = PID;
    p.ARRIVAL_TIME = AT;
    p.REMANING_TIME = RT;
    return p;
}
// ^ General struct initialization method to start the struct with defined values.

int isDigit(char *in) { // Verify the input is a digit.
    int count = 0;
    // ^ Will be responsible for counding leading zeros... should there be any.
    for (int i = 0; in[0] == '0' && i < strlen(in); i++) {
        // ^ First checks if index 0 of the entered number string is a 0, if so, start the removal.
        if (in[i] == '0') {
            count++;
            // ^ Each time we find a 0 at the start of the string, we'll increment 'count' as the count of leading zeros
        } else {
            // ^ As soon as we find a non-zero, we start removing them and then move on to the rest of the method.
            for (int j = count; j <= strlen(in); j++) {
                // ^ Start iterating at the first index with a non-zero. This is so we don't iterate more than we need to
                // Next we check if the current index is greater or equal to the string length.
                // The off-by-one error here is actually intentional as the first index after the array is a null termination
                // character. We'll want to move that too so that we can actually shorten our array.
                in[j-count] = in[j];
                // ^ Rather than walking down 1 index at a time, we can just jump down the entire count of leading zero's
                // effectively removing all of them at once.
            }
        }
    }
    char *p = malloc(sizeof(char) * (strlen(in) + 1));
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

int parseSpaceSeperated(char *in, int *nums) {
    int begin = 0, count = 0;
    // ^ We need a number array of 5, a begin index marker to mark the start of a number, and the count of numbers found
    char *p = malloc(sizeof(in));
    // ^ We need a buffer that can handle the substrings we'll make to parse the spaces in the input.

    for (int i = 0; i < strlen(in); i++) {
        // ^ As long as i is less than the string length of the input and we haven't yet found 5 numbers, loop.
        if (in[i] == '\0')
            return count;
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
            if (in[i] == '\n' || count >= 5) {
                return count;
            }
            // If the found number was found by a newline, we are done. Break loop.
        }
    }
    return count;
    // ^ Just in-case size is 0
}
// ^ A method that takes in a buffer of possible numbers and, if all are numbers,
// the int array that was passed into the method will have it's values set to the numbers in the buffer.

int main() {
    char buff[80];
    int TOTAL_PROCESSES = 20, QUANTUM = 4, CURRENT_PROCESS, input[2], count, readyQueuePos = 0, currentTime = 0, completed = 0;

    printf("Enter the number of processes (20 or less): ");
    fgets(buff, sizeof(buff), stdin);
    if (!isDigit(buff)) {
        printf("Number entered was detected to not be a valid integer. Aborting.");
        return -1;
    }
    // ^ Characters entered were detected to not be numbers.

    TOTAL_PROCESSES = (atoi(buff) >= 0 && atoi(buff) <= 20) ? atoi(buff) : -1;
    if (TOTAL_PROCESSES == -1) {
        printf("Number entered was detected to not be within 0 to 20. Aborting.");
        return -2;
    }
    // ^ Integer entered was not from 0 to 20.

    Process processList[TOTAL_PROCESSES];
    Process readyQueue[TOTAL_PROCESSES];
    // ^ A list of all processes and then a readyQueue for all processes in the round-robin.

    int nextProcess = 0;
    // ^ Saving the index of the next process to lessen list iteration.
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        printf("Enter the Arrival Time and Total Burst Time for process %d seperated by a space", i);
        fgets(buff, sizeof(buff), stdin);
        count = parseSpaceSeperated(buff, &input);
        // ^ Parse the space seperate arrival and running time for the process.
        if (count != 2) {
            printf("Improper input detected. Did not enter exactly 2 arguments. Aborting");
            return -3;
        }
        // ^ If there aren't exactly 2 inputs, one for AT and one for RT, then abort the program.
        processList[i] = initProcess(i, input[0], input[1]);
        // ^ If input was valid, set the PID to the current loop, AT to the first input, and RT to the second.
        if (processList[nextProcess].ARRIVAL_TIME > processList[i].ARRIVAL_TIME) {
            nextProcess = i;
        }
        if (input[0] == 0) {
            readyQueue[readyQueuePos] = processList[i];
            readyQueuePos++;
        }
        // ^ If the AT of the program was set to 0, add it to the queue.
        buff[0] = '\0';
        // ^ Put nullterm at the first index of the buffer to "clear" the buffer.
    }
    // Making the processes
    for (int time = 0; completed < TOTAL_PROCESSES; time++) { // Main loop
        int currentQuantum = 0;
        if (time == processList[nextProcess].ARRIVAL_TIME) {
            // ^ If time quantum equals the arrival time of next process...
            readyQueue[readyQueuePos] = processList[nextProcess];
            nextProcess = 0;
            readyQueuePos++;
            // ^ Add the next process to the next spot in the ready queue, reset nextProcess to 0, so we iterate from the
            // beginning of the processList when looking for our next process,
            // and increment the next spot in the ready queue.
            for (int pro = 0; pro < TOTAL_PROCESSES; pro++) {
                // While the current process is less than the total (going by index)
                int running = 0;
                // This boolean is used for loop control.
                for (int run = 0; run <= readyQueuePos; run++) {
                    // ^ While
                    if (processList[pro].PID == readyQueue[run].PID) {
                        running = 1;
                        break;
                    }
                }
                if (running == 1)
                    continue;
                if (processList[pro].ARRIVAL_TIME < processList[nextProcess].ARRIVAL_TIME)
                    nextProcess = pro;
            }
        }
        // ^ This is for if the current time quantum matches the arrival time of a process that ISN'T running in the
        // process list.
        if (readyQueuePos == 0)
            continue;

        // ^ Above this will be the remaining time decrements and such from the ready que along with the time vs quantum counter
    }

    return 0;
}
