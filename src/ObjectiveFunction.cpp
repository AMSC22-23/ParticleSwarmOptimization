#include "ObjectiveFunction.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <functional>

using namespace std;

/*
2D Ackley function:
Minimun at f(0,0) = 0
*/
double ObjectiveFunction::Ackley(double* position, int dim) {
    double x =0.0;
    double y =0.0;
    for (int i = 0; i < dim; ++i) {
        x += pow(position[i],2);
        y += cos(2*M_PI*position[i]);
    }
    return -20 * exp(-0.2*sqrt(x/dim))-exp(y/dim)+20+M_E;
};

/*
N dimensional Rosenbrock function:
Minimun at f(1,1,...,1) = 0
*/
double ObjectiveFunction::Rosenbrock(double* position, int dim) {
    double f=0.0;
    for (int i = 0; i < dim; ++i) {
        f += 100*pow(position[i]-pow(position[i],2),2)+pow(1-position[i],2); 
    }
    return f;
};

/*
N dimensional Rastrigin function:
Minimun at f(0,0,...,0) = 0
*/
double ObjectiveFunction::Rastrigin(double* position, int dim) {
    double f=0.0;
    for (int i = 0; i < dim-1; ++i) {
        f += pow(position[i],2)-10*cos(2*M_PI*position[i]);
    }
    return f;
};

/* Sphere function */
double ObjectiveFunction::SphereOne(double* position, int dim) {
    double result;
    for(int i = 0; i < dim-1; i++){
        result += pow(position[i],2);
    }
    return result;
}

/* Simple quadratic function */
double ObjectiveFunction::Quadratic_function(double* position, int dim) {
    double result;
    for (int i = 0; i < dim-1; i++) {
        result += (i+1)*10*pow(position[i],2) + (i+1)*20*pow(position[i],2);
    }
    return result;
}

pair<double, double>* ObjectiveFunction::get_bounds(string objFunction, int dim) {
    pair<double, double>* bounds = new pair<double, double>[dim]; 
    if (objFunction == "rosenbrock") {
        for (int i = 0; i < dim; ++i) {
            bounds[i] = make_pair(-30, 30);
        }
    } else if (objFunction == "ackley") {
        for (int i = 0; i < dim; ++i) {
            bounds[i] = make_pair(-5, 10);
        }
    } else if (objFunction == "rastrigin") {
        for (int i = 0; i < dim; ++i) {
            bounds[i] = make_pair(-5.12, 5.12);
        }
    } else if (objFunction == "sphereOne") {
        for (int i = 0; i < dim; ++i) {
            bounds[i] = make_pair(-100, 100);
        }
    } else if (objFunction == "quadratic") {
        for (int i = 0; i < dim; ++i) {
            bounds[i] = make_pair(-100, 100);
        }
    }else {
        cout << "Error: Invalid objective function." << endl;
        exit(1);
    }
    return bounds;
}

function<double(double*, int)> ObjectiveFunction::get_objective_function(string objective_function_name) {
    if (objective_function_name == "rosenbrock") {
        return Rosenbrock;
    } else if (objective_function_name == "ackley") {
        return Ackley;
    } else if (objective_function_name == "rastrigin") {
        return Rastrigin;
    } else if (objective_function_name == "sphereOne") {
        return SphereOne;
    } else if (objective_function_name == "quadratic") {
        return Quadratic_function;
    } else {
        cout << "Error: Invalid objective function." << endl;
        exit(1);
    }
}