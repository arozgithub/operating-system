#include <iostream>
#include <cstdlib>

using namespace std;

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <integer1> <integer2> <integer3> ..." << endl;
        return 1;
    }

    int numArgs = argc - 1;
    int* numbers = new int[numArgs];

    for (int i = 0; i < numArgs; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    qsort(numbers, numArgs, sizeof(int), compare);

    cout << "Sorted integers: ";
    for (int i = 0; i < numArgs; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    delete[] numbers;
    return 0;
}
