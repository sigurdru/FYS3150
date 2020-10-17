#include "celestialbody.hpp"
#include <cstring>

CelestialBody::CelestialBody(char name_[], vec3 pos, vec3 vel, double mass_) {
    strcpy(name, name_);
    position = pos;
    velocity = vel;
    mass = mass_;
}

CelestialBody::CelestialBody(char name_[], 
        double x, double y, double z, 
        double vx, double vy, double vz, 
        double mass_) {
    strcpy(name, name_);
    position = vec3(x,y,z);
    velocity = vec3(vx,vy,vz);
    mass = mass_;
}

void CelestialBody::resetForce() {
    force.zeros();
}
