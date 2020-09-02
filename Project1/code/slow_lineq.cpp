#include "lineq.hpp"
#include <cmath>
#include <chrono>
#include <iostream>

void SlowLineq::initialize(double *a, double *b, double *c, int n, double f(double x), double exact(double x)) {
    // std::cout << "start slow init" << std::endl;
    m_n = n;
    m_a = a;
    m_b = b;
    m_c = c;
    m_comp = new double[m_n];
    m_btilde = new double[m_n];
    m_alpha = new double[m_n];
    m_rho = new double[m_n];
    m_x = new double[m_n];
    m_exact = new double[m_n];
    m_h = 1.0/(m_n - 1);
    for (int i = 0; i < m_n; i++) {
        m_x[i] = m_h*i;
        m_btilde[i] = f(m_x[i])*pow(m_h, 2);
        m_exact[i] = exact(m_x[i]);
    }
    m_alpha[0] = m_c[0]/m_b[0];
    m_rho[0] = m_btilde[0]/m_b[0];
}

void SlowLineq::solve() {
    // std::cout << "start solve" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    // forward substitution
    for (int i = 1; i < m_n; i++){
        m_rho[i] = (m_btilde[i] - m_rho[i - 1] * m_a[i - 1]) / (m_b[i] - m_alpha[i - 1] * m_a[i - 1]);
        m_alpha[i] = m_c[i] / (m_b[i] - m_alpha[i - 1] * m_a[i - 1]);
    }
    // backward substitution
    m_comp[m_n - 1] = m_rho[m_n - 1];
    for (int i = m_n; i > 0; i--){
        m_comp[i - 1] = m_rho[i - 1] - m_alpha[i - 1] * m_comp[i];
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Duration of solve: " << duration.count() << " microseconds" << std::endl;
}
    
SlowLineq::~SlowLineq () {
    delete [] m_a; 
    delete [] m_b;
    delete [] m_c;
    delete [] m_x;
    delete [] m_comp;
    delete [] m_exact;
    delete [] m_alpha;
    delete [] m_rho;
    delete [] m_btilde;
}
