
ForwardEuler::ForwardEuler(double dx, double dt, int n, double *InitialCondition)
{
    n = n;      // store the number of positional steps in an instance variable
    dt = dt;    // store the time step in an instance variable
    alpha = dt/(dx*dx);
    u_old = new double[n+1];
    u_new = new double[n+1];
    for (int i=0; i<=n; i++) u_new[i] = InitialCondition[i];
}

ForwardEuler::Solve(int NumTimeSteps, double BoundaryLeft(double))
{
    t = 0.0;
    for (jnt j=0; j<NumTimeSteps; j++) {
        // store the current values for later use before updating
        for (int i=0; i<=n; i++)
            u_old[i] = u_new[i];
        t += dt;
        u_new[0] = BoundaryLeft(t);
        u_new[n] = BoundaryRight(t);
        for (int i=1; i<n; i++)
            u_new[i] = alpha*u_old[i-1] + (1 - 2*alpha)*u_old[i] + alpha*u_old[i+1];
        WriteToFile();
    }
}
