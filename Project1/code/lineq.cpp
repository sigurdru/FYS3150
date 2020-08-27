#include "lineq.hpp"
#include <iostream>
#include <cmath>
// #include <stdlib.h> // use for writing to file?

void Lineq::write_to_file (std::string fname) {
    std::cout << "x,computed,exact,rel_error,log10(error)" << std::endl;
    double x_val, comp_val, exact_val, rel_error, log_error;
    for (int i=0; i<m_n; i++) {
        x_val = m_x[i];
        comp_val = m_v[i];
        exact_val = m_exact[i];
        rel_error = fabs((comp_val - exact_val)/exact_val);
        log_error = log10(rel_error);
        std::cout << x_val << "," << comp_val << ","
            << exact_val << "," << rel_error << ","
            << log_error << std::endl;
    }
}
