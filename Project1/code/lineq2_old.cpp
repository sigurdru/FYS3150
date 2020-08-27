#include <cmath>
#include <iostream>
#include <chrono> // Time the code

// The function we are evaluating
inline double f(double x) { return 100.0 * exp(-10.0 * x); }
// Exact solution
inline double exact(double x) { return 1.0 - (1.0 - exp(-10.0)) * x - exp(-10 * x); }

int main(int argc, char* argv[]){
    // Starter klokken
    auto start = std::chrono::high_resolution_clock::now();
    int n;
    double h;
    if (argc < 2) {
        std::cout << "Give me args" << std::endl;
        exit(1);
    }
    else {
        n = atoi(argv[1]);
        h = 1.0 / (n - 1);
    }

    double *alpha = new double[n - 1];
    double *rho = new double[n];
    double *v = new double[n];

    alpha[0] = -1/2;
    rho[0] = f(0) / 2;
    // forward substitution
    for (int i = 1; i < n; i++) {
        rho[i] = (f(i*h) + rho[i - 1]) / (2 + alpha[i - 1]);
        alpha[i] = 1 / (2 + alpha[i - 1]);
    }
    // backward substitution
    v[n - 1] = rho[n - 1];
    for (int i = n; i > 0; i--){
        v[i - 1] = rho[i - 1] - alpha[i - 1] * v[i];
    }
    // output the results
    std::cout << "x,computed,exact,rel_error,log10(error)" << std::endl;
    double x_val, comp_val, exact_val, rel_error, log_error;
    for (int i = 0; i < n; i++){
        x_val = i*h;
        comp_val = v[i];
        exact_val = exact(i*h);
        rel_error = fabs((comp_val - exact_val) / exact_val);
        log_error = log10(rel_error);
        std::cout << x_val << "," << comp_val << ","
                  << exact_val << "," << rel_error << ","
                  << log_error << std::endl;
    }

    // cleanup
    // delete[] alpha;
    // delete[] rho;
    // delete[] b_tilde;
    // delete[] v;
    // delete[] x;
    // stop clock
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    // std::cout << 'Time used:' << duration.count() << 'microseconds' << std::endl;
    return 0;
}