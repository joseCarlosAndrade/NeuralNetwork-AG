#include <iostream>

using namespace std;

int * testFunction(int n) {
    int *vec = new int[n];
    for(int i=0 ; i<n ; i++) {
        vec[i] = i;
    }
    return vec;
}

int main() {
    int *test = testFunction(3);
    for(int i=0 ; i<3 ; i++) {
        cout << test[i] << endl;
    }
    delete test;
    return 0;
}