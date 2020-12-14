#ifndef SOLVERS_HPP
#define SOLVERS_HPP
#include <fstream>
#include <iostream>

struct Parameters {
    int Nx, Nt;
    double dt, L;
    double *initialCondition;
    std::string ResOutFileName;
};

class Solvers {
protected:
    // Here we define common stuff
    int Nx, Nt;
    double dt, t, dx, L, alpha;
    double *b;
    std::string ResOutFileName;
    std::ofstream ResOutFile;

    void Initialize(Parameters);
    void ProduceFName();
    void ShouldIPrint(int i, int);
    void WriteToFile();

public:
    double *u;
};

class ForwardEuler : public Solvers{
public:
    ForwardEuler(Parameters);
    void Solve_ForwardEuler(
        double BoundaryLeft(double),
        double BoundaryRight(double),
        int NumberOfprints
    );
    ~ForwardEuler();
};

class BackwardEuler : public Solvers {
public:
    BackwardEuler(Parameters);
    void Solve_BackwardEuler(
        double BoundaryLeft(double),
        double BoundaryRight(double),
        int NumberOfPrints
    );
    ~BackwardEuler();
};

class CrankNicolson : public Solvers {
public:
    CrankNicolson(Parameters);
    void Solve_CrankNicolson(
        double BoundaryLeft(double),
        double BoundaryRight(double),
        int NumberOfprints
    );
    ~CrankNicolson();
};

class TwoDimensions : public Solvers {
public:
    double **u;
    double **u2;
    void ShouldIPrint(int i, int);
    void WriteToFile();
    TwoDimensions(
        int num_int_points,
        int num_time_points,
        double dtimestep,
        double** InitialConditions,
        std::string ResOutFileName
    );
    void Solve_TwoDimensions(int);
};

#endif //SOLVERS_HPP
