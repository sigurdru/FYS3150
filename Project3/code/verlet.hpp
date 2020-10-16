#ifndef VERLET_HPP
#define VERLET_HPP

class Verlet {
private:
    double m_dt;
public:
    Verlet(double dt);
    void Solver(class SolarSystem &system);
};

#endif //VERLET_HPP