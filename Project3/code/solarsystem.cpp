#include "solarsystem.hpp"
#include <cmath>
#include <iostream>
using namespace std;

SolarSystem::SolarSystem(double distDependence) : 
    m_kineticEnergy(0), 
    m_potentialEnergy(0),
    distDependence(distDependence) {}

CelestialBody& SolarSystem::createCelestialBody(CelestialBodyData &data) {
    m_bodies.push_back(CelestialBody(data));
    return m_bodies.back();  // Return reference to the newest added celstial body
}

void SolarSystem::calculateForces() {
    // reset force of all bodies
    for (CelestialBody& body : m_bodies) body.resetForce();

    vec3 deltaRVec, force;
    double dr;
    for (int i = 0; i < numberOfBodies(); i++) {
        CelestialBody& body1 = m_bodies[i];
        for (int j = i + 1; j < numberOfBodies(); j++) {
            CelestialBody& body2 = m_bodies[j];
            deltaRVec = body2.position - body1.position;
            dr = deltaRVec.length();
            force = body1.mass*body2.mass*deltaRVec/pow(dr, distDependence+1);
            body1.force += force;
            body2.force -= force;
        }
        body1.force *= 4*M_PI*M_PI;
    }
}

void SolarSystem::calculateMercForces() {
    //calculate the relative force on Mercury
    for (CelestialBody& body: m_bodies) body.resetForce();

    double dr;
    double l;
    double c = 63239.7263;
    CelestialBody& mercury = m_bodies[1];
    dr = mercury.position.length();
    l = (mercury.position.cross(mercury.velocity)).length();
    mercury.force -= 4*M_PI*M_PI*mercury.mass*m_bodies[0].mass*mercury.position/(dr*dr*dr);
    mercury.force *= (1 + 3*l*l/(dr*dr*c*c));
}

void SolarSystem::calculateEnergyAndAngularMomentum() {
    // Calculate total angular momentum and energy
    double dr;
    vec3 deltaRVector;
    m_angularMomentum.zeros();
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    double pos_dependence = 1 - distDependence;
    for (int i = 0; i < numberOfBodies(); i++) {
        CelestialBody& body1 = m_bodies[i];
        m_kineticEnergy += body1.mass * body1.velocity.lengthSquared();
        m_angularMomentum += body1.mass*body1.position.cross(body1.velocity);
        for (int j = i + 1; j < numberOfBodies(); j++){
            CelestialBody& body2 = m_bodies[j];
            deltaRVector = body2.position - body1.position;
            dr = deltaRVector.length();
            m_potentialEnergy += body1.mass*body2.mass*pow(dr, pos_dependence);
        }
    }
    m_kineticEnergy *= 0.5;
    m_potentialEnergy *= 8*M_PI*M_PI/pos_dependence;
}


void SolarSystem::read_initial_conditions(string input_file) {
    int num_bodies, body_type;      // number of planets, and type identifier
    double mass_sun = 1.989e30;     // Mass of the sun
    double x, y, z, vx, vy, vz;     // To store initial cond. for each planet
    vec3 pos, vel;
    double mass;                    // Store mass of planets.

    int name_length = 10;           // length of planet names, unimportant
    char name[name_length];         // capture the name of object

    // fopen takes char* so we convert
    const char* input_file_char = input_file.c_str();
    // open file with initial conditions
    FILE *init_file = fopen(input_file_char, "r");

    fscanf(init_file, "%i", &num_bodies);   // read number of bodies
    std::cout << '1' << std::endl;
    for (int i = 0; i < num_bodies; i++) {
        // Read names, types, masses and initial conditions
        fscanf(init_file, 
            "%s %d %lf %lf %lf %lf %lf %lf %lf", 
            name, &body_type, &mass, &x, &y, &z, &vx, &vy, &vz
        );
        mass /= mass_sun;               // convert from kg to sun masses
        pos = vec3(x, y, z);
        vel = vec3(vx, vy, vz)*365;     // convert from AU/day to AU/yr
        m_totalMassofSystem += mass;    // calculate total mass of system
        m_totalMomentumofSystem += vel*mass;
        m_totalPositionofSystem += pos*mass;
        
        CelestialBodyData data(name, body_type, pos, vel, mass);
        createCelestialBody(data);
    }
    fclose(init_file);  // close file with initial conditions
}

void SolarSystem::remove_cm_velocity() {
    for (CelestialBody& body: m_bodies){
        body.velocity -= m_totalMomentumofSystem/m_totalMassofSystem;
        body.position -= m_totalPositionofSystem/m_totalMassofSystem;
    }
}

void SolarSystem::printSystem() {
    // Print the system
    int name_length = 10;  // length of planet names, unimportant
    for (int i = 0; i<numberOfBodies(); i++) {
        CelestialBody &body = bodies()[i];          // Reference to this body
        printf("\n%-*s pos:  ", name_length, body.name);   // print body name
        cout << body.position << endl;    // print position
        printf("%*s vel:  ", name_length, "");
        cout << body.velocity << endl;    // print velocity
        printf("%*s mass: ", name_length, "");
        cout << body.mass << endl;
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
    m_file << potentialEnergy() 
        << " " << kineticEnergy() 
        << " " << totalEnergy() 
        << " " << angularMomentum() 
        << endl;
    for (CelestialBody& body : m_bodies) {
        m_file << body.name << " " << body.type << " " << body.position.x() 
            << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}


vec3 SolarSystem::angularMomentum() const {
    return m_angularMomentum;
}

vector<CelestialBody>& SolarSystem::bodies() {
    return m_bodies;
}
