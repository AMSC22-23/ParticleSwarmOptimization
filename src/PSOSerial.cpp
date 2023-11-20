#include <iostream>
#include <limits>
#include "PSO.hpp"

void PSO_serial::pso(std::function<double(const std::vector<double>&)> objective_function,
        const std::vector<std::pair<double,double>> &bounds, int num_particles, int max_iter) 
    {
    int dimensions = bounds.size();
    std::vector<Particle> swarm;

    // Initialize particles
    for (int i = 0; i < num_particles; ++i) {
        swarm.emplace_back(dimensions, bounds);
    }

    // Initialize global best at infinity
    double global_best_sol = std::numeric_limits<double>::infinity();
    std::vector<double> global_best_position(dimensions);

    // Main loop
    for (int iter = 0; iter < max_iter; ++iter) {
        for (auto& particle : swarm) {
            double value = objective_function(particle.position);

            // Update local best
            if (value < particle.best_sol) {
                particle.best_sol = value;
                particle.best_position = particle.position;
            }

            // Update global best
            if (value < global_best_sol) {
                global_best_sol = value;
                global_best_position = particle.position;
            }
        }
    }
    // Output the result
    std::cout << "Best Value: " << global_best_sol << std::endl;
    std::cout << "Best Position: ";
    for (auto& val : global_best_position) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}