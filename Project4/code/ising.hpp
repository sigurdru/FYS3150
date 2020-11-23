#ifndef ISING_HPP
#define ISING_HPP

class Analytical_2D {
    protected:
        double m_Z;
        double m_E_exp;
    public:
        double partition_function(double T);
};

#endif //ISING_HPP