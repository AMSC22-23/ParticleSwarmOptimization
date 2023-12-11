#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <limits>
#include <fstream>
#include <cmath>
#include <chrono>
#include <memory>
#include <vector>

#include "Particle.hpp"
#include "PSO.hpp"
#include "ObjectiveFunction.hpp"
#include "Visual.hpp"

// PSO parameters
// Acceleration constants C1 & C2
const double c1 = 2.0;  // Cognitive parameter
const double c2 = 2.0;  // Social parameter

// Inertia weight
const double inertiaWeight = 0.5;

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    Visual::printShape(5);
    Visual::Menu();

    // Retrieve arguments from command line
    int num_particles = atoi(argv[1]);      // Population size (P)
    int dimensions = atoi(argv[2]);         // Number of dimensions (N-D)
    int max_iter = atoi(argv[3]);           // Maximum iteration number
    string objFunc_name = argv[4];          // Objective function

    //Error catching in the arguments
    if(argc != 5){
        cout << "Usage: " << argv[0] << " <num_particles> <dimensions> <MaxIter> <objectiveFunction>" << endl;
        exit(1);
    }

    Visual::ErrorHandling(num_particles,dimensions,max_iter);
   
    // Checking for the availability of the objective function & retrieving it's bounds.
    const pair<double, double>* bounds = ObjectiveFunction::get_bounds(objFunc_name, dimensions);

    //Retrieving the objective function method.
    typedef double (*ObjFuncPtr)(double*, int);

    /*
    HERE WE NEED TO FIX THE MANUAL CHOSING....
    */
    ObjFuncPtr objective_function = ObjectiveFunction::Rosenbrock;

    // Uniform distribution based on the bounds of the chosen objective function.
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(bounds->first, bounds->second);

    PSO algorithm(dimensions, max_iter);                     // PSO Problem initialization

    vector<Particle> swarm;                                  // Vector of swarm particles

    // Initializing the particles of the swarm.
    int best_index = 0;

    for (int i = 0; i < num_particles; i++) {
        Particle p(dimensions);

        // Initializing N-dimensional postisions, best postions & velocities of a particle
        for(int N = 0 ; N < dimensions; N++){
            p.setPositionAtIndex(N, dis(gen));
            p.setVelocityAtIndex(N, dis(gen));
            p.setBestPositionAtIndex(N, p.getPosAtIndex(N));
        }

        // Initialize the fitness value of a particle based on an objective function.
        p.setFitness(ObjectiveFunction::Rosenbrock(p.getPosition(),dimensions));
        p.setBestFitness(p.getFitness());

        
        swarm.emplace_back(p);

       if(swarm[i].getFitness() < swarm[best_index].getFitness()){
            best_index = i;
        }
    }

    // Initializing the global best position and fitness value (solution).
    algorithm.global_best_position = swarm[best_index].getBestPosition();
    algorithm.global_best_sol = swarm[best_index].getFitness();

    // Time profiling
    const auto t0 = high_resolution_clock::now();

    //Execute PSO(function , bounds of each dim , num particles , maxiter)
    algorithm.PSO_Serial(objective_function, dimensions, bounds, swarm, num_particles, max_iter, inertiaWeight, c1, c2);

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
    //for (auto& val: algorithm.global_best_positions_history[max_iter]) { cout << val << " ";} cout << endl;
    cout <<  "\n----------------------------Profiling----------------------------" << endl;
    cout << "Time for all iterations: " << dt << " [ms]" << " -> " << dt/1000.0 << " [s]" << " -> " << (dt/1000.0)/60.0 << " [min]" << endl;
    cout << "Time for 1 iteration:    " << dt / max_iter << " [ms]" << endl;
   // cout << "Memory used:             " << sizeof(algorithm) << " [bytes]" << endl;

    return 0;
}

