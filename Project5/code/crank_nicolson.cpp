#include "solvers.hpp"
#include "tridiag.hpp"

CrankNicolson::CrankNicolson(Parameters params, double* initialCondition) {
    Initialize(params);
    u = new double[Nx + 1];
    b = new double[Nx + 1];
    for (int i = 0; i <= Nx; i++)
        u[i] = initialCondition[i];
}

void CrankNicolson::Solve(
    double BoundaryLeft(double),
    double BoundaryRight(double),
    int NumberOfPrints
) {
    WriteToFile();
    TriDiagSolver Solver(-alpha, (2+2*alpha), -alpha, Nx);
    bool ShouldPrint;
    for (int j=0; j<Nt; j++) {
        // store the current values for later use before updating
        for (int i=0; i<=Nx-2; i++)
            b[i] = alpha*u[i] + (2-2*alpha)*u[i+1] + alpha*u[i+2];
        t = dt*j;
        u[0] = BoundaryLeft(t);
        u[Nx] = BoundaryRight(t);
        // call tridiag solver and update values in u
        Solver.Solve(u, b);
        ShouldPrint = (j%(Nt/NumberOfPrints + 1) == 0);
        if (ShouldPrint) WriteToFile();
    }
    // Last result
    WriteToFile();
}

CrankNicolson::~CrankNicolson()
{
    delete[] u;
    delete[] b;
}
