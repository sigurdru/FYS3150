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
                  << "I take: L(int), T_start(float), dT(float), "
                  << "N_T(int), N_carl(int), Random_init(bool)"
                  << std::endl;
        exit(1);
    }
    L = atoi(argv[1]);
    T_start = atof(argv[2]);
    dT = atof(argv[3]);
    N_T = atoi(argv[4]);
    N_carl = atoi(argv[5]);
    init_argument = argv[6];
    spin_plot_arg = argv[7];

    random_init = (init_argument == "true");
    spin_plot = (spin_plot_arg == "true");

    double T;
    for (int i=0; i<=N_T; i++) {
        T = T_start + i*dT;
        MetropolisSampling inst(L, random_init);
        inst.Solve(N_carl, T, spin_plot);
    }

    return 0;
}
