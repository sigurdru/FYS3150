#include "jacobi.hpp"
#include <armadillo>
#include <cmath>
#include <iostream>

void JacobiRot::common_initialize(int N) {
    m_N = N;
    m_offdiag = arma::dmat(2, m_N-2);
    m_boffdiag = arma::dmat(2, m_N-2);
    m_bdiag = new double[m_N-1];
    m_diag = new double[m_N-1];

    // test
    m_A = arma::dmat(m_N-1, m_N-1);
    m_B = arma::dmat(m_N-1, m_N-1);
    for (int i=0; i<m_N-1; i++) {
        for (int j=0; j<m_N-1; j++) {
            m_A(i, j) = 0.0;
            m_B(i, j) = 0.0;
        }
    }
}

void JacobiRot::initialize (double a, double d, int N) {
    std::cout << "init called" << std::endl << std::endl;
    common_initialize(N);
    m_k = 1;
    m_l = 0;
    m_k = 2;
    m_l = 1;
    m_offnorm = 2*(m_N - 2)*(std::pow(a,2));
    // m_diag[m_N-2] = d;
    // for (int i=0; i<m_N-2; i++){
        // m_offdiag(0,i) = a;
        // m_offdiag(1,i) = a;
        // m_diag[i] = d;
    // }
    m_A(m_N-2, m_N-2) = d;
    for (int i=0; i<m_N-2; i++){
        m_A(i+1, i) = a;
        m_A(i, i+1) = a;
        m_A(i, i) = d;
    }
}

void JacobiRot::initialize(double *a, double*d, int N) {
    common_initialize(N);
    m_diag[m_N-2] = d[m_N-2];
    for (int i=0; i<m_N-2; i++){
        m_offdiag(0,i) = a[i];
        m_offdiag(1,i) = a[i];
        m_diag[i] = d[i];
    }
    largest();
    off();
}


void JacobiRot::solve (double eps) {
    std::cout << "solve called" << std::endl << std::endl;
    // Solve equations
    m_eps = eps;
    double tau, t, c, s;
    int counter = 0;
    // while (m_offnorm > m_eps) {
    int k = m_k;
    int l = m_l;
    while (counter < 2) {
        // tau = (m_diag[m_k+m_l] - m_diag[m_l+1-m_k])/(2*m_offdiag(m_k,m_l));
        tau = (m_A(m_k, m_k) - m_A(m_l, m_l))/(2*m_A(m_k,m_l));
        t = -tau + std::sqrt(1+std::pow(tau, 2));
        c = 1/std::sqrt(1+std::pow(t,2));
        s = t*c;
        for (int i=0; i<m_N-1; i++) {
            m_B(i, k) = m_A(i, k)*c - m_A(i, l)*s;
            m_B(i, l) = m_A(i, l)*c - m_A(i, k)*s;
        }
        m_B(k, k) = m_A(k, k)*c*c - 2*m_A(k, l)*c*s + m_A(l, l)*s*s;
        m_B(l, l) = m_A(l, l)*c*c + 2*m_A(k, l)*c*s + m_A(k, k)*s*s;
        m_B(k, l) = (m_A(k, k) - m_A(l, l))*c*s + m_A(k, l)*(c*c - s*s);
        // m_bdiag[m_k+m_l] = m_diag[m_k+m_l]*std::pow(c,2) 
            // - 2*m_offdiag(m_k,m_l)*c*s 
            // + m_diag[m_l+1-m_k];
        // m_bdiag[m_l + 1 - m_k] = m_diag[m_l + 1 - m_k] * std::pow(c, 2) 
            // + 2 * m_offdiag(m_k, m_l) * c * s 
            // + m_diag[m_k + m_l];
        // m_boffdiag(m_k, m_l) = (m_diag[m_k+m_l] 
            // - m_diag[m_l+1-m_k])*c*s 
            // + m_offdiag(m_k,m_l)*(std::pow(c,2) 
            // - std::pow(s,2));
        
        largest();
        off();
        print_mat();
        update();
        counter += 1;
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

    for (int i=0; i<m_N-1; i++) {
        for (int j=0; j<m_N-1; j++) {
            std::cout << " " << m_B(i, j);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void JacobiRot::update () {
    for (int i=0; i<m_N-1; i++) {
        for (int j=0; j<m_N-1; j++) {
            m_A(i, j) = m_B(i, j);
        }
    }
}

void JacobiRot::largest () {
    // Find largest element
    double val = 0;
    for (int i=0; i<m_N-2; i++){
        for (int j=i+1; j<m_N-2; j++){
            if (std::abs( m_A(i,j) ) > val){
                m_k = i;
                m_l = j;
                val = std::abs( m_A(i,j) );
            }
        for (int j=0; j<i; j++){
            if (std::abs( m_A(i,j) ) > val){
                m_k = i;
                m_l = j;
                val = std::abs( m_A(i,j) );
            }
        }
        // if (std::abs(m_offdiag(0,i)) > val){
            // val = std::abs(m_offdiag(0,i));
            // m_k = 0;
            // m_l = i;
        // } else if (std::abs(m_offdiag(1,i)) > val){
            // val = std::abs(m_offdiag(1,i));
            // m_k = 1;
            // m_l = i;
        // }
        // if (std::abs(m_A(i+1, i)) > val) {
        //     val = std::abs(m_A(i+1, i));
        //     m_k = i+1;
        //     m_l = i;
        // }
        // if (std::abs(m_A(i, i+1)) > val) {
        //     val = std::abs(m_A(i, i+1));
        //     m_k = i;
        //     m_l = i+1;
        // }
    }
}

void JacobiRot::off () {
    // Update m_offnorm
    double m_offnorm = 0.;
    for (int i=0; i<m_N-2; i++){
        for (int j=i+1; j<m_N-2; j++){
            m_offnorm += std::pow(m_A(i,j),2);
        }
        for (int j=0; j<i; j++){
            m_offnorm += std::pow(m_A(i,j),2);
        }
    }

    // m_offnorm = 0.;
    // for (int i=0; i<m_N-2; i++){
    //     // m_offnorm += std::pow(m_offdiag(0,i), 2) + 
    //         // std::pow(m_offdiag(1, i), 2);
    //     m_offnorm += std::pow(m_A(i+1, i), 2)
    //         + std::pow(m_A(i, i+1), 2);
    // }
JacobiRot::~JacobiRot () {
    delete [] m_diag;
    delete [] m_bdiag;
}
