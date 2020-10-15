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
    double *x, *y, *z, *vx, *vy, *vz; // To store initial conditions for each planet.
    double *mass;                     // Store mass of planets.
    double dt;                        // Time between each step
    int N;                            // Number of integration points
    if (argc < 3) {
        std::cout << "Please include input and output file" << std::endl;
    }
    else {
        output_file = "../output/";
        input_file = "../input/";
        input_file.append(argv[1]);
        output_file.append(argv[2]).append(".cvs");
    }

    const char* input_file_char = input_file.c_str();
    FILE *init_file = fopen(input_file_char, "r"); //open file with initial conditions
    fscanf(init_file, "%i %lf %i", &num_bodies, &dt, &N);
    x = new double[num_bodies];
    y = new double[num_bodies];
    z = new double[num_bodies];
    vx = new double[num_bodies];
    vy = new double[num_bodies];
    vz = new double[num_bodies];
    mass = new double[num_bodies];
    for (int i = 0; i < num_bodies; i++) {
        fscanf(init_file, "%lf %lf %lf %lf %lf %lf %lf", 
        &mass[i], &x[i], &y[i], &z[i], &vx[i], &vy[i], &vz[i]);
    }
    fclose(init_file);


    SolarSystem our_system;
    for (int i = 0; i<num_bodies; i++){
      our_system.createCelestialBody(
          vec3(x[i], x[i], x[i]),
          vec3(vx[i]*M_PI, vy[i]*M_PI, vz[i]*M_PI),
          mass[i]);
    }


}
