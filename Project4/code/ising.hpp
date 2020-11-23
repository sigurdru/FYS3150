#ifndef ISING_HPP
#define ISING_HPP

class Analytical_2D {
    protected:
        double Boltzmann_constant = 1.38064852e-23;
        double m_E_exp;
        double m_M_exp;
        double m_chi;
        double m_C_V;
        double partition_function(double betha);
    public:
        void find_theoretical_values(double betha);
};

#endif //ISING_HPP