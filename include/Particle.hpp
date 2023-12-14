#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <functional>
#include <random>

using namespace std;

class Particle {
public:
    //Constructor
    Particle() = default;
    Particle(int dimensions,uniform_real_distribution<> dis, mt19937 gen, function<double(double*, int)> objective_function);
    ~Particle();

    double value;          // value of particle at current position given a function
    double best_value;     // best value of particle given a function

    virtual void updateVelocityAndPosition(double inertiaWeight,double c1,double c2,const Particle& global_best_position);
    virtual void updateLocalBest(function<double(double*, int)> objective_function);

private: 
    int dimensions;        // dim of problem
    double* position;      // position of particle
    double* velocity;      // velocity of particle
    double* best_position; // best position of particle
/* 
    // Destructor
    ~Particle() {
        delete[] position;
        delete[] velocity;
        delete[] best_position;
    }

    // Copy constructor 
    Particle(const Particle& other) : dimensions(other.dimensions) {
        position = new double[dimensions];
        velocity = new double[dimensions];
        best_position = new double[dimensions];
        std::copy(other.position, other.position + dimensions, position);
        std::copy(other.velocity, other.velocity + dimensions, velocity);
        std::copy(other.best_position, other.best_position + dimensions, best_position);
        value = other.value;
    }

    // Copy operator
    Particle& operator=(const Particle& other) {
        if (this != &other) {
            delete[] position;
            delete[] velocity;
            delete[] best_position;

            dimensions = other.dimensions;
            position = new double[dimensions];
            velocity = new double[dimensions];
            best_position = new double[dimensions];
            std::copy(other.position, other.position + dimensions, position);
            std::copy(other.velocity, other.velocity + dimensions, velocity);
            std::copy(other.best_position, other.best_position + dimensions, best_position);
            value = other.value;
        }
        return *this;
    } 
*/

};
#endif