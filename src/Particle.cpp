#include "Particle.hpp"
#include <random>
#include <functional>

using namespace std;

Particle::Particle(int dimensions,uniform_real_distribution<> dis, mt19937 gen, function<double(double*, int)> objective_function) : dimensions(dimensions) {
    position = new double[dimensions];
    velocity = new double[dimensions];
    best_position = new double[dimensions];

    for(int j = 0 ; j < dimensions; j++){
            position[j] = dis(gen);
            velocity[j] = dis(gen);
            best_position[j] = position[j];

        }
        value = objective_function(position, dimensions);
        best_value = value;
}

Particle::~Particle() {
    delete[] position;
    delete[] velocity;
    delete[] best_position;
}

void Particle::updateVelocityAndPosition(double inertiaWeight,double c1,double c2,const Particle& global_best_particle) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < dimensions; ++i) {
        double r1 = dis(gen);
        double r2 = dis(gen);

        // v(t+1) = inertiaWeight * v(t) + c1 * r1 * (local_best - x(t)) + c2 * r2 * (global_best - x(t))
        velocity[i] = inertiaWeight * velocity[i]
                        + c1 * r1 * (best_position[i] - position[i])
                        + c2 * r2 * (global_best_particle.best_position[i] - position[i]);
        position[i] += velocity[i];
    }
} 

void Particle::updateLocalBest(function<double(double*, int)> objective_function) {
    value = objective_function(position, dimensions);
    if (value < best_value) {
        best_value = value;
        for (int i = 0; i < dimensions; ++i) {
            best_position[i] = position[i];
        }
    }
}
