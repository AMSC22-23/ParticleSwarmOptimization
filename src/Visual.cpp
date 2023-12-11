#include <cmath>
#include <string>
#include <iostream>

#include "Visual.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

using namespace std;

void Visual::Menu(){

    cout << "Welcome to the Particle Swarm Optimization (PSO) algorithm." << endl;
    cout << "Usage:  <num_particles> <dimensions> <MaxIter> <objectiveFunction>" << endl;

    cout << "Objective functions available :" << endl;
    cout << "1. Ackley function" << endl;
    cout << "2. Rosenbrock function " << endl;
    cout << "3. Rastrigin function" << endl;
    cout << "4. Sphere function" << endl;
    cout << "5. quadratic function" << endl;

};


void Visual::printShape(int r) {

    int i, j;
    // Upper part of the shape
    for (i = r; i >= 1; i--) {
        for (j = 1; j <= i; j++)
            cout << RED << "* ";
        for (j = 1; j <= 2 * (r - i); j++)
            cout << "  ";
        for (j = 1; j <= 2 * i; j++)
            cout << BLUE << "* ";;
        cout << "\n";
    }

    // Lower part of the shape
    for (i = 1; i <= r; i++) {
        for (j = 1; j <= i; j++)
            cout << CYAN << "* ";
        for (j = 1; j <= 2 * (r - i); j++)
            cout << "  ";
        for (j = 1; j <= 2 * i; j++)
            cout << RED << "* ";
        cout << "\n";
    }

    cout << RESET << endl;
};

void Visual::ErrorHandling(int num_particles, int dimensions, int max_iter){
    
    if(num_particles <= 0){
        cout << "Error: Number of particles should be more than 0." << endl;
        exit(1);
    }
    else if(dimensions <= 0){
        cout << "Error: Dimensions of the problem should be at least 1." << endl;
        exit(1);
    }
    else if(max_iter <= 0){
        cout << "Error : the amount of iterations should be at least greater than 1." << endl;
        exit(1);
    }

};