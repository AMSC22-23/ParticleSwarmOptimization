#include <iostream>
#include <cmath>
#include <chrono>
#include <memory>
#include <string.h>
#include <random>
#include <vector>
#include <ctime>
#include <limits>


#include "Particle.hpp"
#include "swarmfct.hpp"


// PSO parameters
// Acceleration constants C1 & C2
const double c1 = 1.0;  // Cognitive parameter
const double c2 = 2.0;  // Social parameter

// Inertia weight
const double inertiaWeight = 0.5;

using namespace std;


int main(int argc, char* argv[]) {

    cout << "PSO Usage: <numOfParticles> , <dimensions> , <maxIter> " << endl;

    /*
     * cout << "Functions available : " << endl;
     * maybe we generate random numbers according to the obj fct like in the pdf..
     *
    */


    //Converting strings to integers..
    int numOfParticles = atoi(argv[1]);     // Population size (P)
    int dimensions = atoi(argv[2]);         // Number of dimensions (D)
    int maxIter = atoi(argv[3]);            // Maximum iteration number

    //set to 5... to add obj function..
    if(argc != 4){
        cout << "Usage: " << argv[0] << " <numOfParticles> <dimensions> <MaxIter> <objectiveFunction>" << endl;
        return 1;
    }
    else if(numOfParticles <= 0){
        cout << "Error: Number of particles should be more than 0." << endl;
        return 1;
    }
    else if(dimensions <= 0){
        cout << "Error: Dimensions of the problem should be at least 1." << endl;
        return 1;
    }
    else if(maxIter <= 0){
        cout << "Error : the amount of iterations should be at least greater than 1." << endl;
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);
    /*
     *
     * EFFICIENCY COUNTS HERE MAYBE WE CAN ASSOCIATE OBJ FUNCTIONS TO NUMBERS
     * IN THE MENU AND COMPARE INTEGERS INSTEAD OF STRINGS ( COMPUTATIONALLY CHEAPER).
     *
    Random value generation should be set according to the objective function used...
    to be fixed later... when we check for argv of the obj function...

    we make if statements and use some buitl in c++ compare fct...
    to compare the argv[3] to the obj functions we have.. (comparing strings...)
    */

    /*
    if(strcmp(argv[3],"QuadraticFunction") == 0){
        cout << "QuadraticFunction selected." << endl;
    }
    else if(strcmp(argv[3],"SphereFunction") == 0){
        cout << "SphereFunction selected." << endl;
    }
    else if(strcmp(argv[3],"RastriginFunction") == 0){
        cout << "RastriginFunction selected." << endl;
    }
    else if(strcmp(argv[3],"RosenbrockFunction") == 0){
        cout << "RosenbrockFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GriewankFunction") == 0){
        cout << "GriewankFunction selected." << endl;
    }
    else if(strcmp(argv[3],"AckleyFunction") == 0){
        cout << "AckleyFunction selected." << endl;
    }
    else if(strcmp(argv[3],"SchwefelFunction") == 0){
        cout << "SchwefelFunction selected." << endl;
    }
    else if(strcmp(argv[3],"MichalewiczFunction") == 0){
        cout << "MichalewiczFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GeneralizedPenalizedFunction") == 0){
        cout << "GeneralizedPenalizedFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GeneralizedSchafferFunction") == 0){
        cout << "GeneralizedSchafferFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GeneralizedRastriginFunction") == 0){
        cout << "GeneralizedRastriginFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GeneralizedGriewankFunction") == 0){
        cout << "GeneralizedGriewankFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GeneralizedWeierstrassFunction") == 0){
        cout << "GeneralizedWeierstrassFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GeneralizedSchwefelFunction") == 0){
        cout << "GeneralizedSchwefelFunction selected." << endl;
    }
    else if(strcmp(argv[3],"GeneralizedRotatedHyperEllipsoidFunction") == 0){
        cout << "GeneralizedRotatedHyperEllipsoidFunction selected" << endl;
    }
    else {
        cout << "Error: ObjectiveFunction selected is not available." << endl;
        return 1;
    }
    */

    // Vector to fill the swarm particles inside; maybe change it to dynamic array?
    vector<Particle> swarm;

    // Initialize the particles of the swarm.
    for (int i = 0; i < numOfParticles; ++i) {
        Particle p(dimensions);

        for(int N = 0 ; N < dimensions; N++){
            // Initialize N-dimensional postisions of a particle.
            p.setPositionAtIndex(N, dis(gen));
            // Initialize N-dimensional velocities of a particle.
            p.setVelocityAtIndex(N, dis(gen));
            // Initialize N-dimensional best postisions of a particle.
            p.setBestPositionAtIndex(N, p.getPosAtIndex(N));

        }

        // Initialize the fitness value of a particle based on an objective function.

        // here we must set back the class variables to private &
        // make some fct that returns a pointer to the array of the positions of the particle or fix the obj fct internally.
        p.setFitness(ObjectiveFunction::SphereOne(p.getPosition(),dimensions));
        p.setBestFitness(p.getFitness());

        swarm.emplace_back(p);
    }


    // Printing for Testing...

    /*
    for (int i = 0; i < numOfParticles; ++i) {

        cout << "Particle " << i << " : Position 1 : " << swarm[i].getPosAtIndex(0) <<
        " Position 2 : " << swarm[i].getPosAtIndex(1) << " Velocity 1 : " << swarm[i].getVelocityAtIndex(0) <<
        " Velocity 2 : " << swarm[i].getVelocityAtIndex(1) << " Fitness : " << swarm[i].getFitness() << endl;
    }
    */

    // Best global fitness value for optimization :
    double bestfitness_global = 100000;
    double *x_best_global = new double[dimensions];
    // Initialize all elements to 0
    std::fill(x_best_global, x_best_global + dimensions, 0.0);

    //another random number generator for the range [0, 1] for r1,r2
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_real_distribution<double> dis2(2.0, 5.0);

    // Generate and print random numbers
    double randomNum2 = dis2(gen2);

    //Algorithm Implemetation.
    for (int t = 0; t < maxIter; t++){

        for (int j = 0; j < numOfParticles; j++){
            for(int d = 0 ; d < dimensions; d++){

                // Important; i read in a paper about the r1, r2; we should try U[-1,1] not only U[0,1]

                // UPDATING THE NEW VELOCITY
                swarm[j].setVelocityAtIndex(d,( inertiaWeight*(swarm[j].getVelocityAtIndex(d)) + c1*(swarm[j].getBestPosAtIndex(d) - swarm[j].getPosAtIndex(d))*dis2(gen2)
                                                               + c2*(x_best_global[d] - swarm[j].getPosAtIndex(d))*dis2(gen2)));

                // UPDATING THE NEW POSITION
                swarm[j].setPositionAtIndex(d,(swarm[j].getPosAtIndex(d) + swarm[j].getVelocityAtIndex(d)));

            }

            /// ALSO WE must recheck that paper and the max vel ; min vel stuff; could be useful for

            swarm[j].setFitness(ObjectiveFunction::SphereOne(swarm[j].getPosition(),dimensions));

            if(swarm[j].getFitness() < swarm[j].getBestFitness()){
                swarm[j].setBestFitness(swarm[j].getFitness());


                for (int dd = 0; dd < dimensions ; dd++){ // we can make a fct instead to copy arrays..
                    swarm[j].setBestPositionAtIndex(dd,swarm[j].getPosAtIndex(dd));
                }
            }

            if(swarm[j].getBestFitness() < bestfitness_global){
                cout << swarm[j].getBestFitness() << endl;
                bestfitness_global = swarm[j].getBestFitness();
                for (int dd = 0; dd < dimensions ; dd++){
                    x_best_global[dd] = swarm[j].getBestPosAtIndex(dd);
                }
            }
        }

    }

    cout << "Global fitness : "<<  bestfitness_global << endl;
    for(int dd = 0; dd < dimensions ; dd++){
        cout << "Position " << dd << " : " << x_best_global[dd] << endl;
    }

    delete[] x_best_global;
    return 0;

}

/*
FIND SOME GOOD COMPILER FLAGS TO USE WHEN WE COMPILE THE CODE...
*/