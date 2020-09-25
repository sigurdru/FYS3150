#ifndef JACOBI_HPP
#define JACOBI_HPP
#include <armadillo>

class Common{
protected:
    int m_N;
    double m_offnorm;

public:
};

class JacobiRot : public Common{
protected:
    double m_eps;
    double *m_diag, *m_bdiag;

    void common_initialize(int N);
    void largest();
    void off();

public:
    int m_k, m_l;
    arma::dmat m_A;
    arma::vec m_lambda;
    void initialize(double a, double b, int N);
    void initialize(double *a, double *b, int N);
    void solve(double eps);
    ~JacobiRot();
};

class QM : public JacobiRot {
private:
    double *m_d;
    double *m_e;
    double *m_V;
    double m_h;

public:
    void qm_initialize(int N, double rho0, double rhoN);
    void qm_solve(double eps);
    ~QM();
};

#endif //JACOBI_HPP
