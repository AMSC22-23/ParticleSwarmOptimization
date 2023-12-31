#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>
#include <cmath>

using namespace std;

namespace Function {

    constexpr double aR = 1.0; // Rosenbrock function parameter
    constexpr double bR = 100.0; // Rosenbrock function parameter

    constexpr double aA = 20.0; // Ackley function parameter
    constexpr double bA = 0.2;  // Ackley function parameter
    constexpr double cA = 2 * M_PI; // Ackley function parameter

    template <typename T>
    T Rosenbrock(const vector<T>& x) // most difficult function, suitable for testing flatness of the regione of global minima
    {
        T result = 0;
        for (int i = 0; i < x.size() - 1; ++i) {
            result += (aR - x[i]) * (aR - x[i]) + bR * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]);
        }
        return result;
    }

    template <typename T>
    T Sphere(const vector<T>& x) // very easy convex function
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
    T Ackley(const vector<T>& x) // medium difficulty function, good for local minima
    {
        T sum1 = 0;
        T sum2 = 0;

        for (const auto& xi : x) {
            sum1 += xi * xi;
            sum2 += cos(cA * xi);
        }

        T term1 = -aA * exp(-bA * sqrt(sum1 / x.size()));
        T term2 = -exp(sum2 / x.size());

        return term1 + term2 + aA + exp(1.0);
    }

    template <typename T>
    T Griewank(const vector<T>& x) // more particles needed
    {
        T sum = 0;
        T prod = 1;

        for (size_t i = 0; i < x.size(); ++i)
        {
            sum += x[i] * x[i] / 4000.0;
            prod *= cos(x[i] / sqrt(i + 1));
        }

        return 1.0 + sum - prod;
    }

    template <typename T>
    T Rastrigin(const vector<T>& x) // more particles needed
    {
        T result = 0;
        for (const auto& xi : x) {
            result += xi * xi - 10 * cos(2 * M_PI * xi) + 10;
        }
        return result;
    }

    template <typename T>
        T Shaffer(const std::vector<T>& x)
        {
            T term = 0;
            for (size_t i = 0; i < x.size(); ++i) {
                term += x[i] * x[i];
            }
            T result = 0.5 + (std::sin(std::sqrt(term)) * std::sin(std::sqrt(term)) - 0.5) / ((1 + 0.001 * term) * (1 + 0.001 * term));
            return result;
        }
}


#endif