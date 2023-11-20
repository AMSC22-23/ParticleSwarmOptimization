#include <iostream>
#include <limits>
#include <random>
#include "PSO.hpp"

void PSO_serial::pso(std::function<double(const std::vector<double>&)> objective_function,
        const std::vector<std::pair<double,double>> &bounds, int num_particles, int max_iter) 
    {

    std::random_device rd;
    std::mt19937 gen(rd());

    int dimensions = bounds.size();
    std::vector<Particle> swarm;

    //Constant inertia weight
    double ciw = 0.5;
    //Acceleration constants
    double acceleration1 = 2.0;
    double acceleration2 = 2.0;

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

            // Update velocity
            for (int i = 0; i < dimensions; ++i) {
                std::uniform_real_distribution<> dis(0, 1);
                double r1 = dis(gen);
                double r2 = dis(gen);
                particle.velocity[i] = ciw * particle.velocity[i] + acceleration1 * r1 * (particle.best_position[i] - particle.position[i]) + acceleration2 * r2 * (global_best_position[i] - particle.position[i]);
            }

            // Update position
            for (int i = 0; i < dimensions; ++i) {
                particle.position[i] += particle.velocity[i];
                if (particle.position[i] < bounds[i].first) {
                    particle.position[i] = bounds[i].first;
                }
                if (particle.position[i] > bounds[i].second) {
                    particle.position[i] = bounds[i].second;
                }
            }

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
    for (auto& val: global_best_position) { std::cout << val << " ";}
    std::cout << std::endl;
}