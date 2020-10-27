#include "celestialbody.hpp"
#include <cstring>

CelestialBody::CelestialBody(CelestialBodyData &data) {
    strcpy(name, data.name);
    type = data.type;
    position = data.position;
    velocity = data.velocity;
    mass = data.mass;
}

void CelestialBody::resetForce() {
    force.zeros();
}

CelestialBodyData::CelestialBodyData(
        char name_[], int body_type, 
        vec3 pos, 
        vec3 vel, 
        double mass_) {
    strcpy(name, name_);
    type = body_type;
    position = pos;
    velocity = vel;
    mass = mass_;
}

CelestialBodyData::CelestialBodyData(
        char name[], int body_type,
        double x, double y, double z,
        double vx, double vy, double vz,
        double mass) {
    vec3 pos = vec3(x, y, z);
    vec3 vel = vec3(vx, vy, vz);
    CelestialBodyData(name, body_type, pos, vel, mass);
}
