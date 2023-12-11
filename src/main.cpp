#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <limits>
#include <fstream>
#include <cmath>
#include <chrono>
#include <memory>
#include "Particle.hpp"
#include "PSO.hpp"
#include "ObjectiveFunction.hpp"

// PSO parameters
// Acceleration constants C1 & C2
const double c1 = 2.0;  // Cognitive parameter
const double c2 = 2.0;  // Social parameter

// Inertia weight
const double inertiaWeight = 0.5;

using namespace std;
using namespace chrono;


int main(int argc, char* argv[]) {
    //Converting arg strings to integers..
    int num_particles = atoi(argv[1]);
    int dimensions = atoi(argv[2]);
    int max_iter = atoi(argv[3]);
    string objFunc_name = argv[4];
 
    //Error catching in the arguments
    if(argc != 5){
        cout << "Usage: " << argv[0] << " <num_particles> <dimensions> <MaxIter> <objectiveFunction>" << endl;
        return 1;
    }
    else if(num_particles <= 0){
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

    PSO_serial algorithm(dimensions, max_iter); //PSO init
    vector<Particle> swarm;                     //Swarm init

    // Get bounds of obj_func
    const pair<double, double>* bounds = ObjectiveFunction::get_bounds(objFunc_name, dimensions);

    //Get obj_func
    typedef double (*ObjFuncPtr)(double*, int);
    ObjFuncPtr objective_function = ObjectiveFunction::Rosenbrock;

    // Uniform dist in the bounds of the obj_func
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(bounds[0].first, bounds[0].second);

    // Initialize the particles of the swarm.
    int best_index = 0;
    for (int i = 0; i < num_particles; ++i) {
        swarm.emplace_back(dimensions);

        // Init position, velocity & best position for each dimension
        for(int N = 0 ; N < dimensions; N++){
            swarm.back().setPosition(N, dis(gen));
            swarm.back().setVelocity(N, dis(gen));
            swarm.back().setBestPosition(N, swarm.back().getSinglePosition(N));
        }
        swarm.back().setValue(objective_function(swarm.back().getPosition(),dimensions));
        swarm.back().setBestValue(swarm.back().getValue());

        if(swarm.back().getValue() < swarm[best_index].getValue()){
            best_index = i;
        }
    }
    algorithm.global_best_position = swarm[best_index].getPosition(); // Init global best position
    algorithm.global_best_sol = swarm[best_index].getValue();         // Init global best solution

    // Time profiling
    const auto t0 = high_resolution_clock::now();
    
    // Execute PSO(function , bounds of each dim , num particles , maxiter)
    algorithm.pso(objective_function, dimensions, swarm, max_iter, inertiaWeight, c1, c2);

    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();

    /*OUTPUT*/
/*     ofstream file("../data/global_best_sol_history.csv");
    for (auto &val: algorithm.global_best_sol_history) {file << val << endl;} 
    file << endl;
    file.close(); */

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
    cout << "Best Value     : " << algorithm.global_best_sol_history[max_iter] << endl;
    cout << "Best Position  : " << endl;
/*     for (auto& val: algorithm.global_best_positions_history[max_iter]) { cout << val << " ";}
    cout << endl; */
    cout <<  "\n----------------------------Profiling----------------------------" << endl;
    cout << "Time for all iterations: " << dt << " [ms]" << " -> " << dt/1000.0 << " [s]" << " -> " << (dt/1000.0)/60.0 << " [min]" << endl;
    cout << "Time for 1 iteration:    " << dt / max_iter << " [ms]" << endl;
    cout << "Memory used:             " << sizeof(algorithm) << " [bytes]" << endl;

    return 0;
}