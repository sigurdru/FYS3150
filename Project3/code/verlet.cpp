#include "solarsystem.hpp"
#include "verlet.hpp"

Verlet::Verlet(double dt) : m_dt(dt) {}

void Verlet::integrateOneStep(SolarSystem &system) {
    for (CelestialBody &body : system.bodies() ) {
        body.position += m_dt*body.velocity + m_dt*m_dt/2*body.force/body.mass;
        body.velocity += m_dt/2*body.force/body.mass;
    }
    system.calculateForces(); 
    for (CelestialBody &body : system.bodies() ) {
        body.velocity += m_dt/2*body.force/body.mass;
    }
}
