#include <omp.h>  //parallelization
#include <unistd.h>
#include <cmath>
#include <iostream>
#include <string>
#include "ising.hpp"

int main(int argc, char* argv[]) {
    int L, N_T, N_carl, num_cores;
    bool random_init, WriteDuringSimulation;
    float T_start, dT;
    std::string init_argument, WriteDuringArg, fname;

    // argc is one larger than the number of additional arguments passed
    if (argc != 10) {
        std::cout << "Not enough arguments!" << std::endl
                  << "I take: L(int), T_start(float), dT(float), "
                  << "N_T(int), N_carl(int), Random_init(bool), "
                  << "WriteDuringSimulation(bool), fname(string)"
                  << "Number of cores during parallelization"
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
    num_cores = atoi(argv[9]);

    random_init = (init_argument == "true");
    WriteDuringSimulation = (WriteDuringArg == "true");

    double t_list[N_T];
    double E_values[N_T];
    double Mabs_values[N_T];
    double Cv_values[N_T];
    double chi_values[N_T];
    if (N_T > 1) 
    {   
        double OneOverTotNumSpins = 1.0/((double) L*L);
        std::cout << "Using: "<<num_cores<<" cores"<<std::endl;
        omp_set_num_threads(num_cores); //set number of threads in parallel
        #pragma omp parallel for
        for (int i=0; i < N_T; i++) {
            usleep(5000 * omp_get_thread_num());
            double T = T_start + i*dT;
            MetropolisSampling solver(L, random_init, fname);
            solver.Solve(N_carl, T, WriteDuringSimulation);
            solver.NormAndCalcExp(N_carl, T);
            t_list[i] = T;
            E_values[i] = solver.m_E*OneOverTotNumSpins;
            Mabs_values[i] = solver.m_Mabs*OneOverTotNumSpins;
            Cv_values[i] = solver.m_HeatCapacity;
            chi_values[i] = solver.m_MagneticSusceptibility;
            std::cout << "Process done: " 
                      << "|Iteration " << i << "| "
                      << "|Temperature: " << T << "| "
                      << "|Done by thread number: "<< omp_get_thread_num() << "|"
                      << std::endl;
        }
        // Print to file:
        std::ofstream ofile;
        std::string ofilename = "../output/";
        ofilename.append(fname).append(".csv");
        ofile.open(ofilename);
        ofile << "Temperature"
              << ",MeanEnergy"
              << ",Magnetization_Abs"
              << ",HeatCapacity"
              << ",MagneticSusceptibility" << std::endl;
        for (int i = 0; i<N_T; i++)
        {
            ofile << t_list[i] << "," 
                  << E_values[i] << "," 
                  << Mabs_values[i] << ","
                  << Cv_values[i] << ","
                  << chi_values[i]
                  << std::endl;
        }
        ofile.close();
    } else 
    {
        double T = T_start;
        MetropolisSampling solve(L, random_init, fname);
        solve.Solve(N_carl, T, WriteDuringSimulation);
    }
    return 0;
}
