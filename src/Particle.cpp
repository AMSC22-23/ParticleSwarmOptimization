#include <random>
#include <limits>
#include <vector>
#include "Particle.hpp"

Particle::Particle(int dimensions, const std::vector<std::pair<double, double>>& bounds) : best_sol(std::numeric_limits<double>::infinity()) {
    // Marsenne Twister nb generator w/ random seed generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < dimensions; ++i) {
        std::uniform_real_distribution<> dis(bounds[i].first, bounds[i].second);
        position.push_back(dis(gen));
        velocity.push_back(dis(gen) - 0.5);
    }
    best_position = position;
}
