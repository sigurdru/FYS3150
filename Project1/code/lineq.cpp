#include "lineq.hpp"
#include <iostream>
#include <cmath>
#include <fstream>

void Lineq::write_to_file (std::string fname) {
    std::ofstream myfile;
    double x_val, comp_val, exact_val, rel_error, log_error;
    myfile.open (fname);
    myfile << "x,computed,exact,rel_error,log10(error)" << std::endl;
    for (int i=0; i<m_n; i++) {
        x_val = m_x[i];
        comp_val = m_v[i];
        exact_val = m_exact[i];
        rel_error = fabs((comp_val - exact_val) / exact_val);
        log_error = log10(rel_error);
        myfile << x_val << "," << comp_val << ","
               << exact_val << "," << rel_error << ","
               << log_error << std::endl;
    }
    myfile.close();
}