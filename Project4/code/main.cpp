#include "ising.hpp"
#include <cmath>
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
    int L, N_T, N_carl;
    bool random_init, WriteDuringSimulation;
    float T_start, dT;
    std::string init_argument, WriteDuringArg, fname;

    // argc is one larger than the number of additional arguments passed
    if (argc != 9) {
        std::cout << "Not enough arguments!" << std::endl
                  << "I take: L(int), T_start(float), dT(float), "
                  << "N_T(int), N_carl(int), Random_init(bool), "
                  << "WriteDuringSimulation(bool), fname(string)"
                  << std::endl;
        exit(1);
    }
    L = atoi(argv[1]);
    T_start = atof(argv[2]);
    dT = atof(argv[3]);
    N_T = atoi(argv[4]);
    N_carl = atoi(argv[5]);
    init_argument = argv[6];
    WriteDuringArg = argv[7];
    fname = argv[8];

    random_init = (init_argument == "true");
    WriteDuringSimulation = (WriteDuringArg == "true");

    double T;
    for (int i=0; i < N_T; i++) {
        T = T_start + i*dT;
        MetropolisSampling solver(L, random_init, fname);
        solver.Solve(N_carl, T, WriteDuringSimulation);
    }

    return 0;
}
