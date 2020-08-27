#ifndef LINEQ_HPP
#define LINEQ_HPP

class SlowLineq{ 
private:
    double m_h;
    int m_n;
    double *m_a;
    double *m_b;
    double *m_c;
    double *m_alpha;
    double *m_rho;
    double *m_btilde;
    double *m_v;
    double *m_x;

public:
    void initialize(int n, double f(double x));
    void solve();
};

class FastLineq {
private:
    double m_h;
    int m_n, m_a, m_b, m_c;
    double *m_alpha, *m_rho, *m_btilde, *m_v, *m_x;

public:
    void initialize(int n, double f(double x));
    void solve();
};

#endif

// #ifndef LINEQ_HPP
// #define LINEQ_HPP
// #include <string>

// class Lineq
// {
// private:
//     int m_n;
//     double *m_v;
//     double *m_x;
//     double *m_b_tilde;

// public:
//     void write_to_file(std::string fname);
//     double exact_solution(double x);
// };

// #endif
