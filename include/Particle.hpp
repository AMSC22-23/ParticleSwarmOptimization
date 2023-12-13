#ifndef PARTICLE_HPP
#define PARTICLE_HPP

using namespace std;

class Particle {
public:
    int dimensions;        // dim of problem
    double* position;      // position of particle
    double* velocity;      // velocity of particle
    double* best_position; // best position of particle
    double value;          // value of particle at current position 
    double best_value;     // best value of particle given a function

    /* Constructor */
    Particle(int dimensions) : dimensions(dimensions) {
        position = new double[dimensions];
        velocity = new double[dimensions];
        best_position = new double[dimensions];
    }

    /* Copy constructor */
    Particle(const Particle& other) : dimensions(other.dimensions) {
        position = new double[dimensions];
        velocity = new double[dimensions];
        best_position = new double[dimensions];
        copy(other.position, other.position + dimensions, position);
        copy(other.velocity, other.velocity + dimensions, velocity);
        copy(other.best_position, other.best_position + dimensions, best_position);
        value = other.value;
        best_value = other.best_value;
    }

    /* Copy operator */
    Particle& operator=(const Particle& other) {
        if (this != &other) {
            delete[] position;
            delete[] velocity;
            delete[] best_position;

            dimensions = other.dimensions;
            position = new double[dimensions];
            velocity = new double[dimensions];
            best_position = new double[dimensions];
            copy(other.position, other.position + dimensions, position);
            copy(other.velocity, other.velocity + dimensions, velocity);
            copy(other.best_position, other.best_position + dimensions, best_position);
            value = other.value;
            best_value = other.best_value;
        }
        return *this;
    }

    /* Destructor */ 
    ~Particle() {
        delete[] position;
        delete[] velocity;
        delete[] best_position;
    }
};
#endif