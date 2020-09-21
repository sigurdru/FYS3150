#include "main.hpp"
#include <armadillo>
#include <cmath>

JacobiRot::void largest();
JacobiRot::void off();

JacobiRot::void initialize (double a, double d, int N) {
    // Set matrix elements
    m_N = N;
    m_offdiag = arma::dmat(2, m_N-2);
    m_boffdiag = arma::dmat(2, m_N-2);
    m_bdiag = new double[m_N-1]
    m_diag = new double[m_N-1];
    m_k = 1;
    m_l = 0;
    m_offnorm = 2*(m_N - 2)*(std::pow(m_a,2));
    m_diag[m_N-2] = m_d;
    for (int i=0; i<m_N-2; i++){
        m_offdiag(0,i) = m_a;
        m_offdiag(1,i) = m_a;
        m_diag[i] = m_d;
    }
}


JacobiRot::void solve (double eps) {
    // Solve equations
    m_eps = eps;
    while (m_offnorm>m_eps){
        double tau = (m_diag[m_k+m_l] - m_diag[m_l+1-m_k])/(2*m_offdiag(m_k,m_l));
        double t = -tau + std::sqrt(1+std::pow(tau, 2));
        double c = 1/std::sqrt(1+std:pow(t,2));
        double s = t*c;
        for (int i=0; i<l; i++) {
            
        }
        m_bdiag[m_k+m_l] = m_diag[m_k+m_l]*std::pow(c,2) - 2*m_offdiag(m_k,m_l)*c*s + diag[m_l+1-m_k];
        m_bdiag[m_l + 1 - m_k] = m_diag[m_l + 1 - m_k] * std::pow(c, 2) + 2 * m_offdiag(m_k, m_l) * c * s + diag[m_k + m_l];
        m_boffdiag(m_k, m_l) = (m_diag[m_k+m_l] - m_diag[m_l+1-m_k])*c*s + m_offdiag(m_k,m_l)*(std::pow(c,2) - std::pow(s,2));
        largest();
        off();
    }
}

JacobiRot::void largest () {
    // Find largest element
    float val = 0;
    for (int i=0; i<m_N-2; i++){
        if (std::abs(m_offdiag(0,i)) > val){
            val = std::abs(m_offdiag(0,i));
            m_k = 0;
            m_l = i;
        } else if (std::abs(m_offdiag(1,i)) > val){
            val = std::abs(m_offdiag(1,i));
            m_k = 1;
            m_l = i;
        }
    }
}

JacobiRot::void off () {
    // Update m_off
    m_offnorm = 0.;
    for (int i=0; i<m_N-2; i++){
        m_offnorm += std::pow(m_offdiag(0,i), 2) + 
            std::pow(m_offdiag(1, i), 2);
    }
}

JacobiRot::~JacobiRot () {
    delete [] m_lambda;
}