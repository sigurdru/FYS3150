#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "tridiag.hpp"
#include "forward_euler.hpp"

TEST_CASE("Checking that the TriDiagSolver class works as expected")
{
    int n = 6;
    TriDiagSolver Solver(-1, 2, -1, n);
    double *u = new double[n+1];
    for (int i = 0; i <= n; i++) u[i] = 0.0;
    double *b = new double[n-1];
    double *b_copy = new double[n-1];
    for (int i = 0; i <= n-2; i++) {
        b[i] = i + 1;
        b_copy[i] = i + 1;
    }
    b[n-2] = b_copy[n-2] = 6;
    double exact[n+1] = {0, 6, 11, 14, 14, 10};
    Solver.Solve(u, b);

    SECTION( "Checking that the results are as expected" )
    {
        for (int i = 0; i <= n; i++)
            REQUIRE( u[i] == Approx(exact[i]).epsilon(1E-15) );
    }

    SECTION( "Checking that the RHS array is unchanged" )
    {
        for (int i = 0; i <= n-2; i++)
            REQUIRE( b[i] == b_copy[i] );
    }

    delete[] u;
    delete[] b;
}

TEST_CASE( "Checking that the ForwardEuler class works as expected" )
{
    int n = 10;
    // alpha = dt/dx^2 = 2
    int dt = 8;
    int dx = 2;

    double Boundary(double x) {return 0.0;}

    double *InitialCondition = new double[n+1];
    for (int i = 0; i <= n; i++) InitialCondition[i] = i;
    ForwardEuler Solver(dx, dt, n, InitialCondition);
    Solver.solve(1, Boundary, Boundary);
}
