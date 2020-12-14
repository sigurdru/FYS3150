#include "solvers.hpp"
#include "tridiag.hpp"

CrankNicolson::CrankNicolson(int num_int_points,
                             int num_time_points,
                             float dtimestep,
                             double* InitialCondition,
                             std::string ResOutFileName)
{
    // store parameters in instance variables
    L = 1.0;
    Nx = num_int_points;
    Nt = num_time_points;
    dt = dtimestep;
    dx = L/Nx;
    ResOutFileName = ResOutFileName;
    alpha = dt/(dx*dx);
    t = 0;
    b = new double[Nx-1];
    u = new double[Nx+1];
    for (int i=0; i<=Nx; i++) u[i] = InitialCondition[i];
}

void CrankNicolson::Solve_CrankNicolson(double BoundaryLeft(double),
                                        double BoundaryRight(double))
{
    WriteToFile();
    TriDiagSolver Solver(-alpha, (2+2*alpha), -alpha, Nx);
    for (int j=0; j<Nt; j++) {
        ShouldIPrint(j);
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
    }
    // Last result
    WriteToFile();
}

CrankNicolson::~CrankNicolson()
{
    delete[] u;
    delete[] b;
}
