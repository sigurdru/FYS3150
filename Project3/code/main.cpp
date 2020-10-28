#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "euler.hpp"
#include "verlet.hpp"
#include "solarsystem.hpp"

// test conservation of angular and energy
void testEnergy_and_Angular(SolarSystem& system, double tol_energy, double tol_angular);
// test conservation of kinetic and potential energy seperatly
void testKinetic_and_potential(SolarSystem& system, double tol_pot, double tol_kin);
// test for conservation of circular orbit
void testCirc_Orbit(CelestialBody& body, double tol_orbit);

int main(int argc, char* argv[]) {
    std::string input_file, output_file, solver_method;
    
    double dt, distDependence;  // Time between each step and parameter beta
    int N, print_step;          // Number of integration points
    bool shouldPrint;
    // double tol_angular = 1e-2;  // Tolerance on angular momentum conservation
    // double tol_energy = 1e-3;   // Tolerance on energy conservation

    if (argc < 5) {
        std::cout << "Please include input file, dt, number of time steps, "
            << "solver method and distance dependence parameter beta" 
            << std::endl;
        exit(1);
    } else {
        // Store input, dt, N, solver_method and distDependence
        input_file = "../input/";
        output_file = "../output/positions/";
        input_file.append(argv[1]).append(".txt");
        dt = std::atof(argv[2]);
        N = std::atoi(argv[3]);
        solver_method = argv[4];
        distDependence = std::atof(argv[5]);
        print_step = 0.01/dt;
        output_file.append(argv[1]).append("-") // same name as input file
            .append(argv[4]).append("-")        //   + solver_method
            .append(argv[2]).append("-")        //   + dt
            .append(argv[3]).append("-")        //   + N
            .append(argv[5]).append(".xyz");    //   + distance dependence
    }

    SolarSystem our_system(distDependence);         // initialize our system
    our_system.read_initial_conditions(input_file); // read input file and add planets
    our_system.printSystem();
    our_system.remove_cm_velocity();
    std::cout << std::endl << "Vel. and pos. of center of mass subtracted:";
    our_system.printSystem();
    our_system.calculateEnergyAndAngularMomentum();

    // Solve!
    if (solver_method == "euler") {
        Euler solver(dt);
        our_system.calculateForces();
        for (int timestep=0; timestep<N; timestep++) {
            solver.integrateOneStep(our_system);
            shouldPrint = (timestep%print_step == 0);
            if (shouldPrint) {
                our_system.calculateEnergyAndAngularMomentum();
                our_system.writeToFile(output_file);
            }
        }
    } else if (solver_method == "verlet") {
        Verlet solver(dt, our_system);
        our_system.calculateForces();
        for (int timestep=0; timestep<N; timestep++) {
            solver.integrateOneStep1();
            our_system.calculateForces();
            solver.integrateOneStep2();
            shouldPrint = (timestep%print_step == 0);
            if (shouldPrint) {
                our_system.calculateEnergyAndAngularMomentum();
                our_system.writeToFile(output_file);
            }
        }
    } else if (solver_method == "Mercury") {
        Verlet solver(dt, our_system);
        our_system.calculateMercForces();
        for (int timestep=0; timestep<N; timestep++) {
            solver.integrateOneStep1();
            our_system.calculateMercForces();
            solver.integrateOneStep2();
            shouldPrint = (timestep%print_step == 0);
            if (shouldPrint) {
                our_system.calculateEnergyAndAngularMomentum();
                our_system.writeToFile(output_file);
            }
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
