#ifndef PSOALGO_HPP
#define PSOALGO_HPP

#include <functional>
#include <vector>

#include "Particle.hpp"

class PSO{

public:

    // Dimension of the problem.
    int dimensions;
    // Maximum number of iterations.
    int max_iter;
    // Best global solution/fitness value.
    double  global_best_sol;
    // Best global solution/fitness value history.
    double* global_best_sol_history;
    // Best global position.
    double* global_best_position;
    // Best global position history.
    double** global_best_positions_history;

public:

     // Constructor to initialize the dynamic arrays
    PSO(int dimensions, int max_iter);

    // Destructor to free the allocated memory
   // ~PSO();

    // PSO Algorithm function.
    void PSO_Serial(double (*ObjFuncPtr)(double*, int),
                     const int dimensions,
                     const std::pair<double, double>* &bounds,
                     vector<Particle> &swarm,
                     int num_particles,
                     int max_iter,
                     const double intertiaWeight,
                     const double c1, const double c2);
};
#endif