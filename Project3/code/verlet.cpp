#include "solarsystem.hpp"
#include "verlet.hpp"

Verlet::Verlet(double dt) : m_dt(dt) {}

void Verlet::integrateOneStep(SolarSystem &system) {
    int N = system.numberOfBodies();
    vec3 current_accelerations[N];
    int i = 0;
    for (CelestialBody &body : system.bodies() ) {
        current_accelerations[i] = body.force/body.mass;
        body.position += m_dt*body.velocity + m_dt*m_dt*current_accelerations[i]/2;
        i++;
    }
    system.calculateForces(); 
    i = 0;
    for (CelestialBody &body : system.bodies() ) {
        body.velocity += m_dt*(current_accelerations[i] + body.force/body.mass);
        i++;
    }
}