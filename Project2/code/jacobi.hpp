#ifndef JACOBI_HPP
#define JACOBI_HPP
#include <armadillo>

class Common {
protected:
    int m_N;
    double m_offnorm;
public:

};

class JacobiRot : public Common {
private:
    double m_eps;
    arma::dmat m_offdiag;
    arma::dmat m_boffdiag;
    arma::dmat m_A;
    arma::dmat m_B;
    double *m_diag, *m_bdiag;
    int m_k, m_l;

    void common_initialize(int N);
    void largest();
    void off();
    void update();

public:
    void initialize(double a, double b, int N);
    void initialize(double *a, double *b, int N);
    void print_mat();
    void solve(double eps);
    ~JacobiRot();
};

class QM : public JacobiRot {
private:
    double *m_d;
    double *m_e;
    double m_h;
    double *m_V;

public:
    void initialize(int N, double rho0, double rhoN);
    ~QM();
};

#endif
