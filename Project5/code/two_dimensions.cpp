#include <omp.h>
#include <unistd.h>
#include <cmath>
#include "solvers.hpp"

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

TwoDimensions::TwoDimensions(
    Parameters params,
    double** InitialConditions) 
{
    Initialize(params);
    u = new double**[num_cores + 1];
    for (int i = 0; i<=num_cores; i++){
        u[i] = new double*[Nx+1];
        for (int j = 0; j<=Nx; j++){
            u[i][j] = new double[Nx+1];
        }
    }
    for (int i = 0; i<=Nx; i++){
        for (int j = 0; j<=Nx; j++){
            u[0][i][j] = InitialConditions[i][j];
        }
    }
}

void TwoDimensions::Solve_TwoDimensions(int NumberOfPrints) {
    double good_to_go[num_cores+1][2*Nx+1];
    good_to_go[0][0] = 1;
    omp_set_num_threads(num_cores);
#pragma omp parallel for schedule(static, 1)
    for (int l = 0; l < Nt; l++){
        int cc = omp_get_thread_num();  //current core
        std::cout << "core: " << cc << " does timestep: " << l << std::endl;
        for (int i = 0; i<Nx; i++){
            while (good_to_go[cc][i] != 1) usleep(5);
            for (int j = i; j>1; j--){
                u[cc+1][i][j] = u[cc][i][j] + alpha*(u[cc][i+1][j]
                        + u[cc][i-1][j] + u[cc][i][j+1]
                        + u[cc][i][j-1] - 4*u[cc][i][j]);
            }
        good_to_go[cc+1][i] = 1;
        good_to_go[cc][i+1] = 1;
        }
        good_to_go[0][Nx] = 1;
        for (int j = 1; j<Nx; j++){
            while (good_to_go[cc][Nx + j - 1] != 1) usleep(5);
            for (int i = Nx-1; i>=j; i--){
                u[cc+1][i][j] = u[cc][i][j] + alpha*(u[cc][i+1][j]
                        + u[cc][i-1][j] + u[cc][i][j+1]
                        + u[cc][i][j-1] - 4*u[cc][i][j]);  
            }
        good_to_go[cc+1][Nx + j - 1] = 1;
        good_to_go[cc][Nx + j] = 1;
        }
    if (cc == num_cores-1 ){
        for (int i = 0; i<=num_cores; i++){
            for (int j = 0; j<=2*Nx; j++){
                good_to_go[i][j] = 0;
            }
        }
        good_to_go[0][0] = 1;
    }
    }
}
// void TwoDimensions::Solve_TwoDimensions(int NumberOfPrints) {
//     double good_to_go[num_cores+1][2*Nx+1];
//     good_to_go[0][0] = 1;
//     omp_set_num_threads(num_cores);
// #pragma omp parallel for schedule(static, 1)
//     for (int l = 0; l < Nt; l++){
//         int cc = omp_get_thread_num();  //current core
//         std::cout << "core: " << cc << "does timestep: " << l << std::endl;
//         for (int i = 0; i<Nx; i++){
//             while (good_to_go[cc][i] != 1) usleep(5);
//             for (int j = i; j>1; j--){
//                 u[cc+1][i][j] = u[cc][i][j] + alpha*(u[cc][i+1][j]
//                         + u[cc][i-1][j] + u[cc][i][j+1]
//                         + u[cc][i][j-1] - 4*u[cc][i][j]);
//             }
//         good_to_go[cc+1][i] = 1;
//         good_to_go[cc][i+1] = 1;
//         }
//         good_to_go[0][Nx] = 1;
//         for (int j = 1; j<Nx; j++){
//             while (good_to_go[cc][Nx + j - 1] != 1) usleep(5);
//             for (int i = Nx-1; i>=j; i--){
//                 u[cc+1][i][j] = u[cc][i][j] + alpha*(u[cc][i+1][j]
//                         + u[cc][i-1][j] + u[cc][i][j+1]
//                         + u[cc][i][j-1] - 4*u[cc][i][j]);  
//             }
//         good_to_go[cc+1][Nx + j - 1] = 1;
//         good_to_go[cc][Nx + j] = 1;
//         }
//     if (good_to_go[num_cores-1][2*Nx-1] == 1){
//         for (int i = 0; i<=num_cores; i++){
//             for (int j = 0; j<=2*Nx; j++){
//                 good_to_go[i][j] = 0;
//             }
//         }
//     }
//     good_to_go[0][0] = 1;
//     }
// }