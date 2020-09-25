#include "jacobi.hpp"
#include <cmath>
#include <catch2/catch.hpp>
#include <iostream>
#include <armadillo>

TEST_CASE("Testing index of max offdiagonal value and right eigenvalues") {
    int n = 5;
    double a = 5.;
    double b = 10.; 
    double *testm_a = new double[n-2];
    double *testm_d = new double[n-1];
    for (int i=0; i<n-2; i++){
        testm_a[i] = a;
        testm_d[i] = b;
    }
    testm_d[n-2] = b;

    JacobiRot scenario;
    scenario.initialize(testm_a, testm_d, n);
    SECTION( "testing right index" ) {
        int testm_k = 0;
        int testm_l = 1;
        REQUIRE(scenario.m_k == testm_k);
        REQUIRE(scenario.m_l == testm_l);
    }
    scenario.solve(1e-40);
    arma::vec eigv = arma::vec(n-1);
    SECTION( "Testing eigenvalues" ) {
        double tol = 0.5;
        for (int i=0; i<n-1; i++){
            eigv(i) = b + 2*a*std::cos((i+1)*3.1415/(n));
        }
        eigv = arma::sort(eigv, "ascend");
        
        for (int i=0; i<n-1; i++){
            REQUIRE(scenario.m_lambda[i] == Approx(eigv[i]).epsilon(tol));
        }

    }
}
