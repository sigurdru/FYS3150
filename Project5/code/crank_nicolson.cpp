#include "solvers.hpp"
#include "tridiag.hpp"

CrankNicolson::CrankNicolson(Parameters params) {
    Initialize(params);
    ProduceFName("CrankNicolson");
    b = new double[Nx-1];
}

void CrankNicolson::Solve_CrankNicolson(double BoundaryLeft(double),
                                        double BoundaryRight(double))
{
    TriDiagSolver Solver(-alpha, (2+2*alpha), -alpha, Nx);
    for (int j=0; j<Nt; j++) {
        // store the current values for later use before updating
        for (int i=0; i<=Nx-2; i++)
            b[i] = alpha*u[i] + (2-2*alpha)*u[i+1] + alpha*u[i+2];
        t = dt*j;
        u[0] = BoundaryLeft(t);
        u[Nx] = BoundaryRight(t);
        b[0] += alpha*u[0];
        b[Nx-2] += alpha*u[Nx];
        // call tridiag solver and update values in u
        Solver.Solve(u, b);
        WriteToFile();
    }
}

CrankNicolson::~CrankNicolson()
{
    delete[] u;
    delete[] b;
}
