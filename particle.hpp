#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

#ifndef PARTICLE_HPP_



#define PARTICLE_HPP_

class Particle {

public:
    // Public members are accessible from anywhere
    
    // Position vector :
    vector<double> x;
    // Velocity vector :
    vector<double> v;
    // Best position vector :
    vector<double> x_best;
    // Best global position vector :
    vector<double> x_best_global;
    // Fitness value for optimization :
    double fitness;
    // Best fitness value for optimization :
    double bestfitness;
    // Best global fitness value for optimization :
    double bestfitness_global;


    Particle(vector<double> x, vector<double> v, vector<double> x_best, vector<double> x_best_global,
     double fitness, double bestfitness, double bestfitness_global);

    // Setter methods

    void setPosition(const std::vector<double>& position);

    void setVelocity(const std::vector<double>& velocity);

    void setBestPosition(const std::vector<double>& bestposition);
 
    void setBestGlobalPosition(const std::vector<double>& bestglobalposition);

    void setFitness(double fitnessVal);

    void setBestFitness(double bestfitnessVal);

    void setBestGlobalFitness(double bestfitness_globalVal);

    // Getter methods

    const vector<double>& getPosition() const;

    const vector<double>& getVelocity() const;

    const vector<double>& getBestPosition() const;

    const vector<double>& getBestGlobalPosition() const;

    double getFitness();

    double getBestFitness();

    double getBestGlobalFitness();

    // Getter methods to access individual elements at specific indices

    double getPosAtIndex(int index) const;

    double getVelocityAtIndex(int index) const;

    double getBestPosAtIndex(int index) const;

    double getBestGlobalPosAtIndex(int index) const;

};

#endif // !PARTICLE_HPP_


