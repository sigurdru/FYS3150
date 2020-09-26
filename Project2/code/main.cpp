#include "jacobi.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    int n;
    std::string fname;
    std::string method;
    if (argc < 4) {
        std::cout << "Give me args" << std::endl;
        exit(1);
    }
    else {
        n = std::atoi(argv[1]);
        n = std::pow(10, n) + 1;
        fname = argv[2];
        method = argv[3];
    }

    QM solver;
    float rho0 = 0.;
    float rhoN = 5.;
    float eps = 1e-3;
    eps = 1e-6;
    solver.qm_initialize(n, rho0, rhoN);
    solver.solve(eps);
    return 0;
}
