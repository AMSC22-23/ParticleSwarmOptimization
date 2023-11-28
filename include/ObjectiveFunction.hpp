#ifndef OBJECTIVEFUNCTION_HPP
#define OBJECTIVEFUNCTION_HPP

#include <vector>

class ObjectiveFunction {
public:
    static double Ackley(const std::vector<double>& position);
    static double Rosenbrock(const std::vector<double>& position);
    static double Rastrigin(const std::vector<double>& position);
};

#endif // OBJECTIVEFUNCTION_HPP