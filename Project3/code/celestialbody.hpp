#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP
#include "vec3.hpp"

class CelestialBody {
    public:
        char name[10];
        vec3 position;
        vec3 velocity;
        vec3 force;
        double mass;
        int type;

    CelestialBody(char name[], int body_type, vec3 position, vec3 velocity, double mass);
    CelestialBody(char name[], 
                  int body_type,
                  double x,
                  double y,
                  double z,
                  double vx,
                  double vy,
                  double vz,
                  double mass);
    void resetForce();
};
#endif  // CELESTIALBODY_HPP
