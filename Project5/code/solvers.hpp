#ifndef SOLVERS_HPP
#define SOLVERS_HPP
#include <fstream>

struct Solvers {
    // Here we define common stuff
    int Nx, Nt;
    double dt, t, dx, L, alpha;
    double *u, *b;
    std::string ResOutFileName;
    // std::ofile ResOutFile;
    void WriteToFile(std::string fname);
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
    void Solve(
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
    void Solve(
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

#endif //SOLVERS_HPP

