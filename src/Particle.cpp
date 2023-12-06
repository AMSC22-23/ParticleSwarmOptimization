/*
#include <random>
#include <limits>
#include <vector>
#include "Particle.hpp"

Particle::Particle(int dimensions, const std::vector<std::pair<double, double>>& bounds) {
    // Marsenne Twister nb generator w/ random seed generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < dimensions; ++i) {
        std::uniform_real_distribution<> dis_pos(bounds[i].first, bounds[i].second);
        std::uniform_real_distribution<> dis_vel(bounds[i].first, bounds[i].second);        
        position.push_back(dis_pos(gen));
        velocity.push_back(dis_vel(gen));
        value = 0.0;
        best_sol = 0.0;
    }
    best_position = position;
}
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <stdexcept>

#include "Particle.hpp"


/*

FIXES NEEDED : CONDITIONS & CHECKING STUFF FOR EXAMPLE FITNESS SETTER EXTC....

.................................................................................

NEED TO BE ADDED : SOME TO_STRING FUNCTION THAT RETURNS A STRING WITH ALL THE VALUES OF THE PARTICLE... ( MAYBE 1 DIMENSION...)


*/
using namespace std;

// Constructor to initialize with dynamic arrays
Particle::Particle(int dimensions) : dimensions(dimensions) {
    x = new double[dimensions];
    v = new double[dimensions];
    x_best = new double[dimensions];
}

// Destructor to free the allocated memory
Particle::~Particle() {
    delete[] x;
    delete[] v;
    delete[] x_best;
}


//Setter methods to access individual elements at specific indices
void Particle::setPositionAtIndex(int index, double value){
    if (index >= 0 && index < dimensions) {
        x[index] = value;
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

void Particle::setVelocityAtIndex(int index, double value){
    if (index >= 0 && index < dimensions) {
        v[index] = value;
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

void Particle::setBestPositionAtIndex(int index, double value){
    if(index >= 0 && index < dimensions){
        x_best[index] = value;
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

void Particle::setFitness(double fitnessVal) {
    fitness = fitnessVal;
}
void Particle::setBestFitness(double bestfitnessVal) {
    bestfitness = bestfitnessVal;
}

// Getter methods to access individual elements at specific indices

double Particle::getPosAtIndex(int index) const {
    if(index >= 0 && index < dimensions){
        return x[index];
    }
    else {
        return 0.0;
    }
}

double Particle::getVelocityAtIndex(int index) const {
    if(index >= 0 && index < dimensions){
        return v[index];
    }
    else {
        return 0.0;
    }
}


double Particle::getBestPosAtIndex(int index) const {
    if(index >= 0 && index < dimensions){
        return x_best[index];
    }
    else {
        return 0.0;
    }
}

double Particle::getFitness(){
    return fitness;
}

double Particle::getBestFitness(){
    return bestfitness;
}

double * Particle::getPosition(){
    return x;
}

double * Particle::getBestPosition(){
    return x_best;
}

