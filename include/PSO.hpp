#ifndef PSOALGO_HPP
#define PSOALGO_HPP

#include <functional>
#include <vector>
#include "Particle.hpp"

class PSO{
public:
    PSO(){}
    virtual void pso(double (*ObjFuncPtr)(double*, int),
            const int dimensions,
            vector<Particle> &swarm, 
            int max_iter, 
            const double intertiaWeight,
            const double c1, 
            const double c2) = 0; 
};
class PSO_serial : public PSO {
public:
    /* Constructor */
    PSO_serial(int dimensions, int max_iter): PSO() {
        this->max_iter = max_iter;
        /* Global bests */
        global_best_sol = std::numeric_limits<double>::max();
        global_best_position = new double[dimensions]; 
        /* History arrays */
        global_best_sol_history = new double[max_iter];
        global_best_positions_history = new double*[max_iter];
        for(int i =0; i < max_iter; i++){
            global_best_positions_history[i] = new double[dimensions]; 
        }
    }
    /* Destructor */
    ~PSO_serial() {
        if (global_best_position != nullptr) {
            delete[] global_best_position;
        }
        global_best_position = nullptr;
        delete[] global_best_sol_history;
        global_best_sol_history = nullptr; 
        for (int i = 0; i < max_iter; i++) {
            delete[] global_best_positions_history[i];
            global_best_positions_history[i] = nullptr;
        }
        delete[] global_best_positions_history;
        global_best_positions_history = nullptr;
    }

    void pso(double (*ObjFuncPtr)(double*, int),
           const int dimensions,
            vector<Particle> &swarm, 
            int max_iter, 
            const double intertiaWeight,
            const double c1, const double c2) override;

    int max_iter;
    double global_best_sol;
    double* global_best_position;
    double* global_best_sol_history;
    double** global_best_positions_history;
};
#endif