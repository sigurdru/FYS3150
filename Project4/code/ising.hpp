#ifndef ISING_HPP
#define ISING_HPP
#include <string>

class Analytical_2D {
    protected:
        double Boltzmann_constant = 1.38064852e-23;
        double m_E;
        double m_M;
        double m_Mabs;
        double m_chi;
        double m_Cv;
        double partition_function(double betha);
    public:
        void find_theoretical_values(double betha);
};

class MetropolisSampling {
    private:
        int **SpinMatrix;
        double *EnergyDifference;
        double *ExpectationValues;
        int NumSpins;
        double Energy, MagneticMoment;

        inline int PeriodicBoundary(int, int);
        void WriteResultstoFile(int, double, std::string);

    public:
        MetropolisSampling(int);
        void InitializeLattice(bool);
        void Solve(int, double, std::string);
        ~MetropolisSampling();
};

#endif //ISING_HPP
