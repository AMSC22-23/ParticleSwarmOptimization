#include "SwarmSearch.hpp"
#include <iostream>

int main() {
    const int numParticles = 30;
    const int numDimensions = 2;
    const double inertiaWeight = 0.5;
    const double personalWeight = 1.5;
    const double socialWeight = 1.5;

    SwarmSearch swarm(numParticles, numDimensions, inertiaWeight, personalWeight, socialWeight);

    // Initialize swarm
    swarm.initializeSwarm();

    // Run the swarm search for a certain number of iterations
    const int numIterations = 100;
    for (int iter = 0; iter < numIterations; ++iter) {
        // Update the swarm
        swarm.updateSwarm();

        // Print the global best position at each iteration
        std::cout << "Iteration " << iter + 1 << ": Global Best Position = ("
                  << swarm.getGlobalBestPosition()[0] << ", " << swarm.getGlobalBestPosition()[1] << ")"
                  << "  Global Best Fitness = " << swarm.getGlobalBestPosition()[0] * swarm.getGlobalBestPosition()[0] +
                         swarm.getGlobalBestPosition()[1] * swarm.getGlobalBestPosition()[1]
                  << std::endl;
    }

    return 0;
}
