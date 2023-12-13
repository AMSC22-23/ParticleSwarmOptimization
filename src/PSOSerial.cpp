#include <random>
#include <iterator>
#include <iostream>
#include "PSO.hpp"

using namespace std;

void PSO_serial::pso(double (*ObjFuncPtr)(double*, int),
            const int dimensions,
            const pair<double, double>* bounds,
            vector<Particle> &swarm,
            int num_particles,
            int max_iter,
            double inertiaWeight,
            double c1,
            double c2) 
    {
    // Main loop
    double previous_max_distance = 0.0;
    for (int iter = 0; iter < max_iter; ++iter) {
        cout << "\n----------------------------Iter " << iter << "-----------------------------" << endl;
        double adaptiveInertiaWeight = inertiaWeight;
        //double sum_local_best = 0.0;
        double max_distance = 0.0;

        for (auto& particle : swarm) {
            particle.value = ObjFuncPtr(particle.position, dimensions);
            //cout<<"Particle value: "<<particle.value<<endl;

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
                adaptiveInertiaWeight = w_rand * (1 - distance / previous_max_distance);
            } else {
                adaptiveInertiaWeight = w_rand;
            }

            // Update velocity & position
            for (int i = 0; i < dimensions; ++i) {

                random_device rd;
                mt19937 gen(rd());
                normal_distribution<> dis(0.0, 1.0);
                vector<double> r1;
                vector<double> r2;

                for (int d = 0; d < dimensions; ++d) {
                    r1.emplace_back(dis(gen));
                    r2.emplace_back(dis(gen));
                }

                // v(t+1) = inertiaWeight * v(t) + c1 * r1 * (local_best - x(t)) + c2 * r2 * (global_best - x(t))
                particle.velocity[i] = adaptiveInertiaWeight * particle.velocity[i]
                                        + c1 * r1[i] * (particle.best_position[i] - particle.position[i])
                                        + c2 * r2[i] * (global_best_position[i] - particle.position[i]);

                // Velocity clamping at 20% of the search space
                double max_velocity = 0.2 * (bounds[i].second - bounds[i].first);
                if (particle.velocity[i] > max_velocity) {
                    particle.velocity[i] = max_velocity;
                } else if (particle.velocity[i] < -max_velocity) {
                    particle.velocity[i] = -max_velocity;
                }
                particle.position[i] += particle.velocity[i];

                // Check bounds
                if (particle.position[i] > bounds[i].second) {
                    particle.position[i] = bounds[i].second;
                } else if (particle.position[i] < bounds[i].first) {
                    particle.position[i] = bounds[i].first;
                }
            }

            // Update local best
            if (particle.value < particle.best_value) {
                particle.best_value = particle.value;
                copy(particle.position, particle.position + dimensions, particle.best_position);
            }
            //sum_local_best += particle.best_value;

            // Update global best position and solution
            if (particle.best_value < global_best_sol) {
                copy(particle.position, particle.position + dimensions, global_best_position);
                global_best_sol = particle.best_value;
            }
        }

        //Update inertia weight given distance 
        //sum_local_best /= num_particles;
        //adaptiveAvgInertia = 1.1-(global_best_sol/(num_particles * sum_local_best));

        global_best_sol_history[iter] = global_best_sol;
        copy(global_best_position, global_best_position + dimensions, global_best_positions_history[iter]);

    cout << "Global best solution: " << global_best_sol << endl;
    cout << "Inertia Weight: " << adaptiveInertiaWeight << endl;
    }
}