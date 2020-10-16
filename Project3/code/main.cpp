#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "euler.hpp"
#include "verlet.hpp"
#include "solarsystem.hpp"

int main(int argc, char* argv[]) {
    std::string input_file;           // input file
    std::string output_file;          // output file
    int num_bodies;                   // number of planets
    double x, y, z, vx, vy, vz;       // To store initial conditions for each planet.
    double mass;                      // Store mass of planets.
    double dt;                        // Time between each step
    int N;                            // Number of integration points
    double mass_sun = 1.989e30;       // Mass of the sun
    if (argc < 5) {
        std::cout << "Please include input, output file, dt and number of time steps" << std::endl;
        exit(1);
    }
    else {
        // Store input, output file and dt
        output_file = "../output/";
        input_file = "../input/";
        input_file.append(argv[1]);
        output_file.append(argv[2]).append(".cvs");
        dt = std::atof(argv[3]);
        N = std::atoi(argv[4]);
    }

    char planet[20];

    const char* input_file_char = input_file.c_str();   //fopen takes char* so we convert
    FILE *init_file = fopen(input_file_char, "r");      //open file with initial conditions

    SolarSystem our_system;                             // initialize our system
    fscanf(init_file, "%i", &num_bodies);               // store number of bodies, dt, and number of time steps

    std::cout << num_bodies << std::endl;
    
    for (int i = 0; i < num_bodies; i++) {
        //Here we store the initial conditions and masses
        fscanf(init_file, 
            "%s %lf %lf %lf %lf %lf %lf %lf", 
            planet, &mass, &x, &y, &z, &vx, &vy, &vz
        );

        our_system.createCelestialBody(
            vec3(x, y, z),
            vec3(vx, vy, vz)*365, 
            mass/mass_sun);
    }
    fclose(init_file);  //close file with initial conditions
    std::vector<CelestialBody> &bodies = our_system.bodies();
    for(int i = 0; i<num_bodies; i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        std::cout << "The position of this object is " << body.position << " with velocity " << body.velocity << std::endl;
    }

    Euler integrator_euler(dt);
    for(int timestep=0; timestep<N; timestep++) {
        our_system.writeToFile("../output/positions_euler.xyz");
        integrator_euler.integrateOneStep(our_system);
    }

    // Verlet integrator_verlet(dt);
    // for (int timestep = 0; timestep < N; timestep++) {
    //     integrator_verlet.integrateOneStep(our_system);
    //     our_system.writeToFile("../output/positions_verlet.xyz");
    // }
}
