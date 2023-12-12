#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class Particle {
public:
    int dimensions;        // dim of problem
    double* position;      // position of particle
    double* velocity;      // velocity of particle
    double* best_position; // best position of particle
    double value;          // value of particle at current position given a function
    double best_value;     // best value of particle given a function

    /* Constructor */
    Particle(int dimensions) : dimensions(dimensions) {
        position = new double[dimensions];
        velocity = new double[dimensions];
        best_position = new double[dimensions];
    }

    /* Destructor */ 
    ~Particle() {
        delete[] position;
        delete[] velocity;
        delete[] best_position;
    }
};
#endif