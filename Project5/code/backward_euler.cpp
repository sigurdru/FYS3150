#include "solvers.hpp"
#include "tridiag.hpp"

BackwardEuler::BackwardEuler(Parameters params) {
    Initialize(params);
    b = new double[Nx - 1];
}

void BackwardEuler::Solve_BackwardEuler(
    double BoundaryLeft(double),
    double BoundaryRight(double),
    int NumberOfPrints
) {
    WriteToFile();
    TriDiagSolver Solver(-alpha, (1+2*alpha), -alpha, Nx);
    for (int j=0; j<Nt; j++) {
        ShouldIPrint(j, NumberOfPrints);
        // store the current values for later use before updating
        for (int i=0; i<=Nx-2; i++)
            b[i] = u[i+1];
        t = dt*j;
        u[0] = BoundaryLeft(t);
        u[Nx] = BoundaryRight(t);
        b[0] += alpha*u[0];
        b[Nx-2] += alpha*u[Nx];
        // call tridiag solver and update values in u
        Solver.Solve(u, b);
    }
    WriteToFile();
}

BackwardEuler::~BackwardEuler()
{
    delete[] u;
    delete[] b;
}
