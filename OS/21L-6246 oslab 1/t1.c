#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h> // Include ctype.h for isalpha
#include "util.h"
void removeNonAlphabets(const char* inputFileName, const char* outputFileName) {
    
    int inputFile = open(inputFileName, O_RDONLY);
    int outputFile = open(outputFileName, O_WRONLY | O_CREAT, 0644);

    if (inputFile == -1) {
        perror("Error: Unable to open input file");
        return;
    }

    if (outputFile == -1) {
        perror("Error: Unable to open output file");
        close(inputFile);
        return;
    }

    char c;
    while (read(inputFile, &c, 1) == 1) {
        if (isalpha(c)) {
            write(outputFile, &c, 1);
        }
    }
  printf(inputFile);
  printf(outputFile);
    close(inputFile);
    close(outputFile);
    
}



