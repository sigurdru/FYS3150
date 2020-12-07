#include "lineq.hpp"
#include <iostream>
#include <cmath>
#include <string>

double f (double x) {
    double y;
    if (x < 0.17) {
        y = 1.0;
    } else if (x < 0.34) {
        y = 2.0;
    } else if (x < 0.51) {
        y = 3.0;
    } else if (x < 0.68) {
        y = 4.0;
    } else {
        y = 6.0;
    }
    return 6*6*y;
}

double exact (double x) {
    double y;
    if (x < 0.1) {
        y = 0.0;
    } else if (x < 0.17) {
        y = 6.0;
    } else if (x < 0.34) {
        y = 11.0;
    } else if (x < 0.51) {
        y = 14.0;
    } else if (x < 0.68) {
        y = 14.0;
    } else if (x < 0.85) {
        y = 10.0;
    } else {
        y = 0.0;
    }
    return y;
}

int main (int argc, char* argv[]) {
    int n = 7;
    std::string fname;
    std::string algorithm;
    if (argc < 3) {
        std::cout << "Give me args" << std::endl;
        exit(1);
    }
    else {
        fname = argv[1];
        algorithm = argv[2];
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
        solver.write_to_file(fname);
    } else if (algorithm == "fast") {
        FastLineq solver;
        solver.initialize(n, f, exact);
        solver.solve();
        solver.write_to_file(fname);
    } else if (algorithm == "LU") {
    	LULineq solver;
    	solver.solve(n, f, exact);
    	solver.write_to_file(fname);
    } else {
        std::cout << "Unrecognized description of algorithm: "
            << algorithm << std::endl;
        exit(1);
    }
}
