#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <memory>
#include "Particle.hpp"
#include "PSO.hpp"
#include "ObjectiveFunction.hpp"

int main() {

    using namespace std::chrono;

    const int num_particles = 400;
    const int max_iter = 10000;
    const double ciw = 0.5;      //Constant inertia weight
    const double c1 = 2.0;       //Acceleration constants
    const double c2 = 2.0;

    // Define the bounds for each dimension
    std::vector<std::pair<double, double>> bounds = {{-30, 30}, {-30, 30}, {-30, 30}, {-30, 30}}; 

    //Function to minimize
    double (*objective_function)(const std::vector<double>&) = ObjectiveFunction::Rosenbrock;

    //PSO init
    PSO_serial algorithm(max_iter); 

    //Execution time profiling (TODO: for the moment biased by the time spent writting in CSV files -> writting in csv outside of PSO method )
    const auto t0 = high_resolution_clock::now();
    
    // Execute PSO(function , bounds of each dim , num particles , maxiter)
    algorithm.pso(objective_function, bounds, num_particles, max_iter, ciw, c1, c2);

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
    std::cout << "Number of dimensions: " << bounds.size() << std::endl;
    std::cout << "Number of particles:  " << num_particles << std::endl;
    std::cout << "Maximum iterations:   " << max_iter << std::endl;
    std::cout << "\n-------------------------Hyperparameters-------------------------" << std::endl;
    std::cout << "Constant inertia weight: " << ciw << std::endl;
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
