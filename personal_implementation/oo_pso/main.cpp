#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include "Particle.hpp"
#include "PSO.hpp"

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
    T Griewank(const std::vector<T>& x) // more particles needed
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

    template <typename T>
    T Rastrigin(const std::vector<T>& x) // more particles needed
    {
        T result = 0;
        for (const auto& xi : x) {
            result += xi * xi - 10 * std::cos(2 * M_PI * xi) + 10;
        }
        return result;
    }
}

int main()
{   
    size_t D;
    std::cout << "\nEnter the problem dimension:\n\n ";
    std::cin >> D;

    std::string functionName;
    std::cout << "\nEnter the function name:\n -Rosenbrock (HARD, flat global minimun region) \n -Sphere (EASY) \n -Ackley (MEDIUM, many local minima)\n -Griewank (VERY HARD, many local minima) \n -Rastrigin (VERY HARD, many local minima)\n\n ";
    std::cin >> functionName;



    std::function<double(const std::vector<double>&)> fun;
    using ParticleType = Particle<double, decltype(fun)>;
    using PSOType = PSO<double, int, decltype(fun), ParticleType>;

    std::vector<double> exact_solution; // exact solution of the problem

    if (functionName == "Rosenbrock" || functionName == "rosenbrock" || functionName == "ROSENBROCK")
    {
        fun = Function::Rosenbrock<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(1.0);
    } else if (functionName == "Sphere" || functionName == "sphere" || functionName == "SPHERE")
    {
        fun = Function::Sphere<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    } else if (functionName == "Ackley" || functionName == "ackley" || functionName == "ACKLEY")
    {
        fun = Function::Ackley<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    } else if (functionName == "Griewank" || functionName == "griewank" || functionName == "GRIEWANK")
    {
        fun = Function::Griewank<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    } else if (functionName == "Rastrigin" || functionName == "rastrigin" || functionName == "RASTRIGIN")
    {
        fun = Function::Rastrigin<double>;
        for (size_t i = 0; i < D; ++i)
            exact_solution.emplace_back(0.0);
    }
    else
    {
        std::cerr << "Invalid function name. Exiting." << std::endl;
        return 1;
    }

    size_t max_iter, num_particles;
    double tol;
    std::cout << "\nEnter the maximum number of iterations:\n\n ";
    std::cin >> max_iter;
    std::cout << "\nEnter the tolerance: \n\n ";
    std::cin >> tol;
    std::cout << "\nEnter the number of particles: \n\n ";
    std::cin >> num_particles;

    PSOType pso;

    {
        using namespace std::chrono;
        std::cout << "\n PSO initialization ..." << std::endl;
        auto start = high_resolution_clock::now();
        pso.setMaxIter(max_iter);
        pso.setTol(tol);
        pso.setNParticles(num_particles);
        pso.setFunction(fun);
        pso.setD(D);
        pso.setExactSolution(exact_solution);
        pso.setParticles();
        pso.info(functionName); // passing the function name to info method
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        std::cout << "\n Elapsed time for initialization: " << duration.count() << " ms" << std::endl;
    }

    {
        using namespace std::chrono;
        std::cout << "\n PSO solving ..." << std::endl;
        auto start = high_resolution_clock::now();
        pso.solve();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        std::cout << "\n Elapsed time for solving: " << duration.count() << " ms" << std::endl;
    }

    return 0;
}


