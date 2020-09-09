#include "lineq.hpp"
#include <cmath>
#include <chrono>
#include <iostream>

void FastLineq::initialize(int n, double f(double x), double exact(double x)) {
    m_n = n;
    m_comp = new double[m_n];
    m_x = new double[m_n];
    m_exact = new double[m_n];
    d = new double[m_n];
    m_h = 1.0/(m_n - 1);
    for (int i = 0; i < m_n; i++) {
        m_x[i] = m_h * i;
        m_comp[i] = f(m_x[i]) * pow(m_h, 2);
        m_exact[i] = exact(m_x[i]);
        d[i] = i/(i+1.);
    }
}

void FastLineq::solve() {
    auto start = std::chrono::high_resolution_clock::now();
    // boundary conditions
    m_comp[0] = 0.0;
    m_comp[m_n-1] = 0.0;
    // forward substitution
    m_comp[1] /= 2.0;
    for (int i = 2; i < m_n-1; i++){
        m_comp[i] += m_comp[i-1];
        m_comp[i] *= d[i];
    }
    // backward substitution
    for (int i=m_n-2; i>0; i--) {
        m_comp[i] += d[i]*m_comp[i+1];
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Duration of solve: " << duration.count() << " microseconds" << std::endl;
}

FastLineq::~FastLineq () {
    delete [] m_x;
    delete [] m_exact;
    delete [] m_comp;
    delete [] d;
}

