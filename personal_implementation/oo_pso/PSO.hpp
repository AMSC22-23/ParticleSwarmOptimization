#ifndef PSO_HPP
#define PSO_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cmath>
#include <limits>

template <typename T, typename I, typename Fun, typename Obj>
class PSO {
public:

    // Constructor
    PSO(const I& max_iter,
        const T& tol,
        const T& w,
        const T& c1,
        const T& c2,
        const I& num_particles,
        const Fun& fun,
        const I& D);
    
    PSO();

    // Setters
    void setParticles(); // set particles
    void setGlobalBest(const std::vector<T>& gbp); // set global best position after each iteration
    void setExactSolution(const std::vector<T>& exact_solution); // set exact solution of the problem
    void setFunction(const Fun& fun); // set function to minimize
    void setNParticles(const I& num_particles); // set number of particles
    void setMaxIter(const I& max_iter); // set maximum number of iterations
    void setW(const T& w); // set inertia weight
    void setC1(const T& c1); // set cognitive parameter
    void setC2(const T& c2); // set social parameter
    void setD(const I& D); // set problem dimension
    void setTol(const T& tol); // set tolerance

    // Getters
    const std::vector<Obj>& getParticles() const;
    std::vector<T> getGlobalBest() const;
    const std::vector<T>& getExactSolution() const;
    const Fun& getFunction() const;
    const I& getNParticles() const;
    const I& getMaxIter() const;
    const T& getW() const;
    const T& getC1() const;
    const T& getC2() const;
    const I& getD() const;
    const T& getTol() const;
    

    // Member functions
    void localBest(Obj& particle) const; // auxiliary function to find the local best position of a particle within each iteration
    void solve(); // PSO iteration
    void info(const std::string& fun_name) const; // print info about the PSO object
    const T errorNorm(const std::vector<T>& vec) const; // compute the error norm between the exact solution and the global best position

private:
    I _D{2};
    I _max_iter{1000};
    I _num_particles{10};
    T _w{0.5};
    T _c1{2.0};
    T _c2{2.0};

    std::vector<Obj> _particles; // objects of Particle class

    std::vector<T> _gbp; // global best position

    std::vector<T> _exact_solution; // exact solution of the problem

    T _tol{1e-6}; // tolerance

    Fun _fun; // function to optimize

    std::mt19937_64 _rng{std::random_device{}()};
    std::uniform_real_distribution<T> _dis{0.0, 1.0};
};

#endif // !PSO_HPP