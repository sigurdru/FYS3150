#include <iostream>
#include "solvers.hpp"

BackwardEuler::BackwardEuler(int num_int_points, int num_time_points, float dtimestep){
    L = 1;
    Nx = num_int_points;
    Nt = num_time_points;
    dt = dtimestep;
    dx = L/(Nx + 1);
    alpha = dt/dx/dx;
    u = new double*[Nx];
    for (int i = 0; i<Nx; i++) u[i] = new double[Nt];
    // Set initial conditions
    for (int i = 0; i<Nx; i++) u[i][0] = 0.0;
    for (int i = 0; i<Nt; i++) {
        u[0][i] = 0.0;
        u[Nx-1][i] = 1.0;
    }
}