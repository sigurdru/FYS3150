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
                  << "method(string), ResOutFileName(string),"
                  << std::endl;
        std::cout << "Acceptable method args:" << std::endl
                  << "- ForwardEuler" << std::endl
                  << "- BackwardEuler" << std::endl
                  << "- CrankNicolson" << std::endl
                  << "- TwoDimensions" << std::endl;
        exit(1);
    }
    Nx = std::pow(10, atoi(argv[1]));
    Nt = std::pow(10, atoi(argv[2]));
    dt = std::pow(10, -atof(argv[3]));
    double L = 1.0;
    int NumberOfPrints = 5;
    method = argv[4];
    ResOutFileName = argv[5];

    // Define initial conditions
    double *initialCondition;
    double **InitialConditions2D;
    if (method == "TwoDimensions"){
        // !!!DETTE MÅ FIKSES
        InitialConditions2D = new double*[Nx+1];
        for (int i=0; i<=Nx;i++){
            InitialConditions2D[i] = new double[Nx+1];
            for (int j=0; j<=Nx; j++){
                InitialConditions2D[i][j] = 0.;
            }
        }
    }else{
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
        TwoDimensions TwoDimensionsSolver(params, InitialConditions2D);
        TwoDimensionsSolver.Solve_TwoDimensions(NumberOfPrints);
    } else {
        std::cout << "Error: unknown method" << std::endl;
        std::cout << "Acceptable method args:" << std::endl
                  << "- ForwardEuler" << std::endl
                  << "- BackwardEuler" << std::endl
                  << "- CrankNicolson" << std::endl
                  << "- TwoDimensions" << std::endl;
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
