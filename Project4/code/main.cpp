#include <omp.h>  //parallelization
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <string>
#include "ising.hpp"

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

    if (N_T > 1) {
        omp_set_num_threads(8); //set number of threads in parallel
            #pragma omp parallel for
            for (int i=0; i < N_T; i++) {
                usleep(5000 * omp_get_thread_num());
                double T = T_start + i*dT;
                MetropolisSampling solver(L, random_init, fname);
                solver.Solve(N_carl, T, WriteDuringSimulation);
                std::cout 
                          << " Temperature: " << T
                          << " Thread: "<< omp_get_thread_num()
                          << std::endl;
            }
    } else {
        double T = T_start;
        MetropolisSampling solve(L, random_init, fname);
        solve.Solve(N_carl, T, WriteDuringSimulation);
    }
    return 0;
}
