#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "euler.hpp"
#include "verlet.hpp"
#include "solarsystem.hpp"

int main(int argc, char* argv[]) {
    std::string input_file;         // input file
    std::string output_file;        // output file
    std::string solver_method;      // method for solving our system
    
    double dt;                      // Time between each step
    int N, print_step;              // Number of integration points
    int name_length = 10;           // length of planet names, unimportant

    if (argc < 5) {
        std::cout << "Please include input file, output file, "
            << "dt and number of time steps" << std::endl;
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

    std::vector<CelestialBody> &bodies = our_system.bodies();
    for (int i = 0; i<our_system.numberOfBodies(); i++) {
        CelestialBody &body = bodies[i];            // Reference to this body
        printf("\n%-*s", name_length, body.name);   // print body name
        std::cout << body.position << std::endl;    // print position
        printf("%*s", name_length, "");
        std::cout << body.velocity << std::endl;    // print velocity
        std::cout << body.mass << std::endl;
    }

    if (solver_method == "sun_earth_euler") {
        our_system.bodies()[1].position[0] = 1;
        our_system.bodies()[1].velocity[1] = 2*M_PI;
        Euler solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            our_system.bodies()[1].force = vec3(0,0,0); //want a stationary sun
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
                our_system.calculateEnergyAndAngularMomentum();
            }
        }
    }

    if (solver_method == "sun_earth_verlet") {
        our_system.bodies()[1].position[0] = 1;
        our_system.bodies()[1].velocity[1] = 2*M_PI;
        Verlet solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            our_system.bodies()[1].force = vec3(0,0,0); //want a stationary sun
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
                our_system.calculateEnergyAndAngularMomentum();
            }
        }
    }

    if (solver_method == "euler") {
        our_system.remove_cm_velocity();
        Euler solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
                our_system.calculateEnergyAndAngularMomentum();
            }
        }
    }
    
    if (solver_method == "verlet") {
        our_system.remove_cm_velocity();
        Verlet solver(dt);
        for (int timestep=0; timestep<N; timestep++) {
            our_system.calculateForces();
            solver.integrateOneStep(our_system);
            if (timestep%print_step == 0) {
                our_system.writeToFile(output_file);
                our_system.calculateEnergyAndAngularMomentum();
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
