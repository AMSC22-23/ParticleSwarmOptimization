#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include "Particle.hpp"
#include "PSO.hpp"

constexpr size_t D = 42; // problem dimension

namespace Function 
{

    constexpr double aR = 1.0; // Rosenbrock function parameter
    constexpr double bR = 100.0; // Rosenbrock function parameter

    constexpr double aA = 20.0; // Ackley function parameter
    constexpr double bA = 0.2;  // Ackley function parameter
    constexpr double cA = 2 * M_PI; // Ackley function parameter

    template <typename T>
    T Rosenbrock(const std::vector<T>& x) // most difficult function, suitable for testing flatness of the regione of global minima
    {
        T result = 0;
        for (int i = 0; i < x.size() - 1; ++i) {
            result += (aR - x[i]) * (aR - x[i]) + bR * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]);
        }
        return result;
    }

    template <typename T>
    T Sphere(const std::vector<T>& x) // very easy convex function
    {
        /*
            Problems for high dimensions
        */
        T result = 0;
        for (const auto& xi : x) {
            result += xi * xi;
        }
        return result;
    }

    template <typename T>
    T Ackley(const std::vector<T>& x) // medium difficulty function, good for local minima
    {
        T sum1 = 0;
        T sum2 = 0;

        for (const auto& xi : x) {
            sum1 += xi * xi;
            sum2 += std::cos(cA * xi);
        }

        T term1 = -aA * std::exp(-bA * std::sqrt(sum1 / x.size()));
        T term2 = -std::exp(sum2 / x.size());

        return term1 + term2 + aA + std::exp(1.0);
    }

    template <typename T>
    T Griewank(const std::vector<T>& x)
    {
        T sum = 0;
        T prod = 1;

        for (size_t i = 0; i < x.size(); ++i)
        {
            sum += x[i] * x[i] / 4000.0;
            prod *= std::cos(x[i] / std::sqrt(i + 1));
        }

        return 1.0 + sum - prod;
    }
}

int main() 
{  
    std::function<double(const std::vector<double>&)> fun = Function::Ackley<double>; // choose the function to minimize
    using ParticleType = Particle<double, decltype(fun)>;
    using PSOType = PSO<double, int, decltype(fun), ParticleType>;

    size_t max_iter = 2000;     // maximum number of iterations
    double w = 0.5;             // inertia weight, how much the previous velocity is taken into account
    double c1 = 2;              // cognitive parameter, how much the particle remembers its best position
    double c2 = 2;              // social parameter, how much the particle remembers the best position of the swarm
    size_t num_particles = 20;  // number of particles

    /*
        1st hyperparameter tuning attempt: (see PSO.solve() for the algorithm) --> more suitable for non-convex functions
            - if the best position of the swarm is not updated for one iteration
              the inertia weight is decreased
            -  else the inertia weight is increased

        2d approach: maybe different bounds for initial position and velocity (?)
    */

    // std::vector<ParticleType> particles;

    // for (size_t i = 0; i < num_particles; ++i) {
    //     std::cout << "Particle: " << i + 1 << std::endl;
    //     particles.emplace_back(ParticleType(fun, D));
    //     particles[i].info();
    //     std::cout << std::endl;
    // }

    PSOType pso(max_iter, w, c1, c2, num_particles, fun, D);

    pso.solve(fun);

    pso.info();

    return 0;
}


