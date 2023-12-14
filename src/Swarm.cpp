#include "Swarm.hpp"
#include "ObjectiveFunction.hpp"
#include <limits>
#include <random>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

/*Constructor*/
Swarm::Swarm(int num_particles, int dimensions,string objective_function_name):dimensions(dimensions) {
    const pair<double, double>* bounds = ObjectiveFunction::get_bounds(objective_function_name, dimensions);
    function<double(double*, int)>  objective_function = ObjectiveFunction::get_objective_function(objective_function_name);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(bounds[0].first, bounds[0].second);

    int best_index = 0;
    for (int i = 0; i < num_particles; i++) {  
        particles.emplace_back(Particle(dimensions,dis,gen,objective_function));

        /* Init position, velocity & best position for each dimension */
        if(particles.back().value < particles[best_index].value){
            best_index = i;
        }
    }
    global_best_particle = particles[best_index];         

    particles.shrink_to_fit();
    delete[] bounds;
}

/*Destructor*/
Swarm::~Swarm() {
    particles.clear();
}

void Swarm::updateParticles() {
    for (Particle& particle : particles) {
        particle.updateVelocityAndPosition(inertiaWeight, c1, c2, global_best_particle);
        particle.updateLocalBest(objective_function);
    }
}

void Swarm::updateGlobalBestParticle() {
    for (const Particle& particle : particles) {
        if (particle.best_value < global_best_particle.value) {
            global_best_particle = particle;
        }
    }
}
