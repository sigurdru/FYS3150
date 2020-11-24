#include "ising.hpp"
#include <cmath>
#include <iostream>
using namespace std;

double Analytical_2D::partition_function(double T) {
    /*
    Finds the analytical partition function for a 2D lattice,
    without an external magnetic field.
    */
    double Z = 12 + 4*cosh(8/T);
    return Z;
}

void Analytical_2D::find_theoretical_values(double T) {
    /*
    Finds the following theoretical values:
    - expected energy: E_exp
    - expected absolute magnetic moment: M_exp
    - magnetic susceptibility: chi
    - specitfic heat capacity with constant volume: C_V
    */
    double Probability, E2, M2;
    int M = 16;
    double Z = partition_function(T);
    double num_spins = 4;
    int energy_list[] = {
        -8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, -8};
    int magnetic_list[] = {
        4, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, -4};
    for (int i=0; i<M; i++) {
        Probability = exp(-energy_list[i]/T);
        m_E += energy_list[i]*Probability;
        E2 += pow(energy_list[i], 2)*Probability;
        m_M += magnetic_list[i]*Probability;
        m_Mabs += abs(magnetic_list[i])*Probability;
        M2 += pow(magnetic_list[i], 2)*Probability;
    }
    E2 /= (Z * num_spins * num_spins);
    M2 /= (Z * num_spins * num_spins);
    m_E /= (Z * num_spins);
    m_M /= (Z * num_spins);
    m_Mabs /= (Z * num_spins);
    m_chi = (M2 - m_M*m_M)*num_spins/T;
    m_Cv = (E2 - m_E*m_E)*num_spins/(T*T);
    std::cout 
              << "Temperature: " << 1.0000 << std::endl
              << "expected kinetic energy: " << m_E << std::endl
              << "heat capacity: " << m_Cv << std::endl
              << "expected mag: " << m_M << std::endl
              << "Susceptibility: " << m_chi << std::endl
              << "expected abs mag: " << m_Mabs << std::endl;
}