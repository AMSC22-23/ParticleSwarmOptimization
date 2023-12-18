#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <cstddef>

using namespace std;

template <typename T, typename Fun>
class Particle {
public:

    // Constructor
    Particle(const Fun& fun, const size_t& D);
    Particle() = default;

    // Setters
    void setPosition(const vector<T>& position);
    void setVelocity(const vector<T>& velocity);
    void setBestPosition(const vector<T>& best_position);
    void setValue(const T& value);
    void setBestValue(const T& best_value);

    // Getters
    vector<T>& getPosition();
    vector<T>& getVelocity();
    const vector<T>& getBestPosition() const;
    const T& getValue() const;
    const T& getBestValue() const;

    // Member function
    void info() const;

private:
    size_t _D{2}; // Problem dimension

    vector<T> _position;
    vector<T> _velocity;
    vector<T> _best_position;
    T _value;
    T _best_value;

    mt19937_64 _rng{random_device{}()};
    uniform_real_distribution<T> _dist_position{-32.0, 32.0}; // to be addressed
    uniform_real_distribution<T> _dist_velocity{-1.0, 1.0}; // to be addressed
};

#endif // !PARTICLE_HPP