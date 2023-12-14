#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <limits>
#include <fstream>
#include <cmath>
#include <chrono>
#include <memory>
#include <functional>
#include "Particle.hpp"
#include "ObjectiveFunction.hpp"
#include "Swarm.hpp"

// PSO parameters
//    Acceleration constants C1 & C2
const double c1 = 2.0;  // Cognitive parameter
const double c2 = 2.0;  // Social parameter

// Inertia weight
double inertiaWeight = 0.5;

using namespace std;
using namespace chrono;


int main(int argc, char* argv[]) {
    // Error catching for input
    if(argc != 6){
        cout << "Usage: " << argv[0] << " <num_particles> <dimensions> <MaxIter> <objectiveFunction>" << endl;
        return 1;
    }

    // Convert arg strings to integers
    int num_particles = atoi(argv[1]);
    int dimensions = atoi(argv[2]);
    int max_iter = atoi(argv[3]);
    string objective_function_name = argv[4];
    int history = atoi(argv[5]);
 
    if(num_particles <= 0){
        cout << "Error: Number of particles should be more than 0." << endl;
        return 1;
    }
    else if(dimensions <= 0){
        cout << "Error: Dimensions of the problem should be at least 1." << endl;
        return 1;
    }
    else if(max_iter <= 0){
        cout << "Error : the amount of iterations should be at least greater than 1." << endl;
        return 1;
    }

    // Global best solution history
    double* global_best_sol_history = new double[max_iter];

    // Time profiling
    const auto t0 = high_resolution_clock::now();
    
    // Execute PSO
    Swarm swarm(num_particles, dimensions, objective_function_name);

    for (int i = 0; i < max_iter; ++i) {
        swarm.updateParticles();
        swarm.updateGlobalBestParticle();
        
        //global_best_sol_history[i] = history ? swarm.global_best_particle.value : global_best_sol_history[i];
    }

    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();

    // OUTPUT
/*     ofstream file("../data/global_best_sol_history.csv");
    for (int i = 0; i < max_iter; ++i) {
        file << global_best_sol_history[i] << endl;
    }
    file.close(); */

    delete[] global_best_sol_history;

    cout << "---------------------------Parameters----------------------------" << endl;
    //cout << "PSO version: "<< "serial/parallel" << endl;
    cout << "Objective function:   " << argv[4] << endl;
    cout << "Number of dimensions: " << dimensions << endl;
    cout << "Number of particles:  " << num_particles << endl;
    cout << "Maximum iterations:   " << max_iter << endl;
    cout << "\n-------------------------Hyperparameters-------------------------" << endl;
    cout << "Constant inertia weight: " << inertiaWeight << endl;
    cout << "Acceleration constant 1: " << c1 << endl;
    cout << "Acceleration constant 2: " << c2 << endl;
    cout << "\n----------------------------Solution-----------------------------" << endl;
    cout << "Best Value     : " << swarm.global_best_particle.value << endl;
    cout <<  "\n----------------------------Profiling----------------------------" << endl;
    cout << "Time for all iterations: " << dt << " [ms]" << " -> " << dt/1000.0 << " [s]" << " -> " << (dt/1000.0)/60.0 << " [min]" << endl;
    cout << "Time for 1 iteration:    " << dt / max_iter << " [ms]" << endl;

    return 0;
}