#ifndef ISING_HPP
#define ISING_HPP
#include <string>
#include <fstream>      // write to file

class MetropolisSampling {
    private:
        int **SpinMatrix;
        double *EnergyDifference;
        double m_E2, m_M2;
        double Energy, MagneticMoment;
        int NumSpins, NumberOfFlips;
        std::string ExpValsFname, LatticeFname;
        std::ofstream ExpValsOutfile, LatticeOutfile;

        inline int PeriodicBoundary(int, int);
        void WriteResultstoFile(int, double);
        void WriteLattice(int);
        void InitializeLattice(bool);

    public:
        double m_E, m_Mabs, m_HeatCapacity, m_MagneticSusceptibility;
        double *ExpectationValues;
        MetropolisSampling(int, bool, std::string);
        void Solve(int, double, bool);
        void NormAndCalcExp(int, double);
        ~MetropolisSampling();
};

#endif //ISING_HPP
