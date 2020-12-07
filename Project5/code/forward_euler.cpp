#include <iostream>
#include "solvers.hpp"

void ForwardEuler::Initialize(int num_int_points, int num_time_points, float dtimestep) {
    L = 1;
    Nx = num_int_points;
    Nt = num_time_points;
    dt = dtimestep;
    dx = 1/(Nx + 1);
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

void ForwardEuler::CalcOneStep(int j) {
    // calculates the next timestep (j+1)
    for (int i = 1; i<Nx-1; i++) {
        u[i][j+1] = alpha*u[i-1][j] + 
                    (1 - 2*alpha)*u[i][j] + 
                    alpha*u[i+1][j];
    }
}

ForwardEuler::~ForwardEuler() {
    for (int i = 0; i<Nx; i++) 
        delete[] u[i];
    delete[] u;
}