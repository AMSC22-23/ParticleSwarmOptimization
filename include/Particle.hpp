#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

#ifndef PARTICLE_HPP_


#define PARTICLE_HPP_

class Particle {

private:
    // Private member variables

    // Dimension of the particle.
    int dimensions;

    // Position array :
    double* x;
    // Velocity array :
    double* v;
    // Best position array :
    double* x_best;

    // Fitness value for optimization :
    double fitness;
    // Best fitness value for optimization :
    double bestfitness;

public:

    // Constructor to initialize with dynamic arrays
    Particle(int dimensions);

    // Destructor to free the allocated memory
    ~Particle();

    //Setter methods to access individual elements at specific indices
    void setPositionAtIndex(int index, double value);

    void setVelocityAtIndex(int index, double value);

    void setBestPositionAtIndex(int index, double value);

    void setFitness(double fitnessVal);

    void setBestFitness(double bestfitnessVal);

    // Getter methods to access individual elements at specific indices

    double getPosAtIndex(int index) const;

    double getVelocityAtIndex(int index) const;

    double getBestPosAtIndex(int index) const;

    double getFitness();

    double getBestFitness();

    double * getPosition();

    double * getBestPosition();
};


#endif // !PARTICLE_HPP_

