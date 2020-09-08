#include "lineq.hpp"
#include <armadillo>

void LULineq::solve(int n, double f(double x), double exact(double x)) {
    m_n = n;
    m_h = 1.0 / (m_n - 1);
    m_x = new double[m_n];
    m_exact = new double[m_n];
    m_comp = new double[m_n];
    m_a = -1;
    m_b = 2;
    m_c = -1;
    m_A = arma::dmat(m_n-2, m_n-2);
    m_btilde = arma::dmat(m_n-2, 1);
    for (int i = 0; i<m_n; i++) {
        m_x[i] = i*m_h;
        m_exact[i] = exact(m_x[i]);
    }
    for (int i=0; i<m_n-2; i++) m_btilde(i) = pow(m_h,2)*f(m_x[i+1]);
    m_A(0,0) = m_b;
    for (int i = 1; i<m_n-2; i++) {
        m_A(i,i-1) = m_a;
        m_A(i,i) = m_b;
        m_A(i-1,i) = m_c;
    }

    arma::lu(m_L, m_U, m_A);
    arma::solve(m_X, m_L, m_btilde);
    arma::solve(m_comp_mat, m_U, m_X);

    m_comp[0] = 0.0;
    m_comp[m_n-1] = 0.0;
    for (int i = 1; i<m_n-1; i++){
        m_comp[i] = m_comp_mat(i-1);
    }
}


LULineq::~LULineq () {
    delete [] m_x;
    delete [] m_exact;
    delete [] m_comp;
}
