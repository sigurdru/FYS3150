#ifndef SOLVERS_HPP
#define SOLVERS_HPP
#include <fstream>
#include <iostream>

struct Parameters {
    int Nx, Nt;
    double dt, L;
    std::string ResOutFileName;
};

class Solvers : public Parameters {
protected:
    // Here we define common stuff
    double t, dx, alpha;
    double *b;
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
    ForwardEuler(Parameters, double *initialCondition);
    void Solve(
        double BoundaryLeft(double),
        double BoundaryRight(double),
        int NumberOfprints
    );
    ~ForwardEuler();
};

class BackwardEuler : public Solvers {
public:
    BackwardEuler(Parameters, double *initialCondition);
    void Solve(
        double BoundaryLeft(double),
        double BoundaryRight(double),
        int NumberOfPrints
    );
    ~BackwardEuler();
};

class CrankNicolson : public Solvers {
public:
    CrankNicolson(Parameters, double *initialCondition);
    void Solve(
        double BoundaryLeft(double),
        double BoundaryRight(double),
        int NumberOfprints
    );
    ~CrankNicolson();
};

class TwoDimensions : public Solvers {
public:
    double **u;
    double **b;
    void WriteToFile();
    TwoDimensions(Parameters, double** InitialConditions);
    void Solve_TwoDimensions(int);
};

#endif //SOLVERS_HPP
