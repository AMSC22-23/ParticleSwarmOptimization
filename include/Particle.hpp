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

    Particle(int dimensions); // Constructor 
    ~Particle();              // Destructor

    /* Setter methods */
    void setPosition(int index, double val);
    void setVelocity(int index, double val);
    void setBestPosition(int index, double val);
    void setValue(double value);
    void setBestValue(double best_value);

    /* Getter methods */
    double getSinglePosition(int index) const;
    double getVelocity(int index) const;
    double getBestPos(int index) const;
    double getValue();
    double getBestValue();
    double * getPosition();
    double * getBestPosition();
};
#endif