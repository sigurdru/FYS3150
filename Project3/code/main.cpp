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
    std::string input_file;     // input file
    std::string output_file;    // output file
    std::string solver_method;  // method for solving our system
    
    double dt;                  // Time between each step
    int N, print_step;          // Number of integration points
    // double tol_angular = 1e-2;  // Tolerance on angular momentum conservation
    // double tol_energy = 1e-3;   // Tolerance on energy conservation

    if (argc < 4) {
        std::cout << "Please include input file, "
            << "dt, number of time steps and solver method" << std::endl;
        exit(1);
    } else {
        // Store input, output file, dt and N
        output_file = "../output/positions/";
        input_file = "../input/";
        input_file.append(argv[1]).append(".txt");
        output_file.append(argv[1]).append(".xyz");
        dt = std::atof(argv[2]);
        N = std::atoi(argv[3]);
        solver_method = argv[4];
        print_step = 0.01/dt;
    }

    SolarSystem our_system;                         // initialize our system
    our_system.read_initial_conditions(input_file); // read input file and add planets
    our_system.printSystem();
    our_system.remove_cm_velocity();
    std::cout << std::endl << "Vel. and pos. of center of mass subtracted:";
    our_system.printSystem();
    our_system.calculateEnergyAndAngularMomentum();
    our_system.calculateForces();

    if (solver_method == "euler") {
        Euler solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) our_system.writeToFile(output_file);
        }
    } else if (solver_method == "verlet") {
        Verlet solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) our_system.writeToFile(output_file);
        }
    } else {
        std::cout << "Unknown method " << solver_method << std::endl;
        exit(1);
    }
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