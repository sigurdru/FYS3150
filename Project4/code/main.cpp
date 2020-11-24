#include "ising.hpp"
#include <cmath>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
    int L, N_T, N_carl;
    bool random_init;
    float T_start, dT;
    char* init_argument;
    
    if (argc < 6) {
        std::cout << "Not enough arguments!" << std::endl
                  << "I take: L(int), T_start(float), dT(float), N_T(int), N_carl(int), Random_init(bool)" 
                  << std::endl;
        exit(1);
    }
    else {
        L = atoi(argv[1]);
        T_start = atof(argv[2]);
        dT = atof(argv[3]);
        N_T = atoi(argv[4]);
        N_carl = atoi(argv[5]);
        init_argument = argv[6];
        if (init_argument == "true") {
            random_init = true;
        }
        else {
            random_init = false;
        }
    }
    





    std::string fname = "test.txt";

    MetropolisSampling inst(10);
    inst.InitializeLattice(true);
    inst.Solve(100000, 2.0, fname);

    Analytical_2D ana;
    ana.find_theoretical_values(2.0);



    return 0;
}
