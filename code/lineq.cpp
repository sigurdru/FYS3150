#include <iostream>
#include <cmath>
#include <stdlib.h>

inline double f (double x) {return 100.0*exp(-10.0*x);}

int main (int argc, char* argv[]) {
    int n = 10;
    srand(1);       // random seed
    double a[n-1];
    double b[n];
    double c[n-1];

    for (int i=0; i<n-1; i++) {
        a[i] = rand();
        b[i] = rand();
        c[i] = rand();
    }
    b[n-1] = 3;

    for (int i=0; i<n-1; i++) {
        std::cout << a[i] << "  "
            << b[i] << "  " << 

    return 0;
}
