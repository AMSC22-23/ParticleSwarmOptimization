#include <iostream>
#include <vector>
#include <functional>
#include <random>
//#include "Particle.hpp"

constexpr size_t D = 2;

namespace Function {

   constexpr double a = 1.0; // Rosenbrock function parameter
   constexpr double b = 100.0; // Rosenbrock function parameter

    template <typename T>
    T Rosenbrock(const std::vector<T>& x) 
    {
        T result = 0;
        for (int i = 0; i < x.size() - 1; ++i) {
            result += (a - x[i]) * (a - x[i]) + b * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]);
        }
        return result;
    }
}

template <typename T, typename Fun>
class Particle
{
public:

    // constructor
    Particle(const Fun& fun, const auto& D)
    {   
        for (size_t dim = 0; dim < D; ++dim)
        {
            _position.push_back(_dist_position(_rng));
            _velocity.push_back(_dist_velocity(_rng));
        }

        _best_position = _position; // initialize best position to the iniiial position
        _value = fun(_position);
        _best_value = _value; // initialize best value to the initial value
    }

    // setters
    void setPosition(const std::vector<T>& position) { _position = position; }
    void setVelocity(const std::vector<T>& velocity) { _velocity = velocity; }
    void setBestPosition(const std::vector<T>& best_position) { _best_position = best_position; }
    void setValue(const T& value) { _value = value; }
    void setBestValue(const T& best_value) { _best_value = best_value; }


    // getters
   std::vector<T>& getPosition()  { return _position; }
   std::vector<T>& getVelocity()  { return _velocity; }
    const std::vector<T>& getBestPosition() const { return _best_position; }
    const T& getValue() const { return _value; }
    const T& getBestValue() const { return _best_value; }


    void info() const
    {
        std::cout << "\nPosition: ";
        for (const auto& elem : _position)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        std::cout << "Velocity: ";
        for (const auto& elem : _velocity)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        std::cout << "Best Position: ";
        for (const auto& elem : _best_position)
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;

        std::cout << "Value: " << _value << std::endl;
        std::cout << "Best Value: " << _best_value << std::endl;
    }

private:
    std::vector<T> _position;
    std::vector<T> _velocity;
    std::vector<T> _best_position;
    T _value;
    T _best_value;

    std::mt19937_64 _rng{std::random_device{}()};
    std::uniform_real_distribution<T> _dist_position{-5.0, 5.0}; 
    std::uniform_real_distribution<T> _dist_velocity{-1.0, 1.0};

}; 

template <typename T, typename I,  typename Fun, typename Obj>
class PSO
{
public:
    PSO(const auto& max_iter, 
        const auto& w, 
        const auto& c1, 
        const auto& c2, 
        const auto& num_particles, 
        const Fun& fun, 
        const auto& D)
        : 
        _max_iter(max_iter)
        , _w(w)
        , _c1(c1)
        , _c2(c2)
        , _num_particles(num_particles) 
        , _D(D)
    {
        std::cout << "PSO constructor called." << std::endl;

        for (size_t i = 0; i < _num_particles; ++i)
        {
            _particles.push_back(Obj(fun, _D));
        }

    }

   // getters
   const std::vector<Obj>& getParticles() const { return _particles; }

    void local_best(Obj& particle, const Fun& fun) const
    {
        /*
            This method updates the best position of each particle.
        */
        
        particle.setValue(fun(particle.getPosition()));

        if (particle.getValue() < particle.getBestValue()) 
        {
            particle.setBestPosition(particle.getPosition());
            particle.setBestValue(particle.getValue());
        }
    }

    std::vector<T> getGlobalBest(std::vector<Obj>& particles) const
    {
        /*
            This method updates the global best position among all particles.
        */

        // Initialize best position among all particles
        size_t best_part_id = 0;
        for (size_t i = 1; i < particles.size(); ++i) 
        {
            if (particles[i].getBestValue() < particles[best_part_id].getBestValue()) 
            {
                best_part_id = i;
            }
        }

        std::vector<T> best = particles[best_part_id].getBestPosition();

       return best;
    }

    void setGlobalBest(const std::vector<T>& gbp) { _gbp = gbp; }

    // PSO iteration
    void solve(const Fun& fun)
    {   
        for (I it = 0; it < _max_iter; ++it) // looping iters
        {   

            _gbp = getGlobalBest(_particles);

            std::cout << "===============================================" << std::endl;
            std::cout << "It: " << it+1 << " - Initial Best Value: " << fun(_gbp) << std::endl;

            //std::cout << "Iteration: " << it + 1 << std::endl;
            for (size_t p = 0; p < _num_particles; ++p) // looping particles
            {   
            std::cout << "Particle " << p + 1 << "\t"
                      << "Initial Position: (" << _particles[p].getPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ") | "
                      << "Velocity: (" << _particles[p].getVelocity()[0]<< ", " << _particles[p].getVelocity()[1] << ") | "
                      << "Value: " << _particles[p].getValue() << " | "
                      << "Best Position: (" << _particles[p].getBestPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ")" << std::endl;
                
                // compute initial best position for particle p
                local_best(_particles[p], fun);

                // std::vector<T> gbp = globalBest(_particles);

                // random generators
                std::vector<T> r1, r2;
                for (size_t d = 0; d < _D; ++d) // looping dimensions
                {
                    r1.emplace_back(_dis(_rng));
                    r2.emplace_back(_dis(_rng));
                }

                // velocity update
                for (size_t d = 0; d < _D; ++d) // looping dimensions
                {
                    _particles[p].getVelocity()[d] = _w * _particles[p].getVelocity()[d] + 
                                                     _c1 * r1[d] * (_particles[p].getBestPosition()[d] - _particles[p].getPosition()[d]) + 
                                                     _c2 * r2[d] * (_gbp[d] - _particles[p].getPosition()[d]);
                }

                // position update
                for (size_t d = 0; d < _D; ++d) // looping dimensions
                {
                    _particles[p].getPosition()[d] = _particles[p].getPosition()[d] + _particles[p].getVelocity()[d];
                }
        
                // compute final best position for particle p
                local_best(_particles[p], fun);

                std::cout << "Particle " << p + 1 << "\t"
                      << "Final Position: (" << _particles[p].getPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ") | "
                      << "Velocity: (" << _particles[p].getVelocity()[0]<< ", " << _particles[p].getVelocity()[1] << ") | "
                      << "Value: " << _particles[p].getValue() << " | "
                      << "Best Position: (" << _particles[p].getBestPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ")" << std::endl;
            }

            std::vector<T> gbp_new = getGlobalBest(_particles);

            if (fun(gbp_new) < fun(_gbp)) setGlobalBest(gbp_new);

            std::cout << "It: " << it+1 << " - Final Best Value: " << fun(_gbp) << std::endl;

        }
    }

private: 
    I _D{2}; // dimensionality of the problem

    I _max_iter;
    I _num_particles;
    T _w;
    T _c1;
    T _c2;

    std::vector<Obj> _particles;

   std::vector<T> _gbp;

    std::mt19937_64 _rng{std::random_device{}()};
    std::uniform_real_distribution<T> _dis{0.0, 1.0};
};

int main() 
{  
    std::vector<double> x;

    std::mt19937_64 rng{std::random_device{}()};
    std::uniform_real_distribution<double> dist_position{-5.0, 5.0};
    std::uniform_real_distribution<double> dist_velocity{-1.0, 1.0};

    for (int i = 0; i < D; ++i) {
        x.push_back(dist_position(rng));
    }

    // Specify the template arguments when creating std::function
   std::function<double(const std::vector<double>&)> Rosenbrock = Function::Rosenbrock<double>;
   
    std::cout << Function::Rosenbrock<double>(x) << std::endl;
    std::cout << Rosenbrock(x) << std::endl; // function wrapper

   Particle<double, decltype(Rosenbrock)> p(Rosenbrock, D);
   p.info();

   int num_particles = 3;

   std::vector<Particle<double, decltype(Rosenbrock)>> particles;

   for (int i = 0; i < num_particles; ++i) {
      particles.push_back(Particle<double, decltype(Rosenbrock)>(Rosenbrock, D));
   }

   for (size_t i = 0; i < particles.size(); ++i) {
      std::cout << "\nParticle " << i + 1 << std::endl;
      particles[i].info();
   }

   auto instance =  particles[0].getPosition();
   std::cout << "\nPosition: ";
   for (const auto& elem : instance)
   {
      std::cout << elem << " ";
   }

   int max_iter = 5;
   double w = 0.5;
   double c1 = 2;
   double c2 = 2;

   PSO<double, int, decltype(Rosenbrock), Particle<double, decltype(Rosenbrock)>> pso(max_iter, w, c1, c2, num_particles, Rosenbrock, D);

   auto temp = pso.getParticles();
   for (size_t i = 0; i < temp.size(); ++i) {
      std::cout << "\nParticle " << i + 1 << std::endl;
      temp[i].info();
   }

   pso.solve(Rosenbrock);

   return 0;
}
