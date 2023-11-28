#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "particle.hpp"


/*

FIXES NEEDED : CONDITIONS & CHECKING STUFF FOR EXAMPLE FITNESS SETTER EXTC....

.................................................................................

NEED TO BE ADDED : SOME TO_STRING FUNCTION THAT RETURNS A STRING WITH ALL THE VALUES OF THE PARTICLE... ( MAYBE 1 DIMENSION...)


*/
using namespace std;

    Particle::Particle(vector<double> x, vector<double> v, vector<double> x_best, vector<double> x_best_global,
     double fitness, double bestfitness, double bestfitness_global){

        // Parameterized constructor
        setPosition(x);
        setVelocity(v);
        setBestPosition(x_best);
        setBestGlobalPosition(x_best_global);
        setFitness(fitness);
        setBestFitness(bestfitness);
        setBestGlobalFitness(bestfitness_global);
    }

    // Setter methods

    void Particle::setPosition(const std::vector<double>& position) {
    x = position;
    }

    void Particle::setVelocity(const std::vector<double>& velocity) {
        v = velocity;
    }

    void Particle::setBestPosition(const std::vector<double>& bestposition) {
        x_best = bestposition;
    }

    void Particle::setBestGlobalPosition(const std::vector<double>& bestglobalposition){
        x_best_global = bestglobalposition;
    }
 
    void Particle::setFitness(double fitnessVal) {
        fitness = fitnessVal;
    }
    void Particle::setBestFitness(double bestfitnessVal) {
        bestfitness = bestfitnessVal;
    }

    void Particle::setBestGlobalFitness(double bestfitness_globalVal) {
        bestfitness_global = bestfitness_globalVal;
    }

    // Getter methods

    const vector<double>& Particle::getPosition() const {
        return x;
    }

    const vector<double>& Particle::getVelocity() const {
        return v;
    }

    const vector<double>& Particle::getBestPosition() const {
        return x_best;
    }

    const vector<double>& Particle::getBestGlobalPosition() const {
        return x_best_global;
    }


    double Particle::getFitness() {
        return fitness;
    }

    double Particle::getBestFitness() {
        return bestfitness;
    }

    double Particle::getBestGlobalFitness() {
        return bestfitness_global;
    }

    double Particle::getPosAtIndex(int index) const {
    if (index >= 0 && index < x.size()) {
        return x[index];
    } else {
        return 0.0;
    }
    }

    double Particle::getVelocityAtIndex(int index) const {
        if (index >= 0 && index < v.size()) {
            return v[index];
        } else {
            return 0.0;
        }
    }

    double Particle::getBestPosAtIndex(int index) const {
        if (index >= 0 && index < x_best.size()) {
            return x_best[index];
        } else {
            return 0.0;
        }
    }

    double Particle::getBestGlobalPosAtIndex(int index) const {
        if (index >= 0 && index < x_best_global.size()) {
            return x_best_global[index];
        } else {
            return 0.0;
        }
    }

/*
    string Particle::toString() {
        string s = "";
        s += "x: " + to_string(var[0]) + " y: " + to_string(var[1]) + 
        " vx: " + to_string(velocity[0]) + " vy: " + to_string(velocity[1]) + 
        " fitness: " + to_string(fitness) + " bestX: " + to_string(bestvar[0]) +
         " bestY: " + to_string(bestvar[1]) + 
         " bestFitness: " + (string)getBestFitness();
         return s;
    }

*/
