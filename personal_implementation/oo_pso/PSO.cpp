#include "PSO.hpp"
#include "Particle.hpp"

constexpr double eps = std::numeric_limits<double>::epsilon();

template <typename T, typename I, typename Fun, typename Obj>
PSO<T, I, Fun, Obj>::PSO(const I& max_iter,
                         const T& w,
                         const T& c1,
                         const T& c2,
                         const I& num_particles,
                         const Fun& fun,
                         const I& D)
    : _max_iter(max_iter)
    , _w(w)
    , _c1(c1)
    , _c2(c2)
    , _num_particles(num_particles)
    , _D(D) 
{
    std::cout << "\n============================================="
              << "\n---------------------------------------------"
              << "\n               PSO algorithm                 " 
              << "\n---------------------------------------------"
              << "\n=============================================" << std::endl;

    for (size_t i = 0; i < _num_particles; ++i) {
        _particles.push_back(Obj(fun, _D));
    }
}

template <typename T, typename I, typename Fun, typename Obj>
const std::vector<Obj>& PSO<T, I, Fun, Obj>::getParticles() const 
{
    return _particles;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::local_best(Obj& particle, const Fun& fun) const 
{
    particle.setValue(fun(particle.getPosition()));

    if (particle.getValue() < particle.getBestValue()) {
        particle.setBestPosition(particle.getPosition());
        particle.setBestValue(particle.getValue());
    }
}

template <typename T, typename I, typename Fun, typename Obj>
std::vector<T> PSO<T, I, Fun, Obj>::getGlobalBest(std::vector<Obj>& particles) const 
{
    size_t best_part_id = 0;
    for (size_t i = 1; i < particles.size(); ++i) {
        if (particles[i].getBestValue() < particles[best_part_id].getBestValue()) {
            best_part_id = i;
        }
    }

    std::vector<T> best = particles[best_part_id].getBestPosition();
    return best;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setGlobalBest(const std::vector<T>& gbp) 
{
    _gbp = gbp;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::info() const {
    std::cout << "\n=============================================" << std::endl;
    std::cout << "Max Iter: " << _max_iter << std::endl;
    std::cout << "Number of Particles: " << _num_particles << std::endl;
    std::cout << "Inertia Weight: " << _w << std::endl;
    std::cout << "Cognitive Parameter: " << _c1 << std::endl;
    std::cout << "Social Parameter: " << _c2 << std::endl;
    std::cout << "=============================================" << std::endl;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::solve(const Fun& fun) {
    for (I it = 0; it < _max_iter; ++it) {
        _gbp = getGlobalBest(_particles);

        std::cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" 
                  << "\nIteration: " << it + 1 
                  << "\n - Initial Best Value : " << fun(_gbp);

        for (size_t p = 0; p < _num_particles; ++p) {
            // std::cout << "Particle " << p + 1 << "\t"
            //           << "Initial Position: (" << _particles[p].getPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ") | "
            //           << "Velocity: (" << _particles[p].getVelocity()[0] << ", " << _particles[p].getVelocity()[1] << ") | "
            //           << "Value: " << _particles[p].getValue() << " | "
            //           << "Best Position: (" << _particles[p].getBestPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ")" << std::endl;

            local_best(_particles[p], fun);

            std::vector<T> r1, r2;
            for (size_t d = 0; d < _D; ++d) 
            {
                r1.emplace_back(_dis(_rng));
                r2.emplace_back(_dis(_rng));
            }

            for (size_t d = 0; d < _D; ++d) 
            {
                _particles[p].getVelocity()[d] = _w * _particles[p].getVelocity()[d] +
                                                 _c1 * r1[d] * (_particles[p].getBestPosition()[d] - _particles[p].getPosition()[d]) +
                                                 _c2 * r2[d] * (_gbp[d] - _particles[p].getPosition()[d]);
            }

            for (size_t d = 0; d < _D; ++d) 
            {
                _particles[p].getPosition()[d] = _particles[p].getPosition()[d] + _particles[p].getVelocity()[d];
            }

            local_best(_particles[p], fun);

            // std::cout << "Particle " << p + 1 << "\t"
            //           << "Final Position: (" << _particles[p].getPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ") | "
            //           << "Velocity: (" << _particles[p].getVelocity()[0] << ", " << _particles[p].getVelocity()[1] << ") | "
            //           << "Value: " << _particles[p].getValue() << " | "
            //           << "Best Position: (" << _particles[p].getBestPosition()[0] << ", " << _particles[p].getBestPosition()[1] << ")" << std::endl;
        }

        std::vector<T> gbp_new = getGlobalBest(_particles);

        _increment = std::abs(fun(gbp_new) - fun(_gbp));

        if (fun(gbp_new) < fun(_gbp))
        {
            setGlobalBest(gbp_new);
            _w = std::min(_w*1.2, 0.9); // correction, if you are doing good, you can go faster
            if (std::abs(_w - 0.9) < eps) { _w *= 0.95; } //if you are going too fast, slow down a little
        } else{
            _w = std::max(_w*0.9, 0.1); // correction, if you are doing bad, you should go slower
            if (std::abs(_w - 0.1) < eps) { _w *= 2; } // if you are going too slow, speed up a little
        }

        std::cout << "\n - Final Best Value   : " << fun(_gbp) 
                  << "\n - Increment          : " << _increment;
    }
    std::cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
}

template class PSO<double, int, std::function<double(const std::vector<double>&)>, Particle<double, std::function<double(const std::vector<double>&)>>>;
