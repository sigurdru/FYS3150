#include "ising.hpp"
#include <cmath>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
    std::string fname = "test.txt";

    MetropolisSampling inst(10);
    inst.InitializeLattice();
    inst.Solve(10, 1.0, fname);

    Analytical_2D ana;
    ana.find_theoretical_values(1.0);



    return 0;
}
