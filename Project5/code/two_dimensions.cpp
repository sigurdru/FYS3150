#include <cmath>
#include <iomanip>
#include <unistd.h>
#include <omp.h>        // parallelization
#include "solvers.hpp"

TwoDimensions::TwoDimensions(
    Parameters params,
    double* InitialConditions,
    int numCores
) {
    this->numCores = numCores;
    Initialize(params);
    u = new double[(numCores+1)*(Nx+1)*(Nx+1)];
    for (int core = 0; core <= numCores; core++) {
        for (int row = 0; row <= Nx; row++) {
            for (int col = 0; col <= Nx; col++)
                u[Index2D(core, (Nx+1)*(Nx+1), Index2D(row, Nx+1, col))] = 0.0;
        }
    }
    for (int row = 0; row <= Nx; row++) {
        for (int col = 0; col <= Nx; col++)
            u[Index2D(0, (Nx+1)*(Nx+1), Index2D(row, Nx+1, col))]
                = InitialConditions[Index2D(row, Nx+1, col)];
    }
    completed = new bool[numCores*(2*Nx-2)];
    for (int i = 0; i <= numCores-1; i++) {
        for (int j = 0; j <= 2*Nx-4; j++)
            completed[Index2D(i, 2*Nx-2, j)] = false;
        completed[Index2D(i, 2*Nx-2, 2*Nx-3)] = true;
    }
}

void TwoDimensions::WriteToFile() {
    using namespace std;
    // Open the file, which is a class variable
    if (!ResOutFile.good()){
        ResOutFile.open(ResOutFileName.c_str(), ofstream::out);
        if (!ResOutFile.good()) {
            cout << "Error opening file "
                << ResOutFileName << ". Aborting!" << endl;
            terminate();
        }
    }
    // Add current time
    ResOutFile << t;
    // Add the data of u
    for (int i = 0; i <= Nx; i++) {
        for (int j = 0; j <= Nx; j++) {
            ResOutFile << "," << u[Index2D(0, (Nx+1)*(Nx+1), Index2D(i, Nx+1, j))];
        }
    }
    ResOutFile << endl;
}

void TwoDimensions::Solve(int NumberOfprints)
{
    WriteToFile();
    WriteToFile();
    omp_set_num_threads(numCores); // set number of threads in parallel
    for (int timestep = numCores; timestep <= Nt; timestep += numCores) {
        t = timestep*dt;
        #pragma omp parallel for shared(u, completed)
        for (int core = 1; core <= numCores; core++) {
            int edge;
            for (int diag = 2; diag <= 2*Nx-2; diag++) {
                if (core > 1) {
                    while (!completed[Index2D(core-2, 2*Nx-2, diag-1)]) {
                        usleep(1);
                    }
                }
                edge = std::min(diag-1, Nx-1);
                for (int i = edge; i >= diag-edge; i--) {
                    int j = diag - i;
                    u[Index2D(core, (Nx+1)*(Nx+1), Index2D(i, Nx+1, j))]
                        = u[Index2D(core-1, (Nx+1)*(Nx+1), Index2D(i, Nx+1, j))]
                            + alpha*(
                                u[Index2D(core-1, (Nx+1)*(Nx+1), Index2D(i+1, Nx+1, j))]
                                + u[Index2D(core-1, (Nx+1)*(Nx+1), Index2D(i-1, Nx+1, j))]
                                + u[Index2D(core-1, (Nx+1)*(Nx+1), Index2D(i, Nx+1, j+1))]
                                + u[Index2D(core-1, (Nx+1)*(Nx+1), Index2D(i, Nx+1, j-1))]
                                - 4*u[Index2D(core-1, (Nx+1)*(Nx+1), Index2D(i, Nx+1, j))]);
                }
                completed[Index2D(core-1, 2*Nx-2, diag-2)] = true;
            }
        }
        ResetMatrices();
        if ((NumberOfprints > 0) && (timestep/numCores%(Nt/numCores/NumberOfprints) == 0))
            WriteToFile();
    }
    WriteToFile();
}
void TwoDimensions::ResetMatrices()
{
    for (int i = 0; i <= numCores-1; i++) {
        for (int j = 0; j <= 2*Nx-4; j++)
            completed[Index2D(i, 2*Nx-2, j)] = false;
    }
    for (int row = 0; row <= Nx; row++) {
        for (int col = 0; col <= Nx; col++)
            u[Index2D(0, (Nx+1)*(Nx+1), Index2D(row, Nx+1, col))]
                = u[Index2D(numCores, (Nx+1)*(Nx+1), Index2D(row, Nx+1, col))];
    }
    for (int core = 1; core <= numCores; core++){
        for (int row = 0; row <= Nx; row++) {
            for (int col = 0; col<=Nx; col++)
                u[Index2D(core, (Nx+1)*(Nx+1), Index2D(row, Nx+1, col))] = 0.0;
        }
    }
}

void TwoDimensions::WriteMatrix()
{
    std::cout << "u:" << std::endl;
    for (int core = 0; core <= numCores; core++) {
        for (int i = 0; i <= Nx; i++) {
            for (int j = 0; j <= Nx; j++)
                std::cout << std::setw(10) << std::setprecision(3)
                    << u[Index2D(core, (Nx+1)*(Nx+1), Index2D(i, Nx+1, j))];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void TwoDimensions::WriteCompleted()
{
    std::cout << "completed:" << std::endl;
    for (int core = 0; core <= numCores-1; core++) {
        for (int diag = 0; diag <= 2*Nx-3; diag++)
                std::cout << completed[Index2D(core, numCores, diag)] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

TwoDimensions::~TwoDimensions()
{
    delete[] u;
    delete[] completed;
}
