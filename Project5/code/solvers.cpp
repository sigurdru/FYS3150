#include "solvers.hpp"
#include <iostream>
#include <cmath>
#include <fstream>

void Solvers::WriteToFile () {
    using namespace std;
    if (!ResOutFile.good()){
        ResOutFile.open(ResOutFileName.c_str(), ofstream::out);
        if (!ResOutfile.good()) {
            cout << "Error opening file " << ResOutFileName << ". Aborting!" << endl;
            terminate();
        }
    }
    ResOutFile << t;
    for (int i = 0; i <= n; i++) ResOutFile << "," << u[i];
    ResOutFile << endl;
}
