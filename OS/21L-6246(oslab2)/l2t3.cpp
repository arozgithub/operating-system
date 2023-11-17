#include <iostream>
#include <cstdlib>
using namespace std;


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <integer1> <integer2> <integer3> ..." << endl;
        return 1;
    }
    int sum=0;
    int avg;
    int numArgs = argc - 1;
    int* numbers = new int[numArgs];

    for (int i = 0; i < numArgs; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    for (int i = 0; i < numArgs; i++) {
       sum=numbers[i]+sum;
    }
    
    cout << sum<<endl;
    avg=sum/numArgs;
    cout<<avg<<endl;

    delete[] numbers;
    return 0;
}
