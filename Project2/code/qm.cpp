#include "jacobi.hpp"
#include <armadillo>
#include <cmath>

void QM::qm_initialize(int N, double rho0, double rhoN) {
    m_d = new double[N-1];
    m_e = new double[N-2];
    double m_V;
    m_h = (rhoN - rho0)/N;
    double hsq = std::pow(m_h, 2);

    for (int i = 0; i<N-2; i++){
        m_V = std::pow(rho0 + (i+1)*m_h, 2);
        m_d[i] = 2/hsq + m_V;
        m_e[i] = -1.0/hsq;
    }
    m_V = std::pow(rho0 + (N-1)*m_h, 2);
    m_d[N-2] = 2/hsq + m_V;

    JacobiRot::initialize(m_e, m_d, N);

    delete [] m_d;
    delete [] m_e;
}
