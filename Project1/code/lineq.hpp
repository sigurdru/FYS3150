#ifndef LINEQ_HPP
#define LINEQ_HPP
#include <string>

class Lineq {
private:
    int m_n;
    double *m_v;
    double *m_x;
    double *m_b_tilde;

public:
    void write_to_file(std::string fname);
    double exact_solution(double x);
};

#endif
