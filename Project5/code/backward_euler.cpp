#include "diffusion.hpp"

BackwardEuler::BackwardEuler(double dx, double dt, int n, double *InitialCondition)
{
    n = n;      // store the number of positional steps in an instance variable
    dt = dt;    // store the time step in an instance variable
    alpha = dt/(dx*dx);
    b = new double[n-1];
    u = new double[n+1];
    for (int i=0; i<=n; i++) u_new[i] = InitialCondition[i];
}

ForwardEuler::Solve(int NumTimeSteps, double BoundaryLeft(double))
{
    t = 0.0;
    TriDiagSolver Solver(-alpha, (1+2*alpha), -alpha, n);
    for (jnt j=0; j<NumTimeSteps; j++) {
        // store the current values for later use before updating
        for (int i=0; i<=n-2; i++)
            b[i] = u[i+1];
        t += dt;
        u[0] = BoundaryLeft(t);
        u[n] = BoundaryRight(t);
        b[0] += alpha*u[0];
        b[n-2] += alpha*u[n];
        // call tridiag solver and update values in u
        Solver(u, b);
        WriteToFile();
    }
}

BackwardEuler::~BackwardEuler()
{
    delete[] u;
    delete[] b;
}
