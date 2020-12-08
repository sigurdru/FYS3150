#include "solvers.hpp"
#include <iostream>
#include <cmath>

void Solvers::WriteToFile() {
    using namespace std;
    // Open the file, which is a class variable
    if (!ResOutFile.good()){
        ResOutFile.open(ResOutFileName.c_str(), ofstream::out);
        if (!ResOutFile.good()) {
            cout << "Error opening file " << ResOutFileName << ". Aborting!" << endl;
            terminate();
        }
    }
    // Add current time
    ResOutFile << t;
    // Add the data of u
    for (int i = 0; i <= Nx; i++) 
        ResOutFile << "," << u[i];
    ResOutFile << endl;
}

void Solvers::ProduceFName(std::string fname) {
    ResOutFileName = fname;
    std::string location = "../output/";
    ResOutFileName.insert(0, location);
    ResOutFileName.append(".csv");
    std::cout << "Output file: " << ResOutFileName << std::endl;
}

void Solvers::ShouldIPrint(int i) {
    // Should you print?
    bool ShouldPrint;
    int NumberOfprints = 5;
    ShouldPrint = i%(Nt/NumberOfprints) == 0;
    if (ShouldPrint) WriteToFile();
}