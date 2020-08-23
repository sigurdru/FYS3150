#include <iostream>
#include <cmath>
#include <stdlib.h>

inline double f (double x) {return 100.0*exp(-10.0*x);}

inline double exact (double x) {return 1.0 - (1.0 - exp(-10.0))*x - exp(-10*x);}

int main (int argc, char* argv[]) {
    int n;
    double h;
    if (argc < 2) {
        std::cout << "Give me args" << std::endl;
        exit(1);
    }
    else {
        n = atoi(argv[1]);
        h = 1.0/(n-1);
    }
    double *x = new double[n];
    for (int i=0; i<n; i++) {
        x[i] = i*h;
    }

    double *a = new double[n-1];
    double *b = new double[n];
    double *c = new double[n-1];
    double *alpha = new double[n-1];
    double *rho = new double[n];
    double *b_tilde = new double[n];
    double *v = new double[n];

    for (int i=0; i<n-1; i++) {
        a[i] = -1;
        b[i] = 2;
        c[i] = -1;
        b_tilde[i] = pow(h, 2)*f(x[i]); 
    }
    b[n-1] = 2;
    b_tilde[n-1] = f(x[n-1]);
    
    // forward sub
    alpha[0] = c[0]/b[0];
    rho[0] = b_tilde[0]/b[0];
    for (int i=1; i<n; i++) {
        rho[i] = (b_tilde[i] - rho[i-1]*a[i-1])/(b[i] - alpha[i-1]*a[i-1]);
        alpha[i] = c[i]/(b[i] - alpha[i-1]*a[i-1]);
    }

    // backward substitution
    v[n-1] = rho[n-1];
    for (int i=n; i>0; i--) {
        v[i-1] = rho[i-1] - alpha[i-1]*v[i];
    }

    // output the results, | computed | exact |
    std::cout << "x,computed,exact" << std::endl;    // h
    for (int i=0; i<n; i++) {
        std::cout << x[i] << "," << v[i] << ","
            << exact(x[i]) << std::endl;
    }

    // cleanup
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] alpha;
    delete [] rho;
    delete [] b_tilde;
    delete [] v;
    delete [] x;

    return 0;
}
