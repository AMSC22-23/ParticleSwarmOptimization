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

    const int num_particles = 300;
    const int max_iter = 10000;

    // Define the bounds for each dimension
    std::vector<std::pair<double, double>> bounds = {{-30, 30}, {-30, 30}, {-30, 30}, {-30, 30}, {-30, 30}}; // 5 dimensions

    //Function to minimize
    double (*objective_function)(const std::vector<double>&) = ObjectiveFunction::Rosenbrock;

    //PSO init
    PSO_serial algorithm(max_iter); 

    //Execution time profiling (TODO: for the moment biased by the time spent writting in CSV files -> writting in csv outside of PSO method )
    const auto t0 = high_resolution_clock::now();
    
    // Execute PSO(function , bounds of each dim , num particles , maxiter)
    algorithm.pso(objective_function, bounds, num_particles, max_iter);

    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();

    // Save the global best solution history in a CSV file
    std::ofstream file("../data/global_best_sol_history.csv");
    for (auto& val: algorithm.global_best_sol_history) {file << val << std::endl;} 
    file << std::endl;

    std::cout << "-------------------------Profiling-------------------------" << std::endl;
    std::cout << "Elapsed time for computing all iterations : " << dt << " [ms]" << std::endl;

    return 0;
}
