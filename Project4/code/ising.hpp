#ifndef ISING_HPP
#define ISING_HPP
#include <string>
#include <fstream>      // write to file

class MetropolisSampling {
    private:
        int **SpinMatrix;
        double *EnergyDifference;
        double *ExpectationValues;
        int NumSpins, NumberOfFlips;
        double Energy, MagneticMoment;
        std::string ExpValsFname, LatticeFname;
        std::ofstream ExpValsOutfile, LatticeOutfile;

        inline int PeriodicBoundary(int, int);
        void WriteResultstoFile(int, double);
        void WriteLattice(int);
        void InitializeLattice(bool);

    public:
        MetropolisSampling(int, bool, std::string);
        void Solve(int, double, bool);
        ~MetropolisSampling();
};

#endif //ISING_HPP
