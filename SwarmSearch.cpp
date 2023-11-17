#include "SwarmSearch.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>

// Implementation of Particle class
Particle::Particle() {}

Particle::Particle(const std::vector<double>& initialPosition) {
    position = initialPosition;
    fitness = std::numeric_limits<double>::max(); // Initialize fitness to maximum
    velocity.resize(initialPosition.size(), 0.0); // Initialize velocity to zero
}

Particle::~Particle() {}

void Particle::setPosition(const std::vector<double>& newPosition) {
    position = newPosition;
}

std::vector<double> Particle::getPosition() const {
    return position;
}

double Particle::getFitness() const {
    return fitness;
}

void Particle::setFitness(double newFitness) {
    fitness = newFitness;
}

void Particle::updateVelocity(const std::vector<double>& globalBestPosition, double inertiaWeight, double personalWeight, double socialWeight) {
    // Update velocity based on the inertia, personal, and social components
    for (size_t i = 0; i < velocity.size(); ++i) {
        double personalComponent = personalWeight * (rand() / static_cast<double>(RAND_MAX)) * (position[i] - getPosition()[i]);
        double socialComponent = socialWeight * (rand() / static_cast<double>(RAND_MAX)) * (globalBestPosition[i] - getPosition()[i]);
        velocity[i] = inertiaWeight * velocity[i] + personalComponent + socialComponent;
    }
}

void Particle::updatePosition() {
    // Update position based on the current velocity
    for (size_t i = 0; i < position.size(); ++i) {
        position[i] += velocity[i];
    }
}

// Implementation of SwarmSearch class
SwarmSearch::SwarmSearch(int numParticles, int numDimensions, double inertiaWeight, double personalWeight, double socialWeight)
    : numParticles(numParticles), numDimensions(numDimensions), inertiaWeight(inertiaWeight), personalWeight(personalWeight), socialWeight(socialWeight) {}

SwarmSearch::~SwarmSearch() {}

void SwarmSearch::initializeSwarm() {
    particles.clear();
    globalBestFitness = std::numeric_limits<double>::max();

    // Initialize particles with random positions
    for (int i = 0; i < numParticles; ++i) {
        std::vector<double> initialPosition;
        for (int j = 0; j < numDimensions; ++j) {
            initialPosition.push_back((rand() / static_cast<double>(RAND_MAX)) * 10.0 - 5.0); // Random initial position in the range [-5, 5]
        }
        particles.push_back(Particle(initialPosition));
    }
}

void SwarmSearch::updateSwarm() {
    // Update each particle's velocity and position
    for (int i = 0; i < numParticles; ++i) {
        particles[i].updateVelocity(globalBestPosition, inertiaWeight, personalWeight, socialWeight);
        particles[i].updatePosition();

        // Update particle's fitness
        double fitness = particles[i].getPosition()[0] * particles[i].getPosition()[0] + particles[i].getPosition()[1] * particles[i].getPosition()[1];
        particles[i].setFitness(fitness);

        // Update global best if necessary
        if (particles[i].getFitness() < globalBestFitness) {
            globalBestFitness = particles[i].getFitness();
            globalBestPosition = particles[i].getPosition();
        }
    }
}

std::vector<double> SwarmSearch::getGlobalBestPosition() const {
    return globalBestPosition;
}
