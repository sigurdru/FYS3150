#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "tridiag.hpp"
#include "solvers.hpp"
#include <string>

double RelTol = 1E-6;

TEST_CASE("Checking that the TriDiagSolver class works as expected")
{
    int Nx = 6;
    TriDiagSolver Solver(-1, 2, -1, Nx);
    double *u = new double[Nx+1];
    for (int i = 0; i <= Nx; i++) u[i] = 0.0;
    u[0] = 1.0;
    u[Nx] = 2.0;

    double *b = new double[Nx-1] { 0, 2, 3, 4, 4 };
    double *b_copy = new double[Nx-1];
    for (int i = 0; i <= Nx-2; i++)b_copy[i] = b[i];

    double exact[Nx+1] = {1, 6, 11, 14, 14, 10, 2};
    Solver.Solve(u, b);

    SECTION( "Checking that the results are as expected" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( u[i] == Approx(exact[i]).epsilon(RelTol) );
    }

    SECTION( "Checking that the RHS array is correct" )
    {
        for (int i = 1; i <= Nx-3; i++)
            REQUIRE( b[i] == b_copy[i] );
        REQUIRE( b[0] == (b_copy[0] + u[0]) );
        REQUIRE( b[Nx-2] == (b_copy[Nx-2] + u[Nx]) );
    }

    delete[] u;
    delete[] b;
    delete[] b_copy;
}

// boundary values for the tests
double BoundaryLeft(double x) {return 1.0;}
double BoundaryRight(double x) {return 2.0;}

TEST_CASE( "Checking that the ForwardEuler class works as expected" )
{
    int Nx = 10;
    int Nt = 1;
    double dx = 1.0/Nx;
    // alpha = dt/dx^2 = 2
    double dt = 2.0*dx*dx;
    double L = 1.0;
    std::string fname = "blabla";

    double *InitialCondition = new double[Nx+1]
        {0, 1, 2, 3, 4, 5, 3, 2, 1, 4, 6};
    double Expected[Nx+1] = { 1., 1., 2., 3., 4., -1., 5., 2., 9., 2., 2.};

    Parameters params { Nx, Nt, dt, L, fname };

    ForwardEuler Solver(params, InitialCondition);
    SECTION( "Checking that the result array is initialized correctly" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(InitialCondition[i]).epsilon(RelTol) );
    }
    Solver.Solve(BoundaryLeft, BoundaryRight, 1);
    SECTION( "Checking that the results are as expected" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(Expected[i]).epsilon(RelTol) );
    }
    delete[] InitialCondition;
}

TEST_CASE( "Checking that the BackwardEuler class works as expected" )
{
    int Nx = 5;
    int Nt = 1;
    double dx = 1.0/Nx;
    // alpha = dt/dx^2 = 2
    double dt = 2.0*dx*dx;
    double L = 1.0;
    std::string fname = "blabla";

    double *InitialCondition = new double[Nx+1] {1, 14, -10, 18, 4, 2};
    double Expected[Nx+1] = {1, 4, 2, 6, 4, 2};

    Parameters params { Nx, Nt, dt, L, fname };
    BackwardEuler Solver(params, InitialCondition);
    SECTION( "Checking that the result array is initialized correctly" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(InitialCondition[i]).epsilon(RelTol) );
    }
    Solver.Solve(BoundaryLeft, BoundaryRight, 1);
    SECTION( "Checking that the results are as expected" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(Expected[i]).epsilon(RelTol) );
    }
    delete[] InitialCondition;
}

TEST_CASE( "Checking that the CrankNicolson class works as expected" )
{
    int Nx = 5;
    int Nt = 1;
    double dx = 1.0/Nx;
    // alpha = dt/dx^2 = 2
    double dt = 2.0*dx*dx;
    double L = 1.0;
    std::string fname = "blabla";

    double *InitialCondition = new double[Nx+1] {1, 6, 14, 4, 2, 2};
    double Expected[Nx+1] = {1, 4, 2, 6, 4, 2};

    Parameters params { Nx, Nt, dt, L, fname };
    CrankNicolson Solver(params, InitialCondition);
    SECTION( "Checking that the result array is initialized correctly" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(InitialCondition[i]).epsilon(RelTol) );
    }
    Solver.Solve(BoundaryLeft, BoundaryRight, 1);
    SECTION( "Checking that the results are as expected" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(Expected[i]).epsilon(RelTol) );
    }
    delete[] InitialCondition;
}

TEST_CASE( "Checking that the TwoDimensions class works as expected" )
{
    int Nx = 4;
    double dx = 1.0/Nx;
    // alpha = dt/dx^2 = 2
    double dt = 2.0*dx*dx;
    double L = 1.0;
    std::string fname = "blabla";
    for (int numCores = 1; numCores <= 2; numCores++) {
        for (int Nt = numCores; Nt <= 2; Nt ++) {

            double *initialCondition;
            double *expected;

            initialCondition = new double[(Nx+1)*(Nx+1)]
                {   0.0, 0.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 2.0, 3.0, 0.0,
                    0.0, 4.0, 5.0, 6.0, 0.0,
                    0.0, 7.0, 8.0, 9.0, 0.0,
                    0.0, 0.0, 0.0, 0.0, 0.0
            };
            if (Nt == 1) {
                expected = new double[(Nx+1)*(Nx+1)]
                    {   0.0,   0.0,   0.0,   0.0, 0.0,
                        0.0,   5.0,   4.0,  -5.0, 0.0,
                        0.0,  -2.0,   5.0,  -8.0, 0.0,
                        0.0, -25.0, -14.0, -35.0, 0.0,
                        0.0,   0.0,   0.0,   0.0, 0.0
                };
            } else {
                expected = new double[(Nx+1)*(Nx+1)]
                    {   0.0,   0.0,   0.0,   0.0, 0.0,
                        0.0, -31.0, -18.0,  27.0, 0.0,
                        0.0, -16.0, -75.0, -14.0, 0.0,
                        0.0, 143.0, -12.0, 201.0, 0.0,
                        0.0,   0.0,   0.0,   0.0, 0.0
                };
            }
            Parameters params { Nx, Nt, dt, L, fname };
            TwoDimensions Solver(params, initialCondition, numCores);
            SECTION( "Checking that the result array is initialized correctly" )
            {
                for (int i = 0; i <= (Nx+1)*(Nx+1)-1; i++)
                    REQUIRE(
                        Solver.u[0][i] == Approx(initialCondition[i]).epsilon(RelTol)
                    );
                for (int core = 1; core <= numCores; core++) {
                    for (int i = 0; i <= (Nx+1)*(Nx+1)-1; i++)
                        REQUIRE( Solver.u[core][i] == Approx(0.0).epsilon(RelTol) );
                }
            }
            Solver.Solve();
            SECTION( "Checking that the results are as expected" )
            {
                for (int i = 0; i <= (Nx+1)*(Nx+1)-1; i++)
                    REQUIRE(
                        Solver.u[0][i] == Approx(expected[i]).epsilon(RelTol)
                    );
                for (int core = 1; core <= numCores; core++) {
                    for (int i = 0; i <= (Nx+1)*(Nx+1)-1; i++)
                        REQUIRE( Solver.u[core][i] == Approx(0.0).epsilon(RelTol) );
                }
            }
            delete[] initialCondition;
            delete[] expected;
        }
    }
}
