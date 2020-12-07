#ifndef TRIDIAG_HPP
#define TRIDIAG_HPP
#include <string>

class Common {          // needs renaming
protected:
    double m_h;         // step size in position
    int m_n;            // the number of positional grid points
    double *m_x;
    double *m_exact;
    double *m_comp;

public:
    void write_to_file(std::string fname);
};

class TriDiagSolver : public Lineq {
private:
    double m_a, m_b, m_c;
    double *m_alpha, *m_rho;

public:
    void TriDiagSolver(double a, double b, double c, int n);
    void Solve(double *comp, double *RHS);
    ~TriDiagSolver();
};

#endif
