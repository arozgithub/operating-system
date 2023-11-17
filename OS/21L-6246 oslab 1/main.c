#include <stdio.h>
#include "util.h"

int main() {
    const char* inputFileName = "input.txt";
    const char* outputFileName = "output.txt";
    printf("Starting program...\n");

    removeNonAlphabets(inputFileName, outputFileName);
    printf("Starting finished...\n");

    return 0;
}

