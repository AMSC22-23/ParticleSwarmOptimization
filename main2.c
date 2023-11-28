#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "swarm.hpp"
#include "particle.hpp"

using namespace std;

int main() {

    int numOfParticles = 10;

    // Create a vector of particles
    vector<Particle> swarm;

    // Position vector :
    vector<double> x;
    // Velocity vector :
    vector<double> v;
    // Best position vector :
    vector<double> x_best;
    // Best global position vector :
    vector<double> x_best_global;
    // Fitness value for optimization :
    double fitness;
    // Best fitness value for optimization :
    double bestfitness;
    // Best global fitness value for optimization :
    double bestfitness_global;

    // Initialize the swarm with particles
    for (int i = 0; i < numOfParticles; ++i) {

        // Initialize particle variables (2D) with 2 postisions. 
        x.push_back(((rand() % 2000 - 1000) / 100.0)); // Random values between -10 and 10;
        x.push_back(((rand() % 2000 - 1000) / 100.0)); // Random values between -10 and 10;

        // Initialize particle velocities  (2D) with 2 postisions. 
        v.push_back(x[0] * 0.1); //0.1 + (0.99 - 0.1) * (rand() / static_cast<double>(RAND_MAX));;
        v.push_back(x[1] * 0.1);// 0.1 + (0.99 - 0.1) * (rand() / static_cast<double>(RAND_MAX));;  
 
        //Updating the position.
        x_best.push_back(x[0]);
        x_best.push_back(x[1]);

        x_best_global.push_back(x[0]);
        x_best_global.push_back(x[1]);

        /*
        TO BEST FIXED.... INITIALIZE FUNCTIONS IN THE HEADER FILES WE CREATED...
        FCTS THAT COMPUTE THE OBJECTIVE FCTS... MANY OF THEM...
        */
        //jUST TRYING A QUADRATIC FCT HERE....
        fitness = pow((10 * (x[0] - 1)),2) + pow((20 * (x[1] - 2)),2) ;

        bestfitness = pow((10 * (x_best[0] - 1)),2) + pow((20 * (x_best[1] - 2)),2) ;

        bestfitness_global = pow((10 * (x_best_global[0] - 1)),2) + pow((20 * (x_best_global[1] - 2)),2) ;
;

        Particle p(x,v,x_best,x_best_global,fitness,bestfitness,bestfitness_global);

        swarm.push_back(p);
    }


    /*
    
    Some testing for Getters....

    (NON-INDEXED GETTERS MUST BE FIXED.... THEY HAVE SOME PROBLEMS...THEY DON'T FUNCTION AS WE WANT/ MAYBE REMOVE THEM.....)
    
    */
    for (int i = 0; i < numOfParticles; ++i) {

    cout << "Particle" << i << " :" << endl;

    cout << swarm[i].getFitness() << endl;
    cout << swarm[i].getBestFitness() << endl;
    
    cout << swarm[i].getPosAtIndex(0) << endl;
    cout << swarm[i].getPosAtIndex(1) << endl;

    cout << swarm[i].getVelocityAtIndex(0) << endl;
    cout << swarm[i].getVelocityAtIndex(1) << endl;

    cout << swarm[i].getBestPosAtIndex(0) << endl;
    cout << swarm[i].getBestPosAtIndex(1) << endl;

    
    }

    return 0;
}
