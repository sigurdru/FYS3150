#ifndef TRIDIAG_HPP
#define TRIDIAG_HPP
#include <string>

class TriDiagSolver {
private:
    double m_a, m_b, m_c;
    int m_n;
    double *m_alpha, *m_rho;

public:
    TriDiagSolver(double a, double b, double c, int n);
    void Solve(double *comp, double *RHS);
    ~TriDiagSolver();
};

#endif //TRIDIAG_HPP
