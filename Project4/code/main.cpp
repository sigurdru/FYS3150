#include "ising.hpp"
#include <cmath>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
    std::string fname = "test.txt";

    // MetropolisSampling inst(10);
    // inst.InitializeLattice();
    // inst.Solve(1000, 1.0, fname);
    double a = 2.3;
    std::cout << a  << std::endl;
    a += 1;
    std::cout << a  << std::endl;

    int b = 1;
    a += b;
    std::cout << a  << std::endl;


    return 0;
}
