#ifndef SWARMSEARCH_HPP
#define SWARMSEARCH_HPP

#include <vector>

class Particle {
public:
    Particle();
    Particle(const std::vector<double>& initialPosition);
    ~Particle();

    void setPosition(const std::vector<double>& newPosition);
    std::vector<double> getPosition() const;
    double getFitness() const;
    void setFitness(double newFitness);
    void updateVelocity(const std::vector<double>& globalBestPosition, double inertiaWeight, double personalWeight, double socialWeight);
    void updatePosition();

private:
    std::vector<double> position;
    double fitness;
    std::vector<double> velocity;
};

class SwarmSearch {
public:
    SwarmSearch(int numParticles, int numDimensions, double inertiaWeight, double personalWeight, double socialWeight);
    ~SwarmSearch();

    void initializeSwarm();
    void updateSwarm();
    std::vector<double> getGlobalBestPosition() const;

private:
    int numParticles;
    int numDimensions;
    double inertiaWeight;
    double personalWeight;
    double socialWeight;
    std::vector<Particle> particles;
    std::vector<double> globalBestPosition;
    double globalBestFitness;

    void updateGlobalBest();
};

#endif // SWARMSEARCH_HPP
