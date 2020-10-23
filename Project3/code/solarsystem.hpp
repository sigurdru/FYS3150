#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <fstream>
#include <string>
#include <vector>
#include "celestialbody.hpp"

class SolarSystem {
    public:
        SolarSystem();
        CelestialBody& createCelestialBody(
            char name[], 
            vec3 position, 
            vec3 velocity, 
            double mass
        );
        void calculateForces();
        void calculateEnergyAndAngularMomentum();

        void remove_cm_velocity();
        void read_initial_conditions(std::string input_file);

        int numberOfBodies() const;
        double totalEnergy() const;
        double potentialEnergy() const;
        double kineticEnergy() const;
        void writeToFile(std::string filename);
        vec3 angularMomentum() const;
        std::vector<CelestialBody>& bodies();

    private:
        std::vector<CelestialBody> m_bodies;
        vec3 m_angularMomentum;
        std::ofstream m_file;
        double m_kineticEnergy;
        double m_potentialEnergy;
        double m_totalMassofSystem;
        vec3 m_totalMomentumofSystem;
        vec3 m_totalPositionofSystem;
};

#endif  // SOLARSYSTEM_H
