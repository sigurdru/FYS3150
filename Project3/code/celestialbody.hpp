#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP
#include "vec3.hpp"

struct CelestialBodyData {
    char name[10];
    vec3 position, velocity, force;
    double mass;
    int type;

    CelestialBodyData(
            char name[], int body_type, 
            vec3 position, 
            vec3 velocity, 
            double mass);
    CelestialBodyData(
            char name[], int body_type,
            double x, double y, double z,
            double vx, double vy, double vz,
            double mass);
};

class CelestialBody {
    public:
        char name[10];
        vec3 position, velocity, force;
        double mass, kineticEnergy, potentialEnergy;
        int type;

    CelestialBody(CelestialBodyData &data);
    void resetForce();
};

#endif  // CELESTIALBODY_HPP
