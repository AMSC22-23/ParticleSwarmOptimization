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
    PSO_serial(int max_iter): PSO() {
        global_best_sol_history.reserve(max_iter);
        global_best_positions_history.reserve(max_iter);
    }
    void pso(std::function<double(const std::vector<double>&)> objective_function,
            const std::vector<std::pair<double, double>>& bounds,
            int num_particles,
            int max_iter) override;

    std::vector<double> global_best_sol_history;
    std::vector<std::vector<double>> global_best_positions_history;
};
#endif