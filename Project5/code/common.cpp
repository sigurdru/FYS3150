#include "tridiag.hpp"
#include <iostream>
#include <cmath>
#include <fstream>

void Common::write_to_file (std::string fname) {
    std::string res_fname, error_fname;
    res_fname.append(fname);
    res_fname.append(".txt");
    error_fname.append(fname);
    error_fname.append("_error.txt");
    double x_val, comp_val, exact_val, rel_error, log_error;
    double max_rel_error, max_log_error;
    max_rel_error = 0.0;
    max_log_error = 0.0;
    std::ofstream myfile;
    myfile.open (res_fname);
    myfile << "x,computed,exact,rel_error,log10(error)" << std::endl;
    for (int i=0; i<m_n; i++) {
        x_val = m_x[i];
        comp_val = m_comp[i];
        exact_val = m_exact[i];
        rel_error = fabs((comp_val - exact_val) / exact_val);
        log_error = log10(rel_error);
        if (log_error < 0 && rel_error > max_rel_error) {
            max_rel_error = rel_error;
            max_log_error = log_error;
        }
        myfile << x_val << "," << comp_val << ","
               << exact_val << "," << rel_error << ","
               << log_error << std::endl;
    }
    myfile.close();

    myfile.open(error_fname);
    myfile << max_log_error << std::endl;
    myfile.close();
}
