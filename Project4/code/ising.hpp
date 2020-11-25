#ifndef ISING_HPP
#define ISING_HPP
#include <string>
#include <fstream>      // write to file

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
        std::string ExpValsFname, LatticeFname;
        std::ofstream ExpValsOutfile, LatticeOutfile;

        inline int PeriodicBoundary(int, int);
        void WriteResultstoFile(int, double);
        void WriteLattice(int);
        void InitializeLattice(bool);

    public:
        MetropolisSampling(int, bool);
        void Solve(int, double, bool);
        ~MetropolisSampling();
};

#endif //ISING_HPP
