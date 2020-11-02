#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include "euler.hpp"
#include "verlet.hpp"
#include "solarsystem.hpp"

// test the final precession of Mercury
void testPrecession(vec3* last_positions, int bonus_steps);

int main(int argc, char* argv[]) {
    std::string input_file, output_file, solver_method;

    double dt, distDependence;  // Time between each step and parameter beta
    int N, print_step;          // Number of integration points
    bool shouldPrint;
    // double tol_angular = 1e-2;  // Tolerance on angular momentum conservation
    // double tol_energy = 1e-3;   // Tolerance on energy conservation

    if (argc < 6) {
        std::cout << "Please include input file, dt, number of time steps, "
            << "solver method and distance dependence parameter beta"
            << std::endl;
        exit(1);
    } else {
        // Store input, dt, N, solver_method and distDependence
        input_file = "../input/";
        output_file = "../output/positions/";
        input_file.append(argv[1]).append(".txt");
        dt = std::pow(10, -1*std::atof(argv[2]));
        N = std::pow(10, std::atoi(argv[3]));
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
    // our_system.remove_cm_velocity();
    std::cout << std::endl << "Vel. and pos. of center of mass subtracted:";
    our_system.printSystem();
    our_system.calculateEnergyAndAngularMomentum();

    // Solve!
    if (solver_method == "euler") {
        auto start = std::chrono::high_resolution_clock::now();
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
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Duration of solve: " << duration.count() << " microseconds" << std::endl;
    } else if (solver_method == "verlet") {
        auto start = std::chrono::high_resolution_clock::now();
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
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Duration of solve: " << duration.count() << " microseconds" << std::endl;
    } else if (solver_method == "escape") {
        Verlet solver(dt, our_system);
        double dv = 0.01;
        double tol_pot_energy = 1e-4;
        double tol_v = sqrt(8*M_PI*M_PI*tol_pot_energy);
        double v0, pot_energy;
        double analytic = 2*sqrt(2)*M_PI;
        CelestialBody& sun = our_system.bodies()[0];
        CelestialBody& earth = our_system.bodies()[1];
        v0 = earth.velocity[0];
        while (true) {
            our_system.calculateForces();
            while (earth.velocity[0] > tol_v) {
                solver.integrateOneStep1();
                our_system.calculateForces();
                solver.integrateOneStep2();
                pot_energy = 1/earth.position.length();
                if (pot_energy < tol_pot_energy) {
                    std::cout
                        << "Computed escape velocity: "
                        << v0 << " AU/yr" << std::endl
                        << "Analytic escape velocity: "
                        << analytic << " AU/yr" << std::endl;
                    exit(0);
                }
            }
            v0 += dv;
            // our_system.read_initial_conditions(input_file);
            sun.position[0] = 0;
            sun.velocity[0] = 0;
            earth.position[0] = 1;
            earth.velocity[0] = v0;
            // our_system.printSystem();
            std::cout << "Testing for initial velocity: " << v0 << std::endl;
        }
    } else if (solver_method == "mercury") {
        our_system.writeToFile(output_file);
        Verlet solver(dt, our_system);
        our_system.calculateMercForces();
        int bonus_steps = int(N/400);
        vec3* last_positions = new vec3[bonus_steps];
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
        CelestialBody& mercury = our_system.bodies()[1];
        for (int timestep=0; timestep<bonus_steps; timestep++) {
            solver.integrateOneStep1();
            our_system.calculateMercForces();
            solver.integrateOneStep2();
            last_positions[timestep] = mercury.position;
        }
        testPrecession(last_positions, bonus_steps);
        delete[] last_positions;
    } else {
        std::cout << "Unknown method " << solver_method << std::endl;
        exit(1);
    }

    return 0;
}

void testPrecession(vec3* last_positions, int bonus_steps) {
    double precession_ana = 43; // arcseconds
    vec3 perihelion_position = last_positions[0];
    double r_peri = perihelion_position.length();
    for (int i = 1; i<bonus_steps; i++) {
        double r1 = last_positions[i].length();
        if (r1 < r_peri) {
            perihelion_position = last_positions[i];
            r_peri = perihelion_position.length();
        }
    }
    double precession_calc = std::atan(perihelion_position[1]/perihelion_position[0]);
    precession_calc /= 4.848e-6;
    std::cout << "calculated: " << precession_calc
        << "  expected: " << precession_ana << std::endl;
}
