#if defined(_OPENMP)

#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <chrono>

#include "Particle.hpp"
#include "PSO.hpp"
#include "Functions.hpp"

using namespace std; 
using namespace chrono;
using namespace Function;

int main()
{   
    size_t D;
    cout << "\nEnter the problem dimension:\n\n ";
    cin >> D;

    string functionName;

    cout << "\nEnter the function name:\n 1-Rosenbrock (HARD, flat global minimun region) \n 2-Sphere (EASY) \n 3-Ackley (MEDIUM, many local minima)\n 4-Griewank (VERY HARD, many local minima) \n 5-Rastrigin (VERY HARD, many local minima)\n\n ";
    cin >> functionName;

    function<double(const vector<double>&)> fun;
    using ParticleType = Particle<double, decltype(fun)>;
    using PSOType = PSO<double, int, decltype(fun), ParticleType>;

    vector<double> exact_solution; // exact solution of the problem

    if (functionName == "1")
    {
        fun = Function::Rosenbrock<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(1.0);
    } else if (functionName == "2")
    {
        fun = Function::Sphere<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    } else if (functionName == "3")
    {
        fun = Function::Ackley<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    } else if (functionName == "4")
    {
        fun = Function::Griewank<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    } else if (functionName == "5")
    {
        fun = Function::Rastrigin<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    }
    else
    {
        cerr << "Invalid function name. Exiting." << endl;
        return 1;
    }

    size_t max_iter, num_particles;
    double tol;
    cout << "\nEnter the maximum number of iterations:\n\n ";
    cin >> max_iter;
    cout << "\nEnter the tolerance: \n\n ";
    cin >> tol;
    cout << "\nEnter the number of particles: \n\n ";
    cin >> num_particles;

    vector<PSOType> master;

    for (int sub_swarm_id=0; sub_swarm_id < 3; ++sub_swarm_id)
    {
        cout<<"\n Sub-swarm "<<sub_swarm_id<<" init ... "<< endl;
        PSOType pso;
        pso.init(sub_swarm_id,max_iter, tol, 0.5, 2.0, 2.0, num_particles, fun, D, exact_solution);
        master.emplace_back(pso);
    }
    for (PSOType sub_swarm : master)
    {
        cout << "\n PSO solving for swarm "<< sub_swarm.getId() << " ..." << endl;
        auto start = high_resolution_clock::now();
        sub_swarm.solve();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "\n Elapsed time for solving: " << duration.count() << " ms" << endl;
    }
    return 0;
}

#endif