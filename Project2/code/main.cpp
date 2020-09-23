#include "jacobi.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    int n;
    if (argc < 4) {
        std::cout << "Give me args" << std::endl;
        exit(1);
    }
    else {
        n = aroi(argv[1])
        n = pow(10, n) + 1;
        fname = argv[2];
        method = argv[3];
    }

    if (method == "TestJacobi") {
        exit(1);
    } 
    else if (method == "QM") {
        QM solver;
        float rho0 = 0;
        float rhoN = 10000;
        solver.initialize(n, rho0, rhoN);
        solver.solve();
    }


    // double a = 1.0;
    // double b = 2.0;
    // int N = 5;

    // JacobiRot inst;
    // inst.initialize(a, b, N);
    // inst.print_mat();
    // inst.solve(3.4);

    return 0;
}
