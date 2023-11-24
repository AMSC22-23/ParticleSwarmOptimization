#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>

class Particle {
public:
    std::vector<double> position;
    std::vector<double> velocity;
    std::vector<double> best_position;
    double value; 
    double best_sol;

    Particle(int dimensions, const std::vector<std::pair<double, double>>& bounds);
};
#endif