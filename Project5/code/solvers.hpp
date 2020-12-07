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
    // Forward Euler solver class
    private:
    protected:
    public:
        ForwardEuler(int num_int_points, int num_time_points, 
                      float dtimestep, double *InitialCondition,
                      std::string ResOutFileName);
        void Solve_ForwardEuler(double BoundaryLeft(double),
                                double BoundaryRight(double));
        ~ForwardEuler();
};

class BackwardEuler : public Solvers {
    // Backward Euler solver class
    private:
    public:
        BackwardEuler(int num_int_points, int num_time_points, 
                      float dtimestep, double *InitialCondition,
                      std::string ResOutFileName);
        void Solve_BackwardEuler(double BoundaryLeft(double),
                                 double BoundaryRight(double));
        ~BackwardEuler();
};

class CrankNicolson : public Solvers {
    // Crank-Nicolson solver class
    public:
        CrankNicolson(int num_int_points,
                    int num_time_points,
                    float dtimestep,
                    double* InitialCondition,
                    std::string ResOutFileName);
        void Solve_CrankNocolson(double BoundaryLeft(double),
                                double BoundaryRight(double));
        ~CrankNicolson();
};

#endif //SOLVERS_HPP

