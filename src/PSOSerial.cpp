#include <iostream>
#include <limits>
#include <random>
#include <fstream>
#include "PSO.hpp"

void PSO_serial::pso(function<double(double*, int)> objective_function,
            const int dimensions,
            vector<Particle> &swarm,
            int max_iter,
            double inertiaWeight,
            const double c1,
            const double c2) 
    {

/*v----------------------------------------------------------------------------------------------*/
double previous_max_distance = 0.0;
/*^----------------------------------------------------------------------------------------------*/

    // Main loop
    for (int iter = 0; iter < max_iter; ++iter) {

/*v---------------------------------------------------------------------------------------------*/
    double max_distance = 0.0;
/*^----------------------------------------------------------------------------------------------*/

        for (auto& particle : swarm) {

/*v----------------------------------------------------------------------------------------------*/
            // Compute euclidian dist to global best
            double distance = 0.0;
            for (int j = 0; j < dimensions; ++j) {
                distance += pow(particle.position[j] - global_best_position[j], 2);
            }
            distance = sqrt(distance);

            // Update the maximum distance
            if (distance > max_distance) {
                max_distance = distance;
            }
            //cout<<"Distance: "<<distance<<endl;
            //cout<<"Max Distance: "<<max_distance<<endl;
            // Calculate the adaptive inertia weight
            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0.5, 1.0);
            double w_rand = dis(gen);
            if (previous_max_distance != 0) {
                inertiaWeight = w_rand * (1 - distance / previous_max_distance);
            } else {
                inertiaWeight = w_rand;
            }
/*^----------------------------------------------------------------------------------------------*/


            // Update velocity & position
            for (int i = 0; i < dimensions; ++i) {

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);

                double r1 = dis(gen);
                double r2 = dis(gen);

                // v(t+1) = inertiaWeight * v(t) + c1 * r1 * (local_best - x(t)) + c2 * r2 * (global_best - x(t))
                particle.velocity[i] = inertiaWeight * particle.velocity[i]
                                        + c1 * r1 * (particle.best_position[i] - particle.position[i])
                                        + c2 * r2 * (global_best_position[i] - particle.position[i]);

                particle.position[i] += particle.velocity[i];

            }
            particle.value = objective_function(particle.position, dimensions);

            // Update local best
            if (particle.value < particle.best_value) {
                particle.best_value = particle.value;
                copy(particle.position, particle.position + dimensions, particle.best_position);

            }

            // Update global best position and solution
            if (particle.best_value < global_best_sol) {
                copy(particle.position, particle.position + dimensions, global_best_position);
                global_best_sol = particle.value;
            }
        }
        global_best_sol_history[iter] = global_best_sol;
        copy(global_best_position, global_best_position + dimensions, global_best_positions_history[iter]);
    }
}