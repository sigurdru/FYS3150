#ifndef VERLET_HPP
#define VERLET_HPP

class Verlet {
private:
    double m_dt;
    class SolarSystem& m_system;
public:
    Verlet(double dt, class SolarSystem& system);
    void integrateOneStep1();
    void integrateOneStep2();
};

#endif //VERLET_HPP