#include "solvers.hpp"
#include "tridiag.hpp"

BackwardEuler::BackwardEuler(Parameters params, double* initialCondition) {
    Initialize(params);
    u = new double[Nx + 1];
    b = new double[Nx + 1];
    for (int i = 0; i <= Nx; i++)
        u[i] = initialCondition[i];
}

void BackwardEuler::Solve(
    double BoundaryLeft(double),
    double BoundaryRight(double),
    int NumberOfPrints
) {
    WriteToFile();
    TriDiagSolver Solver(-alpha, (1+2*alpha), -alpha, Nx);
    bool ShouldPrint;
    for (int j=0; j<Nt; j++) {
        // store the current values for later use before updating
        for (int i=0; i<=Nx-2; i++)
            b[i] = u[i+1];
        t = dt*j;
        u[0] = BoundaryLeft(t);
        u[Nx] = BoundaryRight(t);
        // call tridiag solver and update values in u
        Solver.Solve(u, b);
        ShouldPrint = (j%(Nt/NumberOfPrints + 1) == 0);
        if (ShouldPrint) WriteToFile();
    }
    WriteToFile();
}

BackwardEuler::~BackwardEuler()
{
    delete[] u;
    delete[] b;
}
