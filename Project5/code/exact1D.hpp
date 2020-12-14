
class Exact1D {
private:
    int N_Fourier;
    double L;
    double *FourierCoeffs;
public:
    Exact1D(int, double);
    ~Exact1D();
    double Call(double x, double t);
};
