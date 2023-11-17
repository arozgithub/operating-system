#include<iostream>
#include<cmath> // Include the cmath library for pow function
using namespace std;

float F(int N) {
    if (N == 0) {
        return 1.0;
    }
    float Farr[N]; // Define the array with size N
    Farr[0] = 1.0; // Initialize the first element
    float sum = 0.0; // Initialize sum with the first element
    cout<<"F("<<0<<")="<<Farr[0]<<endl;
    for (int i = 0; i <= N-1; i++) {
        sum = sum + Farr[i];
        Farr[i+1] = (pow(2.0, i+1.0) * sum) + (((i + 1.0) / 2.0) * sum);
        cout<<"F("<<i+1<<")="<<Farr[i+1];
        cout<<endl;
    }
    return Farr[N]; // Return the last element of the array
}

int main() {
    int n;
    cout << "Enter number: " ;
    cin >> n;
    cout<<endl;
    float f = F(n); // Call the function and store the result in f
    //cout << "F(" << n << ") = " << f << endl; // Print the result
    return 0; // Add a return statement to indicate successful execution
}
//--------------------------------------------------------below is simple code -----------------------------------------------------------------------------\\
//#include<iostream>
//#include<cmath> // Include the cmath library for pow function
//using namespace std;
//
//float F(int N) {
//    if (N == 0) {
//        return 1.0;
//    }
//    float Farr[N]; // Define the array with size N
//    Farr[0] = 1.0; // Initialize the first element
//    float sum = 0.0; // Initialize sum with the first element
//    for (int i = 0; i < N - 1; i++) {
//        sum = sum + Farr[i];
//        Farr[i + 1] = (pow(2.0, i + 1.0) * sum) + (((i + 1.0) / 2.0) * sum);
//    }
//    return Farr[N - 1]; // Return the last element of the array
//}
//
//int main() {
//    int n;
//    cout << "Enter number: " << endl;
//    cin >> n;
//    float f = F(n); // Call the function and store the result in f
//    cout << "F(" << n << ") = " << f << endl; // Print the result
//    return 0; // Add a return statement to indicate successful execution
//}

