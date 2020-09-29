#ifndef JACOBI_HPP
#define JACOBI_HPP
#include <armadillo>

class JacobiRot {
protected:
    int m_N;
    double m_a, m_d, m_largest_val;
    double *m_rho;
    arma::dmat m_A, m_R;

    void common_initialize(double *rho, int N);
    void largest();

public:
    int m_k, m_l;
    double *m_eigenvec;
    arma::vec m_lambda;

    void initialize(double a, double d, double *rho, int N);
    void initialize(double *a, double *d, double *rho, int N);
    void solve(double eps, int max_iter);
    void write_to_file(std::string fname,
        double analytic_eigvals(double a, double d, int j, int N), 
        double analytic_eigvec(int j, int N));
    void write_to_file(std::string fname,
        double analytic_eigvals(int j));
    void write_to_file(std::string fname);
    ~JacobiRot();
};

class QM : public JacobiRot {
private:
    double *m_d;
    double *m_e;
    double *m_V;
    double m_h;

public:
    void initialize(int N, double rho0, double rhoN, 
        double potential(double rho, double omega_r), double omega_r);
};

#endif //JACOBI_HPP
