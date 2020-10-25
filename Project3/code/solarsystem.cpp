#include "solarsystem.hpp"
#include <cmath>
#include <iostream>
using namespace std;

SolarSystem::SolarSystem() : m_kineticEnergy(0), m_potentialEnergy(0) {}

CelestialBody& SolarSystem::createCelestialBody(char name[],
                                                int body_type,
                                                vec3 position,
                                                vec3 velocity,
                                                double mass) {
    m_bodies.push_back(CelestialBody(name, body_type, position, velocity, mass));
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
            body1.force += body1.mass*body2.mass*deltaRVector/(dr*dr*dr);
            body2.force -= body1.force;
        }
        body1.force *= 4*M_PI*M_PI;
    }
}

void SolarSystem::calculateEnergyAndAngularMomentum() {
    // Calculate total angular momentum and energy
    m_angularMomentum.zeros();
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    for (int i = 0; i < numberOfBodies(); i++) {
        CelestialBody& body1 = m_bodies[i];
        m_kineticEnergy += body1.mass * body1.velocity.lengthSquared();
        m_angularMomentum += body1.position.cross(body1.velocity);
        for (int j = i + 1; j < numberOfBodies(); j++){
            CelestialBody& body2 = m_bodies[j];
            vec3 deltaRVector = body2.position - body1.position;
            double dr = deltaRVector.length();
            m_potentialEnergy -= body1.mass*body2.mass/dr;
        }
    }
    m_kineticEnergy *= 0.5;
    m_potentialEnergy *= 8*M_PI*M_PI;
}


void SolarSystem::read_initial_conditions(string input_file) {
    int num_bodies, body_type;                 // number of planets
    double mass_sun = 1.989e30;     // Mass of the sun
    double reduced_mass;

    double x, y, z, vx, vy, vz;     // To store initial conditions for each planet.
    double mass;                    // Store mass of planets.

    int name_length = 10;           // length of planet names, unimportant
    char name[name_length];         // capture the name of object
    const char* input_file_char = input_file.c_str();   // fopen takes char* so we convert
    FILE *init_file = fopen(input_file_char, "r");      // open file with initial conditions

    fscanf(init_file, "%i", &num_bodies);               // read number of bodies
    
    for (int i = 0; i < num_bodies; i++) {
        // Read names, masses and initial conditions
        fscanf(init_file, 
            "%s %i %lf %lf %lf %lf %lf %lf %lf", 
            name, &body_type, &mass, &x, &y, &z, &vx, &vy, &vz
        );
        reduced_mass = mass/mass_sun;
        m_totalMassofSystem += reduced_mass;           // calculate total mass of system, useful for potential energy
        m_totalMomentumofSystem += vec3(vx, vy, vz)*reduced_mass;
        m_totalPositionofSystem += vec3(x, y, z)*reduced_mass;
        
        createCelestialBody(
            name,
            body_type,
            vec3(x, y, z),
            vec3(vx, vy, vz)*365,       // convert from AU/day to AU/yr
            reduced_mass);             // convert from kg to sun masses
    }
    fclose(init_file);  // close file with initial conditions
}

void SolarSystem::remove_cm_velocity() {
    for (CelestialBody& body: m_bodies){
        body.velocity -= m_totalMomentumofSystem/m_totalMassofSystem;
        body.position -= m_totalPositionofSystem/m_totalMassofSystem;
    }
}

void SolarSystem::print_our_system() {
    // Print the system
    int name_length = 10;  // length of planet names, unimportant
    for (int i = 0; i<numberOfBodies(); i++) {
        CelestialBody &body = bodies()[i];            // Reference to this body
        printf("\n%-*s", name_length, body.name);   // print body name
        std::cout << body.position << std::endl;    // print position
        printf("%*s", name_length, "");
        std::cout << body.velocity << std::endl;    // print velocity
        std::cout << "mass: " << body.mass << std::endl;
    }

}

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
        m_file << body.name << " " << body.position.x() << " " << body.position.y() << " "
        << body.position.z() << "\n";
    }
}


vec3 SolarSystem::angularMomentum() const {
    return m_angularMomentum;
}

std::vector<CelestialBody>& SolarSystem::bodies() {
    return m_bodies;
}
