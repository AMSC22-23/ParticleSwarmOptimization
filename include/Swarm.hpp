#ifndef SWARM_HPP
#define SWARM_HPP

#include <vector>
#include <string>
#include "Particle.hpp"

using namespace std;

class Swarm {
public:
    Swarm(int num_particles, int dimensions, string objective_function_name);
    ~Swarm();
    void updateParticles();
    void updateGlobalBestParticle();

    double inertiaWeight;
    double c1;
    double c2;
    int dimensions;
    function<double(double*, int)> objective_function;
    Particle global_best_particle;

private:
    vector<Particle> particles;
};

#endif