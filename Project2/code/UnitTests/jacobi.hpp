#ifndef JACOBI_HPP
#define JACOBI_HPP
#include <armadillo>

class Common
{
protected:
    int m_N;
    double m_offnorm;

public:
};

class JacobiRot : public Common
{
protected:
    double m_eps;
    arma::dmat m_A;
    double *m_diag, *m_bdiag;

    void common_initialize(int N);
    void largest();
    void off();

public:
    int m_k, m_l;
    double *m_lambda;
    void initialize(double a, double b, int N);
    void initialize(double *a, double *b, int N);
    void print_mat();
    void solve(double eps);
    ~JacobiRot();
};

#endif //JACOBI_HPP