#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <memory>
#include "Particle.hpp"
#include "PSO.hpp"

template <typename T>
T Ackley(const std::vector<T>& position) { //global min of 0 at (0,0)
    T x = position[0];
    T y = position[1];
    T f = -20*exp(-0.2*sqrt(0.5*(std::pow(x,2)+std::pow(y,2))))-exp(0.5*(cos(2*M_PI*x)+cos(2*M_PI*y)))+exp(1)+20;
    return f;
};

double (*objective_function)(const std::vector<double>&) = Ackley<double>;


int main() {

    using namespace std::chrono;

    const int num_particles = 10;
    const int max_iter = 200;
/* 
    //CSV file for each particle to store its position and value data at each iteration
    for (int i = 0; i < num_particles; ++i) {
        std::string filename = "../data/particle_data/particle_" + std::to_string(i) + "_pos.csv";
        std::ofstream file(filename);
    }
 */
    // Define the bounds for each dimension
    std::vector<std::pair<double, double>> bounds = {{-30, 30}, {-30, 30}}; // 2 dimensions

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
/* 
    //Save the global best position history in a CSV file
    std::ofstream file2("../data/global_best_positions_history.csv");
    for (auto& pos : algorithm.global_best_positions_history) {
        file2 << pos[0] <<","<< pos[1] << std::endl;
    }
   */  

    std::cout << "-------------------------Profiling-------------------------" << std::endl;
    std::cout << "Elapsed time for computing all iterations : " << dt << " [ms]" << std::endl;

    return 0;
}
