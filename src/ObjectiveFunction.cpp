#include "ObjectiveFunction.hpp"
#include <cmath>

/*
2D Ackley function:
Minimun at f(0,0) = 0
*/
double ObjectiveFunction::Ackley(const std::vector<double>& position) {
    double x = position[0];
    double y = position[1];
    double f = -20*exp(-0.2*sqrt(0.5*(std::pow(x,2)+std::pow(y,2))))-exp(0.5*(cos(2*M_PI*x)+cos(2*M_PI*y)))+exp(1)+20;
    return f;
};

/*
N dimensional Rosenbrock function:
Minimun at f(1,1,...,1) = 0
*/
double ObjectiveFunction::Rosenbrock(const std::vector<double>& position) {
    double f = 0;
    for (std::vector<double>::size_type i = 0; i < position.size()-1; ++i) {
        f += 100*std::pow(position[i+1]-std::pow(position[i],2),2)+std::pow(1-position[i],2); 
    }
    return f;
};

/*
N dimensional Rastrigin function:
Minimun at f(0,0,...,0) = 0
*/
double ObjectiveFunction::Rastrigin(const std::vector<double>& position) {
    double f = 10*position.size();
    for (std::vector<double>::size_type i = 0; i < position.size(); ++i) {
        f += std::pow(position[i],2)-10*cos(2*M_PI*position[i]);
    }
    return f;
};