#include <iostream>
#include <limits>
#include <random>
#include <fstream>

#include "PSO.hpp"

using namespace std;


// Constructor to initialize with dynamic arrays
PSO::PSO(int dimensions, int max_iter) : dimensions(dimensions) {

    this->max_iter = max_iter;
    //Global Best fitness & position.
    global_best_sol = std::numeric_limits<double>::max();
    global_best_position = new double[dimensions];
    //History.
    global_best_sol_history = new double[max_iter];
    global_best_positions_history = new double*[max_iter];

    for(int i = 0; i < max_iter; i++){
            global_best_positions_history[i] = new double[dimensions];
    }
    
}
/*
// Destructor to free the allocated memory
PSO::~PSO() {
    delete[] global_best_position;
    delete[] global_best_sol_history;

    for (int i = 0; i < max_iter; i++) {
        delete[] global_best_positions_history[i];
    }
    delete[] global_best_positions_history;
}
*/
void PSO::PSO_Serial(double (*ObjFuncPtr)(double*, int),
                     const int dimensions,
                     const std::pair<double, double>* &bounds,
                     vector<Particle> &swarm,
                     int num_particles,
                     int max_iter,
                     const double intertiaWeight,
                     const double c1, const double c2){
    // Main loop
    for (int iter = 0; iter < max_iter; ++iter) {
        int particle_count = 0;

        for (int j = 0; j < num_particles; j++){
            for(int d = 0 ; d < dimensions; d++){

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, 1.0);
                std::vector<double> r1 = {dis(gen), dis(gen)};
                std::vector<double> r2 = {dis(gen), dis(gen)};

                // Important; i read in a paper about the r1, r2; we should try U[-1,1] not only U[0,1]

                // UPDATING THE NEW VELOCITY
                swarm[j].setVelocityAtIndex(d,(intertiaWeight*(swarm[j].getVelocityAtIndex(d))
                + c1*(swarm[j].getBestPosAtIndex(d) - swarm[j].getPosAtIndex(d))*r1[d]
                + c2*(global_best_position[d] - swarm[j].getPosAtIndex(d))*r2[d]));

                // UPDATING THE NEW POSITION
                swarm[j].setPositionAtIndex(d,(swarm[j].getPosAtIndex(d) + swarm[j].getVelocityAtIndex(d)));
            }

            swarm[j].setFitness(ObjFuncPtr(swarm[j].getPosition(),dimensions));

            // Update local best
            if (swarm[j].getFitness() < swarm[j].getBestFitness()) {
                swarm[j].setBestFitness(swarm[j].getFitness());
                for (int dd = 0; dd < dimensions ; dd++){ // we can make a fct instead to copy arrays..
                    swarm[j].setBestPositionAtIndex(dd,swarm[j].getPosAtIndex(dd));
                }
            }

            // Update global best position and solution
            if (swarm[j].getBestFitness() < global_best_sol) {
                global_best_sol = swarm[j].getBestFitness();
                for (int dd = 0; dd < dimensions ; dd++){
                    global_best_position[dd] = swarm[j].getBestPosAtIndex(dd);
                }

            }
            particle_count++;
        }
        global_best_sol_history[iter] = global_best_sol;
        global_best_positions_history[iter] = global_best_position;
    }
}