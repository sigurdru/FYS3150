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
    int num_bodies;                 // number of planets
    double x, y, z, vx, vy, vz;     // To store initial conditions for each planet.
    double mass;                    // Store mass of planets.
    double dt;                      // Time between each step
    int N, print_step;              // Number of integration points
    double mass_sun = 1.989e30;     // Mass of the sun
    int name_length = 10;           // length of planet names, unimportant
    char name[name_length];         // capture the name of objects

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
        print_step = 0.01/dt;

    }

    const char* input_file_char = input_file.c_str();   // fopen takes char* so we convert
    FILE *init_file = fopen(input_file_char, "r");      // open file with initial conditions

    SolarSystem our_system;                             // initialize our system
    fscanf(init_file, "%i", &num_bodies);               // read number of bodies
    std::cout << "Simulating with " << num_bodies << " bodies" << std::endl;
    std::cout << "Printing every " << print_step << " steps" << std::endl;
    
    for (int i = 0; i < num_bodies; i++) {
        // Read names, masses and initial conditions
        fscanf(init_file, 
            "%s %lf %lf %lf %lf %lf %lf %lf", 
            name, &mass, &x, &y, &z, &vx, &vy, &vz
        );

        our_system.createCelestialBody(
            name,
            vec3(x, y, z),
            vec3(vx, vy, vz)*365,       // convert from AU/day to AU/yr
            mass/mass_sun);             // convert from kg to sun masses
    }
    fclose(init_file);  // close file with initial conditions

    std::vector<CelestialBody> &bodies = our_system.bodies();
    for (int i = 0; i<num_bodies; i++) {
        CelestialBody &body = bodies[i];            // Reference to this body
        printf("\n%-*s", name_length, body.name);   // print body name
        std::cout << body.position << std::endl;    // print position
        printf("%*s", name_length, "");
        std::cout << body.velocity << std::endl;    // print velocity
    }

    Euler solver(dt);
    // Verlet solver(dt);
    for (int timestep=0; timestep<N; timestep++) {
        solver.integrateOneStep(our_system);
        if (timestep%print_step == 0) {
            our_system.writeToFile(output_file);
        }
    }

}
