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