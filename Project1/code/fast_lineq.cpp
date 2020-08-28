#include "lineq.hpp"
#include <cmath>
#include <chrono>
#include <iostream>

void FastLineq::initialize(int n, double f(double x), double exact(double x)) {
    // std::cout << "start init" << std::endl;
    m_n = n;
    m_a = -1;
    m_b = 2;
    m_c = -1;
    m_v = new double[m_n];
    m_btilde = new double[m_n];
    m_alpha = new double[m_n];
    m_rho = new double[m_n];
    m_x = new double[m_n];
    m_exact = new double[m_n];
    m_h = 1.0/(m_n - 1);
    for (int i = 0; i < m_n; i++){
        m_x[i] = m_h * i;
        m_btilde[i] = f(m_x[i]) * pow(m_h, 2);
        m_exact[i] = exact(m_x[i]);
    }
    m_alpha[0] = m_c / m_b;
    m_rho[0] = m_btilde[0] / m_b;
}
void FastLineq::solve() {
    // std::cout << "start solve" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    // forward substitution
    for (int i = 1; i < m_n; i++){
        m_rho[i] = (m_btilde[i] + m_rho[i - 1]) / (2 + m_alpha[i - 1]);
        m_alpha[i] = -1 / (2 + m_alpha[i - 1]);
    }
    // backward substitution
    m_v[m_n - 1] = m_rho[m_n - 1];
    for (int i = m_n; i > 0; i--) {
        m_v[i - 1] = m_rho[i - 1] - m_alpha[i - 1] * m_v[i];
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout << "Duration: " << duration.count() << std::endl;
}

FastLineq::~FastLineq () {
    // delete [] m_x;
    // delete [] m_v;
    // delete [] m_exact;
    // delete [] m_alpha;
    // delete [] m_rho;
    // delete [] m_btilde;
}

