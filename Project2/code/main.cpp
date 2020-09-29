#include "jacobi.hpp"
#include <iostream>
#include <string>

double V(double rho, double omega_r);
double V_2(double rho, double omega_r);
double BB_eigvals(double a, double d, int j, int N);
double BB_eigvec(int j, int N);
double QM_eigval(int j);

int main(int argc, char* argv[]) {
    int n;
    double omega_r;
    std::string fname;
    std::string method;
    if (argc < 4) {
        std::cout << "Give me args" << std::endl;
        exit(1);
    }
    else {
        n = std::atoi(argv[1]);
        method = argv[2];
        omega_r = std::atof(argv[3]);
        fname = "../output/";
        fname.append(method).append("_").
            append(argv[1]).append("_").
            append(argv[3]).append(".csv");
    }

    float eps = 1e-40;
    int max_iter = 1000000;
    float rho0 = 0.;
    float rhoN = 5.;

    if (method == "BB") {
        JacobiRot solver;
        double h = 1.0/n;
        double *x = new double[n-1];
        x[0] = h;
        for (int i=0; i<n-2; i++) x[i+1] = x[i] + h;
        double a = -1.0/(h*h);
        double d = 2.0/(h*h);
        solver.initialize(a, d, x, n);
        solver.solve(eps, max_iter);
        solver.write_to_file(fname, BB_eigvals, BB_eigvec);
    } else if (method == "QM1") {
        QM qm_solver;
        qm_solver.initialize(n, rho0, rhoN, V, omega_r);
        qm_solver.solve(eps, max_iter);
        qm_solver.write_to_file(fname, QM_eigval);
    } else if (method == "QM2") {
        QM qm_solver;
        qm_solver.initialize(n, rho0, rhoN, V_2, omega_r);
        qm_solver.solve(eps, max_iter);
        qm_solver.write_to_file(fname);
    } else {
        std::cout << "Bad task argument: " << method << std::endl;
        return 1;
    }
    return 0;
}

double V(double rho, double omega_r) {
    return rho*rho;
}

double V_2(double rho, double omega_r) {
    return omega_r*omega_r*rho*rho + 1/rho;
}

double BB_eigvals (double a, double d, int j, int N) {
    return d + 2*a*std::cos(j*3.1415/N);
}

double BB_eigvec (int j, int N) {
    return std::sin(j*3.1415/N);
}

double QM_eigval (int j) {
    return 3 + 4*(j - 1);
}
