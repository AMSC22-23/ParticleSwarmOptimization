#include <iostream>
#include <limits>
#include <random>
#include <fstream>
#include "PSO.hpp"


void PSO_serial::pso(std::function<double(const std::vector<double>&)> objective_function,
        const std::vector<std::pair<double,double>> &bounds, int num_particles, int max_iter) 
    {
    //PSO PARAMS
    const double ciw = 0.5;      //Constant inertia weight
    const double c1 = 2.0;       //Acceleration constants
    const double c2 = 2.0;

    std::vector<Particle> swarm;                                      // Initialize Swarm

    const int dimensions = bounds.size();
    int best_particle_index = 0;
    for (int i = 0; i < num_particles; ++i) {
        swarm.push_back(Particle(dimensions, bounds));                // Initialize particles
        swarm[i].value = objective_function(swarm[i].position);       // Initilize value of each particle
        swarm[i].best_sol = swarm[i].value;                           // Initialize best sol of each particle
        if (swarm[i].value < swarm[best_particle_index].value) {
            best_particle_index = i;
        }
    }

    std::vector<double> global_best_position = swarm[best_particle_index].position;   // Initialize global best position
    double global_best_sol = objective_function(global_best_position);// Initialize global best solution

    // Main loop
    for (int iter = 0; iter < max_iter; ++iter) {
/*  
        std::cout << "---------------------------------------------------------------------------------" << std::endl;
        std::cout << "It: " << iter << "    GBP: ("<< global_best_position[0]  <<","<<  global_best_position[1] << ")"<<std::endl;
        std::cout << "GBV: " << global_best_sol << std::endl;
 */
        int particle_count = 0; // Particle counter

        for (auto& particle : swarm) {

            // Update velocity & position
            for (int i = 0; i < dimensions; ++i) {

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);
                std::vector<double> r1 = {dis(gen), dis(gen)};
                std::vector<double> r2 = {dis(gen), dis(gen)};

                // v(t+1) = ciw * v(t) + c1 * r1 * (local_best - x(t)) + c2 * r2 * (global_best - x(t))
                particle.velocity[i] = ciw * particle.velocity[i] 
                                        + c1 * r1[i] * (particle.best_position[i] - particle.position[i])
                                        + c2 * r2[i] * (global_best_position[i] - particle.position[i]);
                
                particle.position[i] += particle.velocity[i];
            }
            particle.value = objective_function(particle.position);

            // Update local best
            if (particle.value < particle.best_sol) {
                particle.best_sol = particle.value;
                particle.best_position = particle.position;
            }

            // Update global best position and solution
            if (particle.best_sol < global_best_sol) {
                global_best_position = particle.position;
                global_best_sol = particle.value;
            }

            //Write particle's position in the corresponding CSV
            // Comment out for accurate time profiling
            std::string filename = "../data/particle_" + std::to_string(particle_count) + "_pos.csv";
            std::ofstream file(filename, std::ios_base::app);
            for (auto& pos: particle.position) { file << pos << ",";}
            file << particle.value;
            file << std::endl;

            particle_count++;
        }
    }
    // Output the result
    std::cout << "-------------------------Solution-------------------------" << std::endl;
    std::cout << "Best Value     : " << global_best_sol << std::endl;
    std::cout << "Best Position  : ";
    for (auto& val: global_best_position) { std::cout << val << " ";}
    std::cout << std::endl;
}