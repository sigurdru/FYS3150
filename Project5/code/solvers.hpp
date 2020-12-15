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
private:
    bool *completed;
    int numCores;
    void ResetMatrices();

public:
    double **u;
    TwoDimensions(Parameters, double* InitialConditions, int numCores);
    ~TwoDimensions();
    void WriteToFile();
    static inline int Index2D(int row, int rowLength, int col) 
        { return row*rowLength + col; }
    void Solve();
    void WriteMatrix();
    void WriteCompleted();
};

#endif //SOLVERS_HPP
