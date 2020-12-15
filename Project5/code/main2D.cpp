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

    double L = 1.0;
    Nx = 100;
    Nt = 10000;
    double dx = L/Nx;
    dt = 0.1*dx*dx;
    ResOutFileName = "test2D";
    int numCores = 8;
    // std::cout << "Nx: " << Nx << std::endl;
    // std::cout << "Nt: " << Nt << std::endl;

    // Define initial conditions
    double *InitialConditions2D;
    InitialConditions2D = new double[(Nx+1)*(Nx+1)];
    for (int i = 0; i <= Nx; i++){
        for (int j = 0; j <= Nx; j++)
            InitialConditions2D[TwoDimensions::Index2D(i, Nx+1, j)] = 0.0;
    }
    for (int i = 1; i <= Nx-1; i++){
        for (int j = 1; j <= Nx/2; j++)
            InitialConditions2D[TwoDimensions::Index2D(i, Nx+1, j)] = 0.5;
    }

    Parameters params{ Nx, Nt, dt, L, ResOutFileName };

    // Solve two dimensional problem using Forward Euler
    TwoDimensions Solver(params, InitialConditions2D, numCores);
    Solver.Solve();

    delete[] InitialConditions2D;

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
