#ifndef EULER_HPP
#define EULER_HPP


class Euler {
public:
    double m_dt;
    Euler(double dt);
    void integrateOneStep(class SolarSystem &system);
};

#endif // EULER_HPP