#include <iostream>
#include <string.h>
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
using namespace std::chrono;


int main(int argc, char* argv[]) {
    cout << "Particle Swarm Optimization Menu :" << endl;
    cout << "PSO Usage: <num_particles> , <dimensions> , <maxIter> " << endl;

    /*
     * cout << "Functions available : " << endl;
     * maybe we generate random numbers according to the obj fct like in the pdf..
     *
    */

    //Converting strings to integers..
    int num_particles = atoi(argv[1]);     // Population size (P)
    int dimensions = atoi(argv[2]);         // Number of dimensions (D)
    int max_iter = atoi(argv[3]);            // Maximum iteration number
    string objFunc_name = argv[4];          // Objective function name
 
    //set to 5... to add obj function..
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

    // Bounds for the objective function
    std::pair<double, double>* bounds = ObjectiveFunction::get_bounds(objFunc_name, dimensions);

    //Function pointer type
    typedef double (*ObjFuncPtr)(double*, int);

    // Create a function pointer and point it to Rosenbrock
    ObjFuncPtr objective_function = ObjectiveFunction::Rosenbrock;


    /*
    Random number generation for intializing particle values...
    {To be moved later to the Objective function...}
    */
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);

    
    // Array to hold the best global position values of all particles in the swarm for each dimension.
    double *x_best_global = new double[dimensions];
 
    // Best global fitness value for optimization :
    double bestfitness_global = 0;
    int best_index = 0;

    // Vector to fill the swarm particles inside; maybe change it to dynamic array?
    vector<Particle> swarm;

    // Initialize the particles of the swarm.
    for (int i = 0; i < num_particles; ++i) {
        Particle p(dimensions);

        for(int N = 0 ; N < dimensions; N++){
            // Initialize N-dimensional postisions of a particle.
            p.setPositionAtIndex(N, dis(gen));
            // Initialize N-dimensional velocities of a particle.
            p.setVelocityAtIndex(N, dis(gen));
            // Initialize N-dimensional best postisions of a particle.
            p.setBestPositionAtIndex(N, p.getPosAtIndex(N));

        }

        // Initialize the fitness value of a particle based on an objective function.
        p.setFitness(ObjectiveFunction::SphereOne(p.getPosition(),dimensions));
        p.setBestFitness(p.getFitness());

        swarm.emplace_back(p);

        if(swarm[i].getFitness() < swarm[best_index].getFitness()){
            best_index = i;
        }
    }
    
    x_best_global = swarm[best_index].getPosition();         // Initialize global best position
    bestfitness_global = swarm[best_index].getFitness();     // Initialize global best solution

    PSO_serial.push_back(x_best_global);                               // Store initial global best solution
    PSO_serial.global_best_positions_history.push_back(bestfitness_global);                    // Store initial global best position


    //PSO init
    PSO_serial algorithm(max_iter); 

    //Execution time profiling (TODO: for the moment biased by the time spent writting in CSV files -> writting in csv outside of PSO method )
    const auto t0 = high_resolution_clock::now();
    
    // Execute PSO(function , bounds of each dim , num particles , maxiter)
    algorithm.pso(objective_function, bounds, num_particles, max_iter, inertiaWeight, c1, c2);

    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();

    /*OUTPUT*/
    
    std::ofstream file("../data/global_best_sol_history.csv");
    for (auto& val: algorithm.global_best_sol_history) {file << val << std::endl;} 
    file << std::endl;
    file.close();

    std::string function_name = "Rosenbrock";

    std::cout << "---------------------------Parameters----------------------------" << std::endl;
    //std::cout << "PSO version: "<< "serial/parallel" << std::endl;
    std::cout << "Objective function:   " << function_name << std::endl;
    std::cout << "Number of dimensions: " << dimensions << std::endl;
    std::cout << "Number of particles:  " << num_particles << std::endl;
    std::cout << "Maximum iterations:   " << max_iter << std::endl;
    std::cout << "\n-------------------------Hyperparameters-------------------------" << std::endl;
    std::cout << "Constant inertia weight: " << inertiaWeight << std::endl;
    std::cout << "Acceleration constant 1: " << c1 << std::endl;
    std::cout << "Acceleration constant 2: " << c2 << std::endl;
    std::cout << "\n----------------------------Solution-----------------------------" << std::endl;
    std::cout << "Best Value     : " << algorithm.global_best_sol_history.back() << std::endl;
    std::cout << "Best Position  : ";
    for (auto& val: algorithm.global_best_positions_history.back()) { std::cout << val << " ";}
    std::cout << std::endl;
    std::cout <<  "\n----------------------------Profiling----------------------------" << std::endl;
    std::cout << "Time for all iterations: " << dt << " [ms]" << " -> " << dt/1000.0 << " [s]" << " -> " << (dt/1000.0)/60.0 << " [min]" << std::endl;
    std::cout << "Time for 1 iteration:    " << dt / max_iter << " [ms]" << std::endl;
    std::cout << "Memory used:             " << sizeof(algorithm) << " [bytes]" << std::endl;

    return 0;
}
