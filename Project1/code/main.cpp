#include "lineq.hpp"
#include <iostream>
#include <cmath>
#include <string>

inline double f (double x) {return 100.0*exp(-10.0*x);}

inline double exact (double x) {return 1.0 - (1.0 - exp(-10.0))*x - exp(-10*x);}

int main (int argc, char* argv[]) {
    int n;
    std::string fname;
    std::string algorithm;
    if (argc < 4) {
        std::cout << "Give me args" << std::endl;
        exit(1);
    }
    else {
        n = atoi(argv[1]);
        n = pow(10, n) + 1;
        fname = argv[2];
        algorithm = argv[3];
    }

    if (algorithm == "slow") {
        double *a = new double[n-1];
        double *b = new double[n];
        double *c = new double[n-1];

        b[0] = 2;
        for (int i=0; i<n-1; i++) {
            a[i] = -1;
            b[i+1] = 2;
            c[i] = -1;
        }
        SlowLineq solver;
        solver.initialize(a, b, c, n, f, exact);
        solver.solve();
        if (fname != "no_print") {
            solver.write_to_file(fname);
        }
    } else if (algorithm == "fast") {
        FastLineq solver;
        solver.initialize(n, f, exact);
        solver.solve();
        if (fname != "no_print") {
            solver.write_to_file(fname);
        }
    } 
    else if (algorithm == "LU") {
        LULineq solver;
        solver.solve(n, f, exact);
        if (fname != "no_print") {
            solver.write_to_file(fname);
        }
    }
    else {
        std::cout << "Unrecognized description of algorithm: "
            << algorithm << std::endl;
        exit(1);
    }
}
