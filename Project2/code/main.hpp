#ifndef MAIN_HPP
#define MAIL_HPP
#include <armadillo>

class Common{
protected:
    int m_N;
    double m_offnorm;
public:

};

class JacobiRot : public Common{
private:
    arma::dmat m_offdiag;
    arma::dmat m_boffdiag;
    double *m_diag;
    double *m_bdiag;
    int m_kdiag;
    int m_ldiag;


public:
    void initialize(double a, double b, double c, int N);
    void solve();
    ~JacobiRot();
};

#endif