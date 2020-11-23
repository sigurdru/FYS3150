#include "ising.hpp"
#include <cmath>
#include <iostream>
using namespace std;

double Analytical_2D::partition_function(double betha) {
    /*
    Finds the analytical partition function for a 2D lattice,
    without an external magnetic field.
    */
    double Z = 12 + 4*cosh(8*betha);
    return Z;
}

void Analytical_2D::find_theoretical_values(double betha) {
    /*
    Finds the following theoretical values:
    - expected energy: E_exp
    - expected absolute magnetic moment: M_exp
    - magnetic susceptibility: chi
    - specitfic heat capacity with constant volume: C_V
    */
    double Pi, E2_exp, M2_exp;
    int M = 16;
    double Z = partition_function(betha);
    int energy_list[] = {
        -8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, -8, -8};
    int magnetic_list[] = {
        4, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -4};
    for (int i=0; i<M; i++) {
        Pi = exp(-betha*energy_list[i]);
        m_E_exp += energy_list[i]*Pi;
        E2_exp += pow(energy_list[i], 2)*Pi;
        m_M_exp += abs(magnetic_list[i])*Pi;
        M2_exp += pow(magnetic_list[i], 2)*Pi;
    }
    E2_exp /= Z;
    M2_exp /= Z;
    m_E_exp /= Z;
    m_M_exp /= Z;
    m_chi = betha*sqrt(M2_exp - m_M_exp*m_E_exp);
    m_C_V = betha*Boltzmann_constant*sqrt(E2_exp - m_E_exp*m_E_exp);
}