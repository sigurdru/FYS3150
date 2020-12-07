#define CATCH_CONFIG_MAIN
#include "tridiag.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Testing that the TriDiagSolver class works as expected")
{
    int n = 6;
    TriDiagSolver Solver(-1, 2, -1, n);
    double *u = new double[n+1];
    for (int i = 0; i <= n; i++) u[i] = 0.0;
    double *b = new double[n-1];
    for (int i = 0; i <= n-2; i++)
        b[i] = i + 1;
    b[n-2] = 6;
    double exact[n+1] = {0, 6, 11, 14, 14, 10};
    Solver.Solve(u, b);
    for (int i = 0; i <= n; i++)
        REQUIRE( u[i] == Approx(exact[i]).epsilon(1E-15) );
}
