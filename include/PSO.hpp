#ifndef PSOALGO_HPP
#define PSOALGO_HPP

#include <functional>
#include <vector>
#include "Particle.hpp"

class PSO{
public:
    PSO(){}
    virtual void pso(std::function<double(const std::vector<double>&)> objective_function,
            const std::vector<std::pair<double, double>>& bounds,
            int num_particles,
            int max_iter) = 0; 
};

class PSO_serial : public PSO {
public:
    PSO_serial(): PSO() {}
    void pso(std::function<double(const std::vector<double>&)> objective_function,
            const std::vector<std::pair<double, double>>& bounds,
            int num_particles,
            int max_iter) override;
};
#endif