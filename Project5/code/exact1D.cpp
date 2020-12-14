#include <cmath>
#include "exact1D.hpp"

Exact1D::Exact1D (int N_Fourier, double L)
{
    this->N_Fourier = N_Fourier;
    this->L = L;
    FourierCoeffs = new double[N_Fourier];
    for (int n = 1; n <= N_Fourier; n++)
        FourierCoeffs[n-1] = 2*(M_PI*n*cos(M_PI*n) - sin(M_PI*n))/(M_PI*M_PI*n*n);
}

double Exact1D::Call (double x, double t)
{
    double Value = x/L;
    double C;
    for (int n = 1; n <= N_Fourier; n++) {
        C = n*M_PI/L;
        Value += FourierCoeffs[n-1]*exp(-C*C*t)*sin(C*x);
    }
    return Value;
}

Exact1D::~Exact1D()
{
    delete[] FourierCoeffs;
}
