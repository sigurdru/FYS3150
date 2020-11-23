#include "ising.hpp"
#include <cmath>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
    std::string fname = "test.txt";

    MetropolisSampling inst(2);
    inst.InitializeLattice();
    inst.Solve(10000, 1.0, fname);

    Analytical_2D ana;
    ana.find_theoretical_values(1.0);



    return 0;
}
