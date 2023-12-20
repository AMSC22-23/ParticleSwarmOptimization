#ifndef PSO_HPP
#define PSO_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>
#include <limits>

using namespace std;

template <typename T, typename I, typename Fun, typename Obj>
class PSO {
public:

    // Constructor
    PSO(const I& swarm_id,
        const I& max_iter,
        const T& tol,
        const T& w,
        const T& c1,
        const T& c2,
        const I& num_particles,
        const Fun& fun,
        const I& D,
        const vector<T>& exact_solution);
    
    PSO();

    // Setters
    void setParticles();                                    // set particles
    void setGlobalBest(const vector<T>& gbp);               // set global best position after each iteration
    void setExactSolution(const vector<T>& exact_solution); // set exact solution of the problem
    void setFunction(const Fun& fun);                       // set function to minimize
    void setNParticles(const I& num_particles);             // set number of particles
    void setMaxIter(const I& max_iter);                     // set maximum number of iterations
    void setW(const T& w);                                  // set inertia weight
    void setC1(const T& c1);                                // set cognitive parameter
    void setC2(const T& c2);                                // set social parameter
    void setD(const I& D);                                  // set problem dimension
    void setTol(const T& tol);                              // set tolerance
    void setId(const I& swarm_id);                          // set swarm id

    // Getters
    const vector<Obj>& getParticles() const;
    vector<T> getGlobalBest() const;
    const vector<T>& getExactSolution() const;
    const Fun& getFunction() const;
    const I& getNParticles() const;
    const I& getMaxIter() const;
    const T& getW() const;
    const T& getC1() const;
    const T& getC2() const;
    const I& getD() const;
    const T& getTol() const;
    const I& getId() const;

    // Member functions
    void localBest(Obj& particle) const;            // auxiliary function to find the local best position of a particle within each iteration
    const T solve();                                   // PSO iteration
    void info(const string& fun_name) const;        // print info about the PSO object
    const T errorNorm(const vector<T>& vec) const;  // compute the error norm between the exact solution and the global best position
    void init(const I& swarm_id, 
              const I& max_iter,
              const T& tol,
              const T& w,
              const T& c1,
              const T& c2,
              const I& num_particles,
              const Fun& fun,
              const I& D,
              const vector<T>& exact_solution);   // init the swarm

private:
    I _max_iter{1000};
    T _tol{1e-6};
    T _w{0.5};
    T _c1{2.0};
    T _c2{2.0};
    I _num_particles{10};
    Fun _fun;
    I _D{2};
    I _id{0};

    vector<Obj> _particles;    // objects of Particle class
    vector<T> _gbp;            // global best position
    vector<T> _exact_solution; // exact solution of the problem

    mt19937_64 _rng{random_device{}()};
    uniform_real_distribution<T> _dis{0.0, 1.0};
};

#endif