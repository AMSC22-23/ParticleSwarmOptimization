#include <iostream>
#include <cmath>
#include <chrono>
#include <memory>
#include "Particle.hpp"
#include "PSO.hpp"

int main() {

    using namespace std::chrono;

    auto objective_function = [](const std::vector<double>& position) -> double {
        double x = position[0];
        double y = position[1];

        // 2D Rosenbrock function w/ global min of 0 at (1,1) 
        //f(x,y) = (1-x)^2 + 100*(y-x^2)^2
        double f = std::pow(1-x,2)+100*std::pow(y-std::pow(x,2),2);
        return f;
    };  

    // Define the bounds for each dimension
    std::vector<std::pair<double, double>> bounds = {{-10, 10}, {-10, 10}}; // 2 dimensions

    PSO_serial algorithm; 

    //Execution time profiling
    const auto t0 = high_resolution_clock::now();
    
    // Execute PSO(function , bounds of each dim , num particles , maxiter)
    algorithm.pso(objective_function, bounds, 3, 100);

    const auto t1 = high_resolution_clock::now();
    const auto dt = duration_cast<milliseconds>(t1 - t0).count();

    std::cout << "-------------------------Profiling-------------------------" << std::endl;
    std::cout << "Elapsed time for computing all iterations : " << dt << " [ms]" << std::endl;

    return 0;
}
