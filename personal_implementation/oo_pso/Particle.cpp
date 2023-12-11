#include "Particle.hpp"

template <typename T, typename Fun>
Particle<T, Fun>::Particle(const Fun& fun, const size_t& D) : _D(D)
{
    for (size_t dim = 0; dim < _D; ++dim) {
        _position.push_back(_dist_position(_rng));
        _velocity.push_back(_dist_velocity(_rng));
    }

    _best_position = _position;
    _value = fun(_position);
    _best_value = _value;
}

template <typename T, typename Fun>
void Particle<T, Fun>::setPosition(const std::vector<T>& position) 
{
    _position = position;
}

template <typename T, typename Fun>
void Particle<T, Fun>::setVelocity(const std::vector<T>& velocity) 
{
    _velocity = velocity;
}

template <typename T, typename Fun>
void Particle<T, Fun>::setBestPosition(const std::vector<T>& best_position) 
{
    _best_position = best_position;
}

template <typename T, typename Fun>
void Particle<T, Fun>::setValue(const T& value) 
{
    _value = value;
}

template <typename T, typename Fun>
void Particle<T, Fun>::setBestValue(const T& best_value) 
{
    _best_value = best_value;
}

template <typename T, typename Fun>
std::vector<T>& Particle<T, Fun>::getPosition() 
{
    return _position;
}

template <typename T, typename Fun>
std::vector<T>& Particle<T, Fun>::getVelocity() 
{
    return _velocity;
}

template <typename T, typename Fun>
const std::vector<T>& Particle<T, Fun>::getBestPosition() const 
{
    return _best_position;
}

template <typename T, typename Fun>
const T& Particle<T, Fun>::getValue() const 
{
    return _value;
}

template <typename T, typename Fun>
const T& Particle<T, Fun>::getBestValue() const 
{
    return _best_value;
}

template <typename T, typename Fun>
void Particle<T, Fun>::info() const 
{
    std::cout << "Position: ";
    for (const auto& elem : _position) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Velocity: ";
    for (const auto& elem : _velocity) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Best Position: ";
    for (const auto& elem : _best_position) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Value: " << _value << std::endl;
    std::cout << "Best Value: " << _best_value << std::endl;
}


template class Particle<double, std::function<double(const std::vector<double>&)>>;
