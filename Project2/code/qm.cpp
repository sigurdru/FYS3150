#include "jacobi.hpp"
#include <armadillo>
#include <cmath>

void QM::initialize(int N, double rho0, double rhoN, 
        double potential(double rho, double omega_r), double omega_r) {
    double *d = new double[N-1];
    double *e = new double[N-2];
    double *rho = new double[N-1];
    double V;
    m_h = (rhoN - rho0)/N;
    double hsq = std::pow(m_h, 2);

    rho[0] = rho0 + m_h;
    for (int i = 0; i<N-2; i++){
        rho[i+1] = rho[i] + m_h;
        V = potential(rho[i], omega_r);
        d[i] = 2/hsq + V;
        e[i] = -1.0/hsq;
    }
    V = potential(rho[N-2], omega_r);
    d[N-2] = 2/hsq + V;

    JacobiRot::initialize(e, d, rho, N);
    delete [] d;
    delete [] e;
}
