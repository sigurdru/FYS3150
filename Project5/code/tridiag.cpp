#include "tridiag.hpp"

void TriDiagSolver::TriDiagSolver(double a, double b, double c, int n)
{
    m_n = n;
    m_a = a;
    m_b = b;
    m_c = c;
    m_alpha = new double[m_n-1];
    m_rho = new double[m_n-1];
}

void TriDiagSolver::Solve(double *comp, double *RHS)
{
    m_btilde = RHS;
    m_alpha[0] = m_c/m_b;
    m_rho[0] = m_btilde[0]/m_b;
    // forward substitution
    for (int i=1; i<=m_n-2; i++){
        m_rho[i] = (m_btilde[i] - m_rho[i-1]*m_a)/(m_b - m_alpha[i-1]*m_a);
        m_alpha[i] = m_c/(m_b - m_alpha[i-1]*m_a);
    }
    // backward substitution
    comp[m_n-1] = m_rho[m_n-2];
    for (int i = m_n-2; i >= 1; i--)
        comp[i] = m_rho[i-1] - m_alpha[i-1]*m_comp[i+1];
}

TriDiagSolver::~TriDiagSolver () {
    delete [] m_alpha;
    delete [] m_rho;
}
