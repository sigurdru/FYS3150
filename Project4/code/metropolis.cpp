#include <cmath>        // exp, fabs
#include <random>       // random number generator
#include <iostream>     // input and output
#include <string>
#include <iomanip>      // setw, setprecision
#include "ising.hpp"

inline int MetropolisSampling::PeriodicBoundary(int index, int add) {
    return (index+NumSpins+add) % (NumSpins);
}


MetropolisSampling::MetropolisSampling(int NSpins, bool random_init)
{
    SpinMatrix = new int*[NSpins];
    for (int i=0; i<NSpins; i++) {
        SpinMatrix[i] = new int[NSpins];
    }
    ExpectationValues = new double[5];
    EnergyDifference = new double[17];
    NumSpins = NSpins;      // store number of spins in a class variable
    InitializeLattice();
    std::string NSpins_str = std::to_string(NSpins);
    std::string config;
    if (random_init) config = "random";
    else config = "up";
    std::string fname = "../output/";
    fname = fname.append(NSpins_str).append("_")
        .append(config).append("_");
    LatticeFname = fname.append("Lattice.csv");
    ExpValsFname = fname.append("ExpVals.csv");
}


// initialize energy, spin matrix and magnetization
void MetropolisSampling::InitializeLattice()
{
    Energy = 0.;
    MagneticMoment = 0.;
    // reset expectation values and energy differences
    for (int i=0; i<5; i++) ExpectationValues[i] = 0.0;
    for (int de=-8; de<=8; de++) EnergyDifference[de+8] = 0;
    // setup spin matrix using cold start, all spins pointing up
    for (int x=0; x < NumSpins; x++) {
        for (int y=0; y < NumSpins; y++){
            SpinMatrix[x][y] = 1; // spin orientation for the ground state
            MagneticMoment += 1;
            Energy -= 4;
        }
    }
}

// The Monte Carlo part with the Metropolis algo with sweeps over the lattice
void MetropolisSampling::Solve(
        int MonteCarloCycles, double Temperature,
        bool PrintLattice){
    // initialize the seed and call the Mersienne algo
    std::random_device rd;
    std::mt19937_64 gen(rd());
    // set up the uniform distribution for x \in [[0, 1]
    std::uniform_real_distribution<double> RandomNumberGenerator(0.0, 1.0);
    // setup array for possible energy changes
    for (int de=-8; de<=8; de+=4) EnergyDifference[de+8] = exp(-de/Temperature);
    // start Monte Carlo experiments
    int AllSpins = NumSpins*NumSpins;
    int ix, iy, deltaE;
    for (int cycles = 1; cycles <= MonteCarloCycles; cycles++){
        // the sweep over the lattice, looping over all spin sites
        for (int Spins=0; Spins<AllSpins; Spins++) {
            ix = (int) (RandomNumberGenerator(gen)*NumSpins);
            iy = (int) (RandomNumberGenerator(gen)*NumSpins);
            deltaE =  2*SpinMatrix[ix][iy]*(
                SpinMatrix[ix][PeriodicBoundary(iy, -1)]
                + SpinMatrix[PeriodicBoundary(ix, -1)][iy]
                + SpinMatrix[ix][PeriodicBoundary(iy, 1)]
                + SpinMatrix[PeriodicBoundary(ix, 1)][iy]
            );
            if ( RandomNumberGenerator(gen) <= EnergyDifference[deltaE+8] ){
                // flip one spin and accept new spin config
                SpinMatrix[ix][iy] *= -1;
                MagneticMoment += (double) 2.0*SpinMatrix[ix][iy];
                Energy += (double) deltaE;
            }
        }
        // update expectation values for local node after a sweep through the lattice
        // std::cout << Energy << std::endl;
        ExpectationValues[0] += Energy;
        ExpectationValues[1] += Energy*Energy;
        ExpectationValues[2] += MagneticMoment;
        ExpectationValues[3] += MagneticMoment*MagneticMoment;
        ExpectationValues[4] += fabs(MagneticMoment);
        if (PrintLattice & (cycles % (MonteCarloCycles/100) == 1)) WriteLattice();
    }
    WriteResultstoFile(MonteCarloCycles, Temperature);
}


void MetropolisSampling::WriteResultstoFile(
        int MonteCarloCycles,
        double temperature)
{
    using namespace std;
    if (!ExpValsOutfile.good()){
        ExpValsOutfile.open(ExpValsFname.c_str(), ofstream::out);
        if (!ExpValsOutfile.good()) {
            cout << "Error opening file " << ExpValsFname << ". Aborting!" << endl;
            terminate();
        }
        ExpValsOutfile
            << "Temperature,"
            << "Energy,"
            << "HeatCapacity,"
            << "Magnetization,"
            << "MagneticSusceptibility,"
            << "Magnetization_Abs" << endl;
    }

    // normalization constant, divide by number of cycles
    double norm = 1.0/MonteCarloCycles;
    double E = ExpectationValues[0]*norm;
    double E2 = ExpectationValues[1]*norm;
    double M = ExpectationValues[2]*norm;
    double M2 = ExpectationValues[3]*norm;
    double Mabs = ExpectationValues[4]*norm;
    // all expectation values are per spin, divide by 1/NSpins/NSpins
    double AllSpins = 1.0/((double) NumSpins*NumSpins);
    double HeatCapacity = (E2 - E*E)*AllSpins/temperature/temperature;
    double MagneticSusceptibility = (M2 - M*M)*AllSpins/temperature;
    ExpValsOutfile << setiosflags(ios::showpoint | ios::uppercase);
    ExpValsOutfile << setw(15) << setprecision(8) << temperature;
    ExpValsOutfile << setw(15) << setprecision(8) << E*AllSpins;
    ExpValsOutfile << setw(15) << setprecision(8) << HeatCapacity;
    ExpValsOutfile << setw(15) << setprecision(8) << M*AllSpins;
    ExpValsOutfile << setw(15) << setprecision(8) << MagneticSusceptibility;
    ExpValsOutfile << setw(15) << setprecision(8) << Mabs*AllSpins << endl;
}

MetropolisSampling::~MetropolisSampling()
{
    // deallocate memory
    for (int i=0; i<NumSpins; i++) delete[] SpinMatrix[i];
    delete[] SpinMatrix;
    // close output files
    ExpValsOutfile.close();
    LatticeOutfile.close();
}

void MetropolisSampling::WriteLattice()
{
    using namespace std;
    if (!LatticeOutfile.good()){
        LatticeOutfile.open(LatticeFname.c_str(), ofstream::out);
        if (!LatticeOutfile.good()) {
            cout << "Error opening file " << LatticeFname << ". Aborting!" << endl;
            terminate();
        }
    }

    for (int i=0; i<NumSpins; i++) {
        for (int j=0; j<NumSpins; j++) {
            LatticeOutfile << SpinMatrix[i][j] << ",";
        }
    }
    LatticeOutfile << "\n";
}
