#include "jacobi.hpp"
#include <armadillo>
#include <cmath>
#include <iostream>

void JacobiRot::common_initialize(double *rho, int N) {
    m_N = N;
    m_A = arma::dmat(m_N-1, m_N-1).fill(0.);
    m_R = arma::dmat(m_N-1, m_N-1).fill(0.);
    for (int i=0; i<N-1; i++) m_R(i, i) = 1.0;
    m_rho = rho;
}

void JacobiRot::initialize (double a, double d, double *rho, int N) {
    common_initialize(rho, N);
    m_a = a; m_d = d;
    m_k = 0;
    m_l = 1;
    m_largest_val = std::abs(a);
    m_A(m_N-2, m_N-2) = d;
    for (int i=0; i<m_N-2; i++){
        m_A(i+1, i) = a;
        m_A(i, i+1) = a;
        m_A(i, i) = d;
    }
}

void JacobiRot::initialize(double *a, double*d, double *rho, int N) {
    common_initialize(rho, N);
    m_A(m_N-2, m_N-2) = d[m_N-2];
    for (int i=0; i<m_N-2; i++){
        m_A(i+1, i) = a[i];
        m_A(i, i+1) = a[i];
        m_A(i, i) = d[i];
    }
    largest();
}


void JacobiRot::solve (double eps, int max_iter) {
    // Solve equations
    auto start = std::chrono::high_resolution_clock::now();
    double tau, t, c, s;
    double Aik, Ail, Akk, All, Akl, R_ik, R_il;
    int k;
    int l;
    int iterations = 0;
    while (m_largest_val > eps && iterations <= max_iter) {
        k = m_k; l = m_l;
        tau = (m_A(l, l) - m_A(k, k))/(2*m_A(k, l));
        if (tau >= 0)
            t = 1.0 / (tau + std::sqrt(1.0 + tau * tau));
        else
            t = 1.0 / (tau - std::sqrt(1.0 + tau * tau));

        c = 1.0/std::sqrt(1 + t*t);
        s = t*c;
        Akk = m_A(k, k);
        All = m_A(l, l);
        Akl = m_A(k, l);
        for (int i=0; i<m_N-1; i++) {
            if ((i!=k) && (i!=l) ) {
                Aik = m_A(i, k);
                Ail = m_A(i, l);
                m_A(i, k) = Aik*c - Ail*s;
                m_A(k, i) = m_A(i, k);
                m_A(i, l) = Ail*c + Aik*s;
                m_A(l, i) = m_A(i, l);
            }
            R_ik = m_R(i,k);
            R_il = m_R(i,l);
            m_R(i,k) = c*R_ik - s*R_il;
            m_R(i,l) = c*R_il + s*R_ik;
        }
        m_A(k, k) = Akk*c*c - 2.0*Akl*c*s + All*s*s;
        m_A(l, l) = All*c*c + 2.0*Akl*c*s + Akk*s*s;
        m_A(k, l) = 0.;     // manually set to 0
        m_A(l, k) = 0.;     // manually set to 0

        largest();
        iterations++;
    }
    m_lambda = arma::diagvec(m_A);
    m_eigenvec = new double[m_N - 1];
    int min_idx = m_lambda.index_min();
    for (int i=0; i<m_N-1; i++) m_eigenvec[i] = m_R(i, min_idx);
    m_lambda = arma::sort(m_lambda, "ascend");

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "    Duration of solve: " << duration.count() 
        << " milliseconds" << std::endl;
    std::cout << "    Iterations: " << iterations << std::endl;
}

void JacobiRot::largest () {
    // Find largest element
    m_largest_val = 0;
    for (int i=0; i<m_N-1; i++){
        for (int j=i+1; j<m_N-1; j++){
            if (std::abs( m_A(i,j) ) > m_largest_val){
                m_k = i;
                m_l = j;
                m_largest_val = std::abs( m_A(i,j) );
            }
        }
    }
}

void JacobiRot::write_to_file (std::string fname, 
        double analytic_eigvals(double a, double d, int j, int N), 
        double analytic_eigvec(int j, int N)) {
    double *ana_eigvec = new double[m_N-1];
    arma::dvec ana_eigvals = arma::vec(m_N-1);
    for (int i=0; i<m_N-1; i++) {
        ana_eigvals(i) = analytic_eigvals(m_a, m_d, i+1, m_N);
    }
    int min_idx = ana_eigvals.index_min();
    ana_eigvals = arma::sort(ana_eigvals, "ascend");
    double norm = 0.0;
    for (int i=0; i<m_N-1; i++) {
        ana_eigvec[i] = analytic_eigvec((i+1)*(min_idx+1), m_N);
        norm += std::pow(ana_eigvec[i], 2);
    }
    norm = std::sqrt(norm);
    for (int i=0; i<m_N-1; i++) {
        ana_eigvec[i] /= norm;
    }
    std::ofstream myfile;
    myfile.open (fname);
    myfile << "rho,eigenvals,analytic_eigenvals,eigenvec,analytic_eigenvec" 
        << std::endl;
    for (int i=0; i<m_N-1; i++) {
        myfile << m_rho[i] << ","
               << m_lambda(i) << ","
               << ana_eigvals(i) << ","
               << m_eigenvec[i] << ","
               << ana_eigvec[i] << std::endl;
    }
    myfile.close();
    delete [] ana_eigvec;
}

void JacobiRot::write_to_file (std::string fname, 
        double analytic_eigvals(int j)) {
    arma::dvec ana_eigvals = arma::vec(m_N-1);
    for (int i=0; i<m_N-1; i++) {
        ana_eigvals(i) = analytic_eigvals(i+1);
    }
    ana_eigvals = arma::sort(ana_eigvals, "ascend");
    std::ofstream myfile;
    myfile.open (fname);
    myfile << "rho,eigenvals,analytic_eigenvals,eigenvec" << std::endl;
    for (int i=0; i<m_N-1; i++) {
        myfile << m_rho[i] << ","
               << m_lambda(i) << ","
               << ana_eigvals(i) << ","
               << m_eigenvec[i] << std::endl;
    }
    myfile.close();
}

void JacobiRot::write_to_file (std::string fname) {
    std::ofstream myfile;
    myfile.open (fname);
    myfile << "rho,eigenvals,eigenvec" << std::endl;
    for (int i=0; i<m_N-1; i++) {
        myfile << m_rho[i] << ","
               << m_lambda(i) << ","
               << m_eigenvec[i] << std::endl;
    }
    myfile.close();
}

JacobiRot::~JacobiRot () {
    delete [] m_rho;
    delete [] m_eigenvec;
}
