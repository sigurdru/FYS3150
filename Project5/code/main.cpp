#include <iostream>
#include <cmath>
#include "solvers.hpp"

// Left boundary condition
double BoundaryLeft(double);
// Right boundary condition
double BoundaryRight(double);

int main(int charc, char* argv[])
{
    int Nx, Nt;
    double dt;
    std::string method, ResOutFileName;
    if (charc != 6) {
        std::cout << "Not enough arguments!" << std::endl
                  << "I take: Nx(int), Nt(int), dt(float), "
                  << "method(string), ResOutFileName(string)"
                  << std::endl;
        std::cout << "Acceptable method args:" << std::endl
                  << "- ForwardEuler" << std::endl
                  << "- BackwardEuler" << std::endl
                  << "- CrankNicolson" << std::endl;
        exit(1);
    }
    Nx = std::pow(10, atoi(argv[1]));
    Nt = std::pow(10, atoi(argv[2]));
    dt = std::pow(10, -atof(argv[3]));
    double L = 1.0;
    method = argv[4];
    ResOutFileName = argv[5];

    // Define initial conditions
    double initialCondition[Nx + 1];
    for (int i=0; i<Nx-1; i++)
        initialCondition[i] = 0.;
    initialCondition[Nx] = 1.;

    Parameters params{ Nx, Nt, dt, L, initialCondition, ResOutFileName };

    // Solve with desired solver
    if (method == "ForwardEuler") {
        // Solve using Forward Euler
        ForwardEuler ForwardSolver(params); 
        ForwardSolver.Solve_ForwardEuler(BoundaryLeft, BoundaryRight);
    }else if (method == "BackwardEuler") {
        // Solve using Backward Euler
        BackwardEuler BackwardSolver(params);
        BackwardSolver.Solve_BackwardEuler(BoundaryLeft, BoundaryRight);
    }else if (method == "CrankNicolson") {
        // Solve using Crank-Nicolson
        CrankNicolson CrankNicolsonSolver(params);
        CrankNicolsonSolver.Solve_CrankNicolson(BoundaryLeft, BoundaryRight);
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

double BoundaryRight(double t) {
    // Right boundary condition
    return 1.0;
}
double BoundaryLeft(double t) {
    // Left boundary condition
    return 0.0;
}
