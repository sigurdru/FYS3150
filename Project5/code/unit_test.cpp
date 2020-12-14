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
    double *b = new double[Nx-1];
    double *b_copy = new double[Nx-1];
    for (int i = 0; i <= Nx-2; i++) {
        b[i] = i + 1;
        b_copy[i] = i + 1;
    }
    b[Nx-2] = b_copy[Nx-2] = 6;
    double exact[Nx+1] = {0, 6, 11, 14, 14, 10};
    Solver.Solve(u, b);

    SECTION( "Checking that the results are as expected" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( u[i] == Approx(exact[i]).epsilon(RelTol) );
    }

    SECTION( "Checking that the RHS array is unchanged" )
    {
        for (int i = 0; i <= Nx-2; i++)
            REQUIRE( b[i] == b_copy[i] );
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

    Parameters params { Nx, Nt, dt, L, InitialCondition, fname };

    ForwardEuler Solver(params);
    SECTION( "Checking that the result array is initialized correctly" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(InitialCondition[i]).epsilon(RelTol) );
    }
    Solver.Solve_ForwardEuler(BoundaryLeft, BoundaryRight, 1);
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

    Parameters params { Nx, Nt, dt, L, InitialCondition, fname };
    BackwardEuler Solver(params);
    SECTION( "Checking that the result array is initialized correctly" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(InitialCondition[i]).epsilon(RelTol) );
    }
    Solver.Solve_BackwardEuler(BoundaryLeft, BoundaryRight, 1);
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

    Parameters params { Nx, Nt, dt, L, InitialCondition, fname };
    CrankNicolson Solver(params);
    SECTION( "Checking that the result array is initialized correctly" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(InitialCondition[i]).epsilon(RelTol) );
    }
    Solver.Solve_CrankNicolson(BoundaryLeft, BoundaryRight, 1);
    SECTION( "Checking that the results are as expected" )
    {
        for (int i = 0; i <= Nx; i++)
            REQUIRE( Solver.u[i] == Approx(Expected[i]).epsilon(RelTol) );
    }
    delete[] InitialCondition;
}
