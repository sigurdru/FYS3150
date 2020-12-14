#include "solvers.hpp"
#include <iostream>
#include <cmath>

void Solvers::Initialize(Parameters params)
{
    // store parameters as instance variables
    this->Nx = params.Nx;
    this->Nt = params.Nt;
    this->dt = params.dt;
    this->L = params.L;
    this->ResOutFileName = params.ResOutFileName;

    dx = L/Nx;
    alpha = dt/dx/dx;
    u = new double[Nx + 1];
    for (int i = 0; i <= Nx; i++)
        u[i] = params.initialCondition[i];
}

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

void Solvers::ProduceFName(std::string method) {
    std::string location = "../output/";
    ResOutFileName.insert(0, location);
    ResOutFileName.append("_").append(method);
    ResOutFileName.append(".csv");
    std::cout << "Output file: " << ResOutFileName << std::endl;
}
