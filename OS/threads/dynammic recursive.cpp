#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
//ALAWAYS MAKE CODE BY CHECING AND RUNNING 1ST VALUE OF THE ARRAY
vector<float> memo; // Memoization table to store intermediate results

float F(int N) {
    if (N == 0) {
        return 1.0;
    }

    // If the result for N is already calculated, return it from the memo table
    if (memo[N] != 0.0) {
        return memo[N];
    }

    float sum = 0.0;
    for (int i = 0; i <=N-1; i++) {
        sum += F(i);
    }

    // Recursive dynamic programming formula
    float result = pow(2.0, N) * sum + ((N / 2.0) * sum);
    
    // Store the result in the memo table for future reference
    memo[N] = result;

    return result;
}

int main() {
    int n;
    cout << "Enter number: " << endl;
    cin >> n;

    // Initialize memoization table with zeros
    memo.resize(n + 1, 0.0);

    float f = F(n); // Call the function and store the result in f
    cout << "F(" << n << ") = " << f << endl; // Print the result
    return 0; // Add a return statement to indicate successful execution
}

