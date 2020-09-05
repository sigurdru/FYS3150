#ifndef LINEQ_HPP
#define LINEQ_HPP
#include <string>
// NY
#include <armadillo>
// NY

class Lineq {
protected:
    double m_h;
    int m_n;
    double *m_x;
    double *m_exact;
    double *m_comp;

public:
    void write_to_file(std::string fname);
};

class SlowLineq : public Lineq { 
private:
    double *m_a, *m_b, *m_c;
    double *m_alpha, *m_rho;
    double *m_btilde;

public:
    void initialize(double *a, double *b, double *c, int n, double f(double x), double exact(double x));
    void solve();
    ~SlowLineq();
};

class FastLineq : public Lineq {
private:
    double *d;
public:
    void initialize(int n, double f(double x), double exact(double x));
    void solve();
    ~FastLineq();
};
// NY
class LULineq : public Lineq {
private:
    int m_a, m_b, m_c;
    arma::dmat m_A;
    arma::dmat m_btilde;
    arma::dmat m_L, m_U;
    arma::dmat m_X, m_comp_mat;
public:
    void solve(int n, double f(double x), double exact(double x));
    // ~LULineq();
};
// NY

#endif
