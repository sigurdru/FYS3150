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

class QM : public JacobiRot {
private:
    double *m_d;
    double *m_e;
    double m_h;
    double *m_V;

public:
    void qm_initialize(int N, double rho0, double rhoN);
    void qm_solve(double eps);
    // ~QM();
};

class UnitTests: public JacobiRot {
//Here we test eigenvalues and that we find the biggest matrix element.
private:
    double *testm_a;
    double *testm_d;
    int testm_k, testm_l; 
    // float m_tol;
public:
    void test_initialize();
    void test_largest();
    // void test_solver(float tol);
};

#endif //JACOBI_HPP
