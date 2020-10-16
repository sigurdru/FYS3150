#include "solarsystem.hpp"
#include "verlet.hpp"


Verlet::Verlet(double dt): m_dt(dt) {}

void Verlet::integrateOneStep(SolarSystem &system) {
    system.calculateForces();
    int N = numberOfBodies();
    double* current_accelerations[N];
    int i = 0;
    for (CelestialBody &body : system.bodies() ) {
        double current_acceleration[i] = body.force/body.mass;
        body.position += m_dt*body.velocity + m_dt**2*current_acceleration[i]/2;
        i++;
    }
    system.calculateForces(); 
    i = 0;
    for (CelestialBody &body : system.bodies() ) {
        body.velocity += m_dt*(current_acceleration[i] + body.force/body.mass);
        i++;
    }
}