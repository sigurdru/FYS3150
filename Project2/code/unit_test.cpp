#define CATCH_CONFIG_MAIN
#include "jacobi.hpp"
#include <cmath>
#include <catch2/catch.hpp>
#include <iostream>
#include <armadillo>

TEST_CASE("Testing index of max offdiagonal value and right eigenvalues") {
    int n = 10;
    double a = 5.;
    double b = 10.; 
    double *testm_a = new double[n-2];
    double *testm_d = new double[n-1];
    for (int i=0; i<n-2; i++) {
        testm_a[i] = a;
        testm_d[i] = b;
    }
    testm_d[n-2] = b;
    double *x = nullptr;

    JacobiRot scenario;
    scenario.initialize(testm_a, testm_d, x, n);
    SECTION( "testing right index" ) {
        int testm_k = 0;
        int testm_l = 1;
        REQUIRE(scenario.m_k == testm_k);
        REQUIRE(scenario.m_l == testm_l);

        scenario.initialize(a, b, x, n);
        REQUIRE(scenario.m_k == testm_k);
        REQUIRE(scenario.m_l == testm_l);
    }
    scenario.solve(1e-40, 10000);
    arma::vec eigval = arma::vec(n-1);
    arma::vec eigvec = arma::vec(n-1);
    SECTION( "Testing eigenvalues" ) {
        double frac;
        for (int i=0; i<n-1; i++) {
            frac = (i+1.0)*3.1415/n;
            eigval(i) = b + 2*a*std::cos(frac);
        }
        int min_idx = eigval.index_min();
        double norm = 0.0;
        for (int i=0; i<n-1; i++) {
            frac = (i+1.0)*(min_idx+1.0)*3.1415/n;
            eigvec(i) = std::sin(frac);
            norm += std::pow(eigvec(i), 2);
        }
        norm = std::sqrt(norm);
        for (int i=0; i<n-1; i++) {
            eigvec(i) /= norm;
        }
        eigval = arma::sort(eigval, "ascend");
        
        for (int i=0; i<n-1; i++){
            REQUIRE(scenario.m_lambda[i] == Approx(eigval(i)).epsilon(1E-3));
            REQUIRE(scenario.m_eigenvec[i] == Approx(eigvec(i)).epsilon(1E-2));
        }

    }
}
