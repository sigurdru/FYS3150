#include "class_name.hpp"
#include <cmath>
#include <iostream>
#include <armadillo>

void TestCalc::initialize(double x, double y, int n){
    m_x = x; m_y = y; m_n = n;
    m_ya = new double[n];
    m_xa = new double[n];
}

void TestCalc::calculations1(){
    double product = m_x*m_y;
    std::cout << product << std::endl;
    std::cout << "done" << std::endl;
    arma::mat A = arma::mat(1,1);
    // for (int i = 0; i<2; i++){
    //     for (int j = 0; j<2; j++){
    //         A(i,j) = 1;
    //     }
    // }
    arma::mat B = A*A;
    std::cout << A << std::endl;
    for (int i = 0; i<5; i++){
        std::cout << i << std::endl;
        for (int j=0; j<i; j++){
            std::cout << i << j << std::endl;
        }
    }
}
// void TestCalc::calculations2(){
//     for (int i = 0; i < m_n; i++){
//         m_ya[i] = m_y;
//         m_xa[i] = m_x;
//         std::cout << m_ya[i] << m_xa[i] << std::endl;
//     }
// }