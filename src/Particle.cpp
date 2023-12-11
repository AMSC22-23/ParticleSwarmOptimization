#include <vector>
#include <stdexcept>

#include "Particle.hpp"

using namespace std;

/* Constructor */
Particle::Particle(int dimensions) : dimensions(dimensions) {
    position = new double[dimensions];
    velocity = new double[dimensions];
    best_position = new double[dimensions];
}

/* Destructor */ 
Particle::~Particle() {
    delete[] position;
    delete[] velocity;
    delete[] best_position;
}

/* Setter methods */
void Particle::setPosition(int index, double val){
    if (index >= 0 && index < dimensions) {
        position[index] = val;
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

void Particle::setVelocity(int index, double val){
    if (index >= 0 && index < dimensions) {
        velocity[index] = val;
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

void Particle::setBestPosition(int index, double val){
    if(index >= 0 && index < dimensions){
        best_position[index] = val;
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

void Particle::setValue(double newVal) {
    value = newVal;
}
void Particle::setBestValue(double newVal) {
    best_value = newVal;
}

/* Getter methods */
double Particle::getSinglePosition(int index) const {
    if(index >= 0 && index < dimensions){
        return position[index];
    }
    else {
        return 0.0;
    }
}

double Particle::getVelocity(int index) const {
    if(index >= 0 && index < dimensions){
        return velocity[index];
    }
    else {
        return 0.0;
    }
}

double Particle::getBestPos(int index) const {
    if(index >= 0 && index < dimensions){
        return best_position[index];
    }
    else {
        return 0.0;
    }
}

double Particle::getValue(){
    return value;
}

double Particle::getBestValue(){
    return best_value;
}

double * Particle::getPosition(){
    double * copy = new double[dimensions];
    std::copy(position, position + dimensions, copy);
    return copy;}

double * Particle::getBestPosition(){
    return best_position;
}