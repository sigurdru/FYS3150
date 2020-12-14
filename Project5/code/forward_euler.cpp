#include "solvers.hpp"
#include <iostream>

ForwardEuler::ForwardEuler(Parameters params) {
    Initialize(params);
    ProduceFName("ForwardEuler");
    b = new double[Nx + 1];
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
    WriteToFile();
    }
}

ForwardEuler::~ForwardEuler() {
    delete[] u;
    delete[] b;
}
