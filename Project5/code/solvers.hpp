#ifndef SOLVERS_HPP
#define SOLVERS_HPP
#include <fstream>

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
    void WriteToFile();
    void ProduceFName(std::string method);

public:
    double *u;
};

class ForwardEuler : public Solvers{
public:
    ForwardEuler(Parameters);
    void Solve_ForwardEuler(
        double BoundaryLeft(double),
        double BoundaryRight(double)
    );
    ~ForwardEuler();
};

class BackwardEuler : public Solvers {
public:
    BackwardEuler(Parameters);
    void Solve_BackwardEuler(
        double BoundaryLeft(double),
        double BoundaryRight(double)
    );
    ~BackwardEuler();
};

class CrankNicolson : public Solvers {
public:
    CrankNicolson(Parameters);
    void Solve_CrankNicolson(
        double BoundaryLeft(double),
        double BoundaryRight(double)
    );
    ~CrankNicolson();
};

#endif //SOLVERS_HPP

