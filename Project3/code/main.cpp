#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "euler.hpp"
#include "solarsystem.hpp"

int main(int argc, char* argv[]) {
    std::string input_file;           // input file
    std::string output_file;          // output file
    int num_bodies;                   // number of planets
    double x, y, z, vx, vy, vz;       // To store initial conditions for each planet.
    double mass;                      // Store mass of planets.
    double dt;                        // Time between each step
    int N;                            // Number of integration points
    if (argc < 3) {
        std::cout << "Please include input and output file" << std::endl;
    }
    else {
        // Store input and output file
        output_file = "../output/";
        input_file = "../input/";
        input_file.append(argv[1]);
        output_file.append(argv[2]).append(".cvs");
    }

    const char* input_file_char = input_file.c_str(); //fopen takes char* so we convert
    FILE *init_file = fopen(input_file_char, "r"); //open file with initial conditions
    
    //initialize our system
    SolarSystem our_system;
    //store number of bodies, dt, and number of time steps
    fscanf(init_file, "%i %lf %i", &num_bodies, &dt, &N);
    
    for (int i = 0; i < num_bodies; i++) {
        //Here we store the initial conditions and masses
        fscanf(init_file, "%lf %lf %lf %lf %lf %lf %lf", 
        &mass, &x, &y, &z, &vx, &vy, &vz);
        our_system.createCelestialBody(
            vec3(x, y, z),
            vec3(vx*M_PI, vy*M_PI, vz*M_PI), 
            mass);
    }
    fclose(init_file);  //close file with initial conditions
    std::vector<CelestialBody> &bodies = our_system.bodies();
    for(int i = 0; i<num_bodies; i++) {
        CelestialBody &body = bodies[i]; // Reference to this body
        std::cout << "The position of this object is " << body.position << " with velocity " << body.velocity << std::endl;
    }
}
