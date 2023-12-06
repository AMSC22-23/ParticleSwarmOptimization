#include <iostream>
#include <limits>
#include <random>
#include <fstream>
#include "PSO.hpp"


void PSO_serial::pso(std::function<double(const std::vector<double>&)> objective_function,

        const std::vector<std::pair<double,double>> &bounds, int num_particles, int max_ter,

        const double inertiaWeight, const double c1, const double c2) 
    {

 

    // Main loop
    for (int iter = 0; iter < max_iter; ++iter) {
        int particle_count = 0;

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
            particle_count++;
        }
        global_best_sol_history.push_back(global_best_sol);
        global_best_positions_history.push_back(global_best_position);
    }
}