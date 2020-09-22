#ifndef CLASS_NAME_HPP
#define CLASS_NAME_HPP

class TestCalc {
private:
    double m_x, m_y;
    double *m_xa, *m_ya;
    int m_n;
public:
    void initialize(double x, double y, int n);
    void calculations1();
    // void calculations2();
};

#endif