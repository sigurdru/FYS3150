#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "euler.hpp"
#include "verlet.hpp"
#include "solarsystem.hpp"

//test conservation of angular and energy
void testEnergy_and_Angular(SolarSystem& system, double tol_energy, double tol_angular);
//test conservation of kinetic and potential energy seperatly
void testKinetic_and_potential(SolarSystem& system, double tol_pot, double tol_kin);
//test for conservation of circular orbit
void testCirc_Orbit(CelestialBody& body, double tol_orbit);

int main(int argc, char* argv[]) {
    std::string input_file;         // input file
    std::string output_file;        // output file
    std::string solver_method;      // method for solving our system
    
    double dt;                      // Time between each step
    int N, print_step;              // Number of integration points
    double tol_angular = 1e-2;      // Tolerance on angular momentum conservation
    double tol_energy = 1e-3;       // Tolerance on energy conservation

    if (argc < 5) {
        std::cout << "Please include input file, output file, "
            << "dt and number of time ste ps" << std::endl;
        exit(1);
    }
    else {
        // Store input, output file, dt and N
        output_file = "../output/";
        input_file = "../input/";
        input_file.append(argv[1]);
        output_file.append(argv[2]).append(".xyz");
        dt = std::atof(argv[3]);
        N = std::atoi(argv[4]);
        solver_method = argv[5];
        print_step = 0.01/dt;

    }

    SolarSystem our_system;                             // initialize our system
    our_system.read_initial_conditions(input_file);     // read input file and add planets

    if (solver_method == "sun_earth_euler") {
        double tol_orbit = 1e-2;
        our_system.bodies()[1].position[0] = 1;
        our_system.bodies()[1].velocity[1] = 2*M_PI;
        our_system.print_our_system();
        our_system.calculateEnergyAndAngularMomentum();
        Euler solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            our_system.bodies()[1].force = vec3(0,0,0); //want a stationary sun
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
                testCirc_Orbit(our_system.bodies()[1], tol_orbit);
            }
        }
    }

    if (solver_method == "sun_earth_verlet") {
        double tol_orbit = 1e-7;
        double tol_kin = 1e-3;
        double tol_pot = 1e-3;
        our_system.bodies()[1].position[0] = 1;
        our_system.bodies()[1].velocity[1] = 2*M_PI;
        our_system.calculateEnergyAndAngularMomentum();
        our_system.print_our_system();
        Verlet solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            our_system.bodies()[1].force = vec3(0,0,0); //want a stationary sun
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
                testKinetic_and_potential(our_system, tol_kin, tol_pot);
                testCirc_Orbit(our_system.bodies()[1], tol_orbit);
            }
        }
    }
    our_system.calculateEnergyAndAngularMomentum();

    if (solver_method == "euler") {
        our_system.remove_cm_velocity();
        our_system.calculateEnergyAndAngularMomentum();
        Euler solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
            }
        }
    }
    
    if (solver_method == "verlet") {
        our_system.remove_cm_velocity();
        our_system.calculateEnergyAndAngularMomentum();
        Verlet solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
            }
        }    
    }

    // if (solver_method == "mercury_rel") {
    //     our_system.remove_cm_velocity();
    //     Verlet solver(dt);
    //     for (int timestep=0; timestep<N; timestep++) {
    //         our_system.calculateRelForces();
    //         solver.integrateOneStep(our_system);
    //         if (timestep%print_step == 0) {
    //             our_system.writeToFile(output_file);
    //             our_system.calculateEnergyAndAngularMomentum();
    //     }
    // }
}
void testEnergy_and_Angular(SolarSystem& system, double tol_energy, double tol_angular){
    double old_energy = system.totalEnergy();
    vec3 old_angular_momentum = system.angularMomentum();
    system.calculateEnergyAndAngularMomentum();
    double new_energy = system.totalEnergy();
    vec3 new_angular_momentum = system.angularMomentum();
    double d_energy = std::abs(old_energy - new_energy);
    double d_angular = (old_angular_momentum - new_angular_momentum).length();
    if (d_energy > tol_energy) {
        std::cout << "Total energy out of bounds" << std::endl;
        exit(1);
    }
    else if (d_angular > tol_angular) {
        std::cout << "Angular momentum out of bounds" << std::endl;
        exit(1);
    }
}

void testKinetic_and_potential(SolarSystem& system, double tol_kin, double tol_pot) {
    double old_kin = system.kineticEnergy();
    double old_pot = system.potentialEnergy();
    system.calculateEnergyAndAngularMomentum();
    double new_kin = system.kineticEnergy();
    double new_pot = system.potentialEnergy();
    double d_kin = std::abs(old_kin - new_kin);
    double d_pot = std::abs(old_pot - new_pot);
    if (d_kin > tol_kin) {
        std::cout << "Kinetic energy out of bounds" << std::endl;
        exit(1);
    }
    else if (d_pot > tol_pot) {
        std::cout << "Potential energy out of bounds" << std::endl;
        exit(1);
    }
}

void testCirc_Orbit(CelestialBody& body, double tol_orbit){
    double r = 1.; //what the radius should be
    double d_r =  std::abs(r - body.position.length());
    std::cout << d_r << std::endl;
    if (d_r > tol_orbit) {
        std::cout << "Orbit out of bounds" << std::endl;
        exit(1);
    }
}
