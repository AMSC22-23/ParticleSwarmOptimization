#ifndef OBJECTIVEFUNCTION_HPP
#define OBJECTIVEFUNCTION_HPP

#include <vector>
namespace ObjectiveFunction {

    double Ackley(double* position, int dim);
    double Rosenbrock(double* position, int dim);
    double Rastrigin(double* position, int dim);
    double Quadratic_function(double *position, int dim);
    double SphereOne(double *position, int dim);

    std::pair<double, double>* ObjectiveFunction::get_bounds(std::string objFunction, int dim);
}

#endif // OBJECTIVEFUNCTION_HPP