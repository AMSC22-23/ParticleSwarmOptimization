#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "swarmfct.hpp"

using namespace std;

double ObjectiveFunction::SphereOne(double *x, int dim) {

    double result;

    for(size_t i = 0; i < dim ; i++){
        result += pow(x[i],2);
    }

    return result;
}

// Objective function (here it minimizes a simple quadratic function)
double ObjectiveFunction::Quadratic_function(double *x, int dim) {

    double result;

    for (size_t i = 0; i < dim; i++) {
        result += (i+1)*10*pow(x[i],2) + (i+1)*20*pow(x[i],2);
    }

    return result;
}