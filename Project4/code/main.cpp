#include "ising.hpp"
#include <cmath>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
    int L, N_T, N_carl;
    bool random_init, spin_plot;
    float T_start, dT;
    std::string init_argument, spin_plot_arg;

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
        spin_plot_arg = argv[7];
        if (init_argument == "true") {
            random_init = true;
        }
        else {
            random_init = false;
        }
        if (spin_plot_arg == "true")
            spin_plot = true;
        else 
            spin_plot = false;
    }

    std::string fname = "test.txt";

    MetropolisSampling inst(L, random_init);
    inst.Solve(N_carl, T_start, spin_plot);

    Analytical_2D ana;
    ana.find_theoretical_values(2.0);



    return 0;
}
