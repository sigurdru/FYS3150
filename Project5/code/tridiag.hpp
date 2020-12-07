#ifndef TRIDIAG_HPP
#define TRIDIAG_HPP
#include <string>

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

class TriDiagSolver {
private:
    double m_a, m_b, m_c;
    double *m_alpha, *m_rho;

public:
    TriDiagSolver(double a, double b, double c, int n);
    void Solve(double *comp, double *RHS);
    ~TriDiagSolver();
};

#endif
