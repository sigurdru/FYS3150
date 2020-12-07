#include <iostream>
#include "solvers.hpp"

int main(int charc, char* argv[])
{
    int Nx;
    int Nt;
    double dt;
    std::string method;
    if (charc != 5) {
        std::cout << "Not enough arguments!" << std::endl
                  << "I take: Nx(int), Nt(int), dt(float), "
                  << "method(string)"
                  << std::endl;
        std::cout << "Acceptable method args:" << std::endl
                  << "- ForwardEuler" << std::endl
                  << "- BackwardEuler" << std::endl
                  << "- CrankNicolson" << std::endl;
        exit(1);
    }
    Nx = atoi(argv[1]);
    Nt = atoi(argv[2]);
    dt = atof(argv[3]);
    method = argv[4];


    if (method == "ForwardEuler") {
        ForwardEuler ForwardSolver;
        ForwardSolver.Initialize(Nx, Nt, dt);
        for (int i=0; i<Nt-1; i++){
            ForwardSolver.CalcOneStep(i);
        }
    }else if (method == "BackwardEuler") {
        exit(1);
    }else if (method == "CrankNicolson") {
        exit(1);
    }else {
        std::cout << "Error: unknown method" << std::endl;
        std::cout << "Acceptable method args:" << std::endl
                  << "- ForwardEuler" << std::endl
                  << "- BackwardEuler" << std::endl
                  << "- CrankNicolson" << std::endl;
        exit(1);
    }
    return 0;
}