#include "jacobi.hpp"

int main() {
    double a = 1.0;
    double b = 2.0;
    int N = 5;

    JacobiRot inst;
    inst.initialize(a, b, N);
    inst.print_mat();
    inst.solve(3.4);

    return 0;
}
