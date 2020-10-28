#include "solarsystem.hpp"
#include "verlet.hpp"

Verlet::Verlet(double dt, SolarSystem& system) : m_dt(dt), m_system(system) {}

void Verlet::integrateOneStep1() {
    for (CelestialBody &body : m_system.bodies() ) {
        body.position += m_dt*body.velocity + m_dt*m_dt/2*body.force/body.mass;
        body.velocity += m_dt/2*body.force/body.mass;
    }
}
void Verlet::integrateOneStep2() {
    for (CelestialBody &body : m_system.bodies() ) {
        body.velocity += m_dt/2*body.force/body.mass;
    }
}
