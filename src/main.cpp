#include <iostream>
#include <cmath>
#include "Particle.hpp"
#include "PSO.hpp"

int main() {
    auto objective_function = [](const std::vector<double>& position) -> double {
        double x = position[0];
        double y = position[1];

        // 2D Rosenbrock function w/ global min of 0 at (1,1) 
        //f(x) = (1-x)^2 + 100*(y-x^2)^2
        double f = std::pow(1-x,2)+100*std::pow(y-std::pow(x,2),2);
        return f;
    };  

    // Define the bounds for each dimension
    std::vector<std::pair<double, double>> bounds = {{-10, 10}, {-10, 10}}; // 2 dimensions

    PSO_serial algorithm; 
    
    // Execute PSO(function , bounds of each dim , num particles , maxiter)
    algorithm.pso(objective_function, bounds, 30, 50000);

    return 0;
}
