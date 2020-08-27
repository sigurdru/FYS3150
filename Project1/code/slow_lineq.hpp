#include "lineq.hpp"
#ifndef SLOW_LINEQ_HPP
#define SLOW_LINEQ_HPP

class SlowLineq : public Lineq {
private:
    double m_h;
    double *m_a;
    double *m_b;
    double *m_c;
    double *m_alpha;
    double *m_rho;


public:
    void initialize(double *a, double *b, double *c, int n, double f(double x));
    void solve();
    ~SlowLineq();
};

#endif
