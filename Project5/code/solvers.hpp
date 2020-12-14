#ifndef SOLVERS_HPP
#define SOLVERS_HPP
#include <fstream>
#include <iostream>

struct Solvers {
    // Here we define common stuff
    int Nx, Nt;
    double dt, t, dx, L, alpha;
    double *u, *b;
    std::string ResOutFileName;
    std::ofstream ResOutFile;
    void WriteToFile();
    void ProduceFName(std::string fname);
    void ShouldIPrint(int i);
};

class ForwardEuler : public Solvers{
public:
    ForwardEuler(
        int num_int_points,
        int num_time_points,
        float dtimestep,
        double *InitialCondition,
        std::string ResOutFileName
    );
    void Solve_ForwardEuler(
        double BoundaryLeft(double),
        double BoundaryRight(double)
    );
    ~ForwardEuler();
};

class BackwardEuler : public Solvers {
public:
    BackwardEuler(
        int num_int_points,
        int num_time_points,
        float dtimestep,
        double *InitialCondition,
        std::string ResOutFileName
    );
    void Solve_BackwardEuler(
        double BoundaryLeft(double),
        double BoundaryRight(double)
    );
    ~BackwardEuler();
};

class CrankNicolson : public Solvers {
public:
    CrankNicolson(
        int num_int_points,
        int num_time_points,
        float dtimestep,
        double* InitialCondition,
        std::string ResOutFileName
    );
    void Solve_CrankNicolson(
        double BoundaryLeft(double),
        double BoundaryRight(double)
    );
    ~CrankNicolson();
};

class TwoDimensions : public Solvers {
public:
    double **u;
    double **u2;
    void WriteToFile();
    TwoDimensions(
        int num_int_points,
        int num_time_points,
        double dtimestep,
        double** InitialConditions,
        std::string ResOutFileName
    );
    void WriteToFile();
    void ShouldIPrint(int i);
    void Solve_TwoDimensions();
};

#endif //SOLVERS_HPP

