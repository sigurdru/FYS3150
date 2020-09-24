#include "jacobi.hpp"
#include <armadillo>
#include <cmath>

void QM::qm_initialize(int N, double rho0, double rhoN) {
    m_N = N;
    m_d = new double[m_N-2];
    m_e = new double[m_N-3];
    m_V = new double[m_N-2];
    m_h = (rhoN - rho0)/m_N;
    double hsq = std::pow(m_h, 2);


    for (int i = 0; i<m_N-3; i++){
        m_V[i] = std::pow(rho0 + (i+1)*m_h, 2);
        m_d[i] = 2/hsq + m_V[i];
        m_e[i] = -1hsq;
    }
    m_V[m_N-3] = std::pow(rho0 + (m_N-2)*m_h, 2);
    m_d[m_N-3] = 2/hsq + m_V[m_M-3];
}

void QM::qm_solve(double eps){
    JacobiRot::initialize(m_e, m_d, m_N);
    JacobiRot::solve(eps);
}

// ~QM::QM(){
//     delete [] m_d;
//     delete [] m_e;
//     delete [] m_V;
// }