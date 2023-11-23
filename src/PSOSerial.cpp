#include <iostream>
#include <limits>
#include <random>
#include <fstream>
#include "PSO.hpp"

void PSO_serial::pso(std::function<double(const std::vector<double>&)> objective_function,
        const std::vector<std::pair<double,double>> &bounds, int num_particles, int max_iter) 
    {

    std::random_device rd;
    std::mt19937 gen(rd());

    int dimensions = bounds.size();
    std::vector<Particle> swarm;

    //Constant inertia weight
    const double ciw = 0.5;
    //Acceleration constants
    const double c1 = 2.0;
    const double c2 = 2.0;

    // Initialize particles
    for (int i = 0; i < num_particles; ++i) {
        swarm.emplace_back(dimensions, bounds);
    }

    // Initialize global best at infinity
    double global_best_sol = std::numeric_limits<double>::infinity();
    std::vector<double> global_best_position(dimensions);

    // Main loop
    for (int iter = 0; iter < max_iter; ++iter) {

        //Counter of particles
        int particle_count = 0;

        for (auto& particle : swarm) {
            double value = objective_function(particle.position);

            // Update velocity
            // v(t+1) = ciw * v(t) + c1 * r1 * (local_best - x(t)) + c2 * r2 * (global_best - x(t))
            for (int i = 0; i < dimensions; ++i) {
                std::uniform_real_distribution<> dis(0, 1);
                double r1 = dis(gen);
                double r2 = dis(gen);
                particle.velocity[i] = ciw * particle.velocity[i] + c1 * r1 * (particle.best_position[i] - particle.position[i]) + c2 * r2 * (global_best_position[i] - particle.position[i]);
                //                     \________________________/    \_________________________________________________________/  \_________________________________________________________/ 
                //                                |                                           |                                                           |
                //                          Velocity update                               Local best update                                          Global best update
                //                         (inertia component)                          (cognitive component)                                        (social component)
            }

            // Update position 
            // x(t+1) = x(t) + v(t+1)
            //(TODO: add velocity clamping/constriction coefficient methods)
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

            //Write particle's position in the corresponding CSV
            // Comment out for accurate time profiling
            std::string filename = "../data/particle_" + std::to_string(particle_count) + "_pos.csv";
            std::ofstream file(filename, std::ios_base::app);
            for (auto& pos: particle.position) { file << pos << ",";}
            file << value;
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