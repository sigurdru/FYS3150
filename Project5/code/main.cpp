#include <iostream>
#include <cmath>
#include "solvers.hpp"

// Left boundary condition
double BoundaryLeft(double);
// Right boundary condition
double BoundaryRight(double);

int main(int charc, char* argv[])
{
    int Nx, Nt, numCores;
    double dt;
    std::string method, ResOutFileName;
    if (charc != 7) {
        std::cout << "Not enough arguments!" << std::endl
                  << "I take: Nx(int), Nt(int), dt(float), "
                  << "method(string), numCores(int), ResOutFileName(string)"
                  << std::endl;
        std::cout << "Acceptable method args:" << std::endl
                  << "- ForwardEuler" << std::endl
                  << "- BackwardEuler" << std::endl
                  << "- CrankNicolson" << std::endl
                  << "- TwoDimensions" << std::endl;
        exit(1);
    }
    Nx = atoi(argv[1]);
    Nt = atoi(argv[2]);
    dt = atof(argv[3]);
    method = argv[4];
    numCores = atoi(argv[5]);
    ResOutFileName = argv[6];
    double L = 1.0;
    int NumberOfPrints = 6;

    // Define initial conditions
    double *initialCondition;
    if (method == "TwoDimensions") {
        initialCondition = new double[(Nx+1)*(Nx+1)];
        for (int i = 0; i <= Nx; i++) {
            for (int j = 0; j <= Nx; j++)
                initialCondition[TwoDimensions::Index2D(i, Nx+1, j)] = 0.0;
        }
        for (int i = 1; i <= Nx-1; i++) {
            for (int j = 1; j <= Nx/2; j++)
                initialCondition[TwoDimensions::Index2D(i, Nx+1, j)] = 1.0;
        }
    } else {
        initialCondition = new double[Nx + 1];
        for (int i=0; i<Nx-1; i++)
            initialCondition[i] = 0.;
        initialCondition[Nx] = 1.;
    }

    Parameters params{ Nx, Nt, dt, L, ResOutFileName };

    // Solve with desired solver
    if (method == "ForwardEuler") {
        // Solve using Forward Euler
        ForwardEuler ForwardSolver(params, initialCondition);
        ForwardSolver.Solve(BoundaryLeft, BoundaryRight, NumberOfPrints);
    } else if (method == "BackwardEuler") {
        // Solve using Backward Euler
        BackwardEuler BackwardSolver(params, initialCondition);
        BackwardSolver.Solve(BoundaryLeft, BoundaryRight, NumberOfPrints);
    } else if (method == "CrankNicolson") {
        // Solve using Crank-Nicolson
        CrankNicolson CrankNicolsonSolver(params, initialCondition);
        CrankNicolsonSolver.Solve(BoundaryLeft, BoundaryRight, NumberOfPrints);
    } else if (method == "TwoDimensions") {
        // Solve two dimensional problem using Forward Euler
        TwoDimensions TwoDimensionsSolver(params, initialCondition, numCores);
        TwoDimensionsSolver.Solve(2);
    } else {
        std::cout << "Error: unknown method " << method << std::endl;
        std::cout << "Acceptable method args:" << std::endl
                  << "- ForwardEuler" << std::endl
                  << "- BackwardEuler" << std::endl
                  << "- CrankNicolson" << std::endl
                  << "- TwoDimensions" << std::endl;
        delete[] initialCondition;
        exit(1);
    }

    delete[] initialCondition;
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
