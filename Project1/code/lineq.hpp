#ifndef LINEQ_HPP
#define LINEQ_HPP
#include <string>

class Lineq {
public:
    double m_h;
    int m_n;
    double *m_x;
    double *m_v;
    double *m_exact;
    double *m_alpha, *m_rho, *m_btilde;
    void write_to_file(std::string fname);
};

class SlowLineq : public Lineq { 
private:
    double *m_a;
    double *m_b;
    double *m_c;

public:
    void initialize(int n, double f(double x), double exact(double x));
    void solve();
};

class FastLineq : public Lineq {
private:
    int m_a, m_b, m_c;

public:
    void initialize(int n, double f(double x), double exact(double x));
    void solve();
};

#endif
