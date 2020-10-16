#include "solarsystem.hpp"
#include <cmath>
#include <iostream>
using namespace std;

SolarSystem::SolarSystem() : m_kineticEnergy(0), m_potentialEnergy(0) {}

CelestialBody& SolarSystem::createCelestialBody(vec3 position,
                                                vec3 velocity,
                                                double mass) {
    m_bodies.push_back(CelestialBody(position, velocity, mass));
    return m_bodies.back();  // Return reference to the newest added celstial body
}

void SolarSystem::calculateForces() {
    for (CelestialBody& body : m_bodies) {
        // Reset forces on all bodies
        body.force.zeros();
    }

    for (int i = 0; i < numberOfBodies(); i++) {
        CelestialBody& body1 = m_bodies[i];
        for (int j = i + 1; j < numberOfBodies(); j++) {
            CelestialBody& body2 = m_bodies[j];
            vec3 deltaRVector = body2.position - body1.position;
            double dr = deltaRVector.length();
            // Calculate the force
            body1.force += body2.mass*body1.mass*4*M_PI*M_PI*deltaRVector/(dr*dr*dr);
            body2.force -= body1.force;
        }
    }
}

// MANGLER Å REGNE UT ANGULAR MOMENTUM
void SolarSystem::calculateEnergyAndAngularMomentum() {
    m_angularMomentum.zeros();
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    for (int i = 0; i < numberOfBodies(); i++) {
        CelestialBody& body1 = m_bodies[i];
        m_kineticEnergy += 0.5 * body1.mass * body1.velocity.lengthSquared();
        for (int j = 0; j < numberOfBodies(); j++){
            if (j != i) {
                CelestialBody& body2 = m_bodies[j];
                vec3 deltaRVector = body1.position - body2.position;
                m_potentialEnergy += body2.mass/deltaRVector.length();
            }
        }
        m_potentialEnergy *= body1.mass;
    }
    m_potentialEnergy *= 4*M_PI;
}
// MANGLER

int SolarSystem::numberOfBodies() const {
    return m_bodies.size();
}

double SolarSystem::totalEnergy() const {
    return m_kineticEnergy + m_potentialEnergy;
}

double SolarSystem::potentialEnergy() const {
    return m_potentialEnergy;
}

double SolarSystem::kineticEnergy() const {
    return m_kineticEnergy;
}

void SolarSystem::writeToFile(string filename) {
    if (!m_file.good()) {
        m_file.open(filename.c_str(), ofstream::out);
        if (!m_file.good()) {
            cout << "Error opening file " << filename << ". Aborting!" << endl;
            terminate();
        }
    }

    m_file << numberOfBodies() << endl;
    m_file << "Comment line that needs to be here. Balle." << endl;
    for (CelestialBody& body : m_bodies) {
        m_file << "1 " << body.position.x() << " " << body.position.y() << " "
        << body.position.z() << "\n";
    }
}

vec3 SolarSystem::angularMomentum() const {
    return m_angularMomentum;
}

std::vector<CelestialBody>& SolarSystem::bodies() {
    return m_bodies;
}
