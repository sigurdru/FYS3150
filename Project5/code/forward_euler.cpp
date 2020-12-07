#include "solvers.hpp"
#include <iostream>

ForwardEuler::ForwardEuler(int num_int_points,
                           int num_time_points,
                           float dtimestep,
                           double* InitialCondition,
                           std::string ResOutFileName) {

    double L = 1;
    Nx = num_int_points;    // store the number of positional steps in an instance variable
    Nt = num_time_points;
    dx = L/Nx;
    dt = dtimestep;         // store the time step in an instance variable
    alpha = dt/dx/dx;
    u = new double[Nx + 1];
    b = new double[Nx + 1];
    for (int i = 0; i <= Nx; i++)
        u[i] = InitialCondition[i];
}

void ForwardEuler::Solve_ForwardEuler(double BoundaryLeft(double),
                                    double BoundaryRight(double)) {
  for (int j = 0; j < Nt; j++) {
    // store the current values for later use before updating
    for (int i = 0; i <= Nx; i++)
      b[i] = u[i];
    t = dt*j;
    u[0] = BoundaryLeft(t);
    u[Nx] = BoundaryRight(t);
    for (int i = 1; i < Nx; i++)
      u[i] = alpha * b[i - 1] + (1 - 2 * alpha) * b[i] +
                 alpha * b[i + 1];
    // WriteToFile();
  }
}

ForwardEuler::~ForwardEuler() {
    delete[] u;
    delete[] b;
}
