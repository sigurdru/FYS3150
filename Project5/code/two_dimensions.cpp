#include "solvers.hpp"
#include <cmath>

TwoDimensions::TwoDimensions(
    Parameters params,
    double** InitialConditions
) {
    Initialize(params);
    u = new double*[Nx+1];
    b = new double*[Nx+1];
    for (int i = 0; i<=Nx; i++){
        u[i] = new double[Nx+1];
        b[i] = new double[Nx+1];
    }
    for (int i = 0; i<=Nx; i++){
        for (int j = 0; j<=Nx; j++){
            u[i][j] = InitialConditions[i][j];
        }
    }
}

void TwoDimensions::ShouldIPrint(int i, int NumberOfPrints) {
    // Should you print?
    bool ShouldPrint;
    ShouldPrint = i%(Nt/NumberOfPrints) == 0;
    if (ShouldPrint) WriteToFile();
}

void TwoDimensions::WriteToFile() {
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
    for (int i = 0; i <= Nx; i++) {
        for (int j = 0; j <= Nx; j++) {
            ResOutFile << "," << u[i];
        }
    }
    ResOutFile << endl;
}

void TwoDimensions::Solve_TwoDimensions(int NumberOfPrints) {
    WriteToFile();
    for (int l = 0; l < Nt; l++){
        ShouldIPrint(l, NumberOfPrints);
        for (int i = 0; i <= Nx; i++){
            for (int j = 0; j <= Nx; j++){
                b[i][j] = u[i][j];
            }
        }
        for (int i = 0; i <= Nx; i++){
            for (int j = 0; j <= Nx; j++){
                u[i][j] = b[i][j] + alpha*(b[i+1][j]
                        + b[i-1][j] + b[i][j+1]
                        + b[i][j-1] - 4*b[i][j]);
            }
        }
    }
    WriteToFile();
}

