#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   

    int number = atoi(argv[1]);
    int square = number * number;
    
    printf("Square of %d is %d\n", number, square);

    return 0;
}

