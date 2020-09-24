#include "jacobi.hpp"
#include <armadillo>
#include <cmath>
#include <iostream>

void JacobiRot::common_initialize(int N) {
    m_N = N;
    m_A = arma::dmat(m_N-1, m_N-1);
    for (int i=0; i<m_N-1; i++) {
        for (int j=0; j<m_N-1; j++) {
            m_A(i, j) = 0.0;
        }
    }
}

void JacobiRot::initialize (double a, double d, int N) {
    common_initialize(N);
    m_k = 2;
    m_l = 1;
    m_offnorm = 2*(m_N - 2)*(std::pow(a,2));
    m_A(m_N-2, m_N-2) = d;
    for (int i=0; i<m_N-2; i++){
        m_A(i+1, i) = a;
        m_A(i, i+1) = a;
        m_A(i, i) = d;
    }
}

void JacobiRot::initialize(double *a, double*d, int N) {
    common_initialize(N);
    m_A(m_N-2, m_N-2) = d[m_N-2];
    for (int i=0; i<m_N-2; i++){
        m_A(i+1, i) = a[i];
        m_A(i, i+1) = a[i];
        m_A(i, i) = d[i];
    }
    largest();
    off();
}


void JacobiRot::solve (double eps) {
    // Solve equations
    m_eps = eps;
    double tau, t, c, s;
    double Aik, Ail, Akk, All, Akl;
    m_lambda = new double[m_N-1];
    while (m_offnorm > eps) {
        tau = (m_A(m_l, m_l) - m_A(m_k, m_k))/(2*m_A(m_k,m_l));
        if (tau > 0)
            t = 1 / (tau + std::sqrt(1 + tau * tau));
        else
            t = -1 / (-tau + std::sqrt(1 + tau * tau));

        c = 1/std::sqrt(1+t*t);
        s = t*c;
        Akk = m_A(m_k, m_k);
        Akl = m_A(m_k, m_l);
        All = m_A(m_l, m_l);
        for (int i=0; i<m_N-1; i++) {
            if ((i!=m_k) && (i!=m_l) ) {
            Aik = m_A(i,m_k);
            Ail = m_A(i,m_l);
            m_A(i, m_k) = Aik*c - Ail*s;
            m_A(m_k, i) = m_A(i, m_k);
            m_A(i, m_l) = Ail*c - Aik*s;
            m_A(m_l, i) = m_A(i, m_l);
            }
        }
        m_A(m_k, m_k) = Akk*c*c - 2*Akl*c*s + All*s*s;
        m_A(m_l, m_l) = All*c*c + 2*Akl*c*s + Akk*s*s;
        m_A(m_k, m_l) = 0.;
        m_A(m_l, m_k) = 0.;
        largest();
        off();
    }
    for (int i=0; i<m_N-1; i++){
        m_lambda[i] = m_A(i,i);
    }
}

void JacobiRot::print_mat () {
    for (int i=0; i<m_N-1; i++) {
        for (int j=0; j<m_N-1; j++) {
            std::cout << " " << m_A(i, j);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void JacobiRot::largest () {
    // Find largest element
    double val = 0;
    for (int i=0; i<m_N-1; i++){
        for (int j=i+1; j<m_N-1; j++){
            if (std::abs( m_A(i,j) ) > val){
                m_k = i;
                m_l = j;
                val = std::abs( m_A(i,j) );
            }
        }
        for (int j=0; j<i; j++){
            if (std::abs( m_A(i,j) ) > val){
                m_k = i;
                m_l = j;
                val = std::abs( m_A(i,j) );
            }
        }
    }
}

void JacobiRot::off () {
    // Update m_offnorm
    m_offnorm = 0.;
    for (int i=0; i<m_N-1; i++){
        for (int j=i+1; j<m_N-1; j++){
            m_offnorm += std::pow(m_A(i,j),2);
        }
        for (int j=0; j<i; j++){
            m_offnorm += std::pow(m_A(i,j),2);
        }
    }
}
JacobiRot::~JacobiRot () {
    delete [] m_diag;
    delete [] m_bdiag;
    delete [] m_lambda;
}
