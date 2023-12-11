#ifndef PSO_HPP
#define PSO_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <limits>

template <typename T, typename I, typename Fun, typename Obj>
class PSO {
public:

    // Constructor
    PSO(const I& max_iter,
        const T& w,
        const T& c1,
        const T& c2,
        const I& num_particles,
        const Fun& fun,
        const I& D);
    
    PSO() = default;

    // Setters
    void setGlobalBest(const std::vector<T>& gbp); // set global best position after each iteration

    // Getters
    const std::vector<Obj>& getParticles() const;
    std::vector<T> getGlobalBest(std::vector<Obj>& particles) const;

    // Member functions
    void local_best(Obj& particle, const Fun& fun) const;
    void solve(const Fun& fun); // PSO iteration
    void info() const;

private:
    I _D{2};
    I _max_iter;
    I _num_particles;
    T _w;
    T _c1;
    T _c2;

    std::vector<Obj> _particles; // objects of Particle class

    std::vector<T> _gbp; // global best position

    T _increment {1.0}; // increment

    std::mt19937_64 _rng{std::random_device{}()};
    std::uniform_real_distribution<T> _dis{0.0, 1.0};
};

#endif // !PSO_HPP