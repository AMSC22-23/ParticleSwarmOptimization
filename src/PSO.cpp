#include "PSO.hpp"
#include "Particle.hpp"
#include <limits>
#include <omp.h>
#include <chrono>

using namespace chrono;
using namespace std;

constexpr double eps = numeric_limits<double>::epsilon();

template <typename T, typename I, typename Fun, typename Obj>
PSO<T, I, Fun, Obj>::PSO(const I& swarm_id, 
                         const I& max_iter,
                         const T& tol,
                         const T& w,
                         const T& c1,
                         const T& c2,
                         const I& num_particles,
                         const Fun& fun,
                         const I& D,
                         const vector<T>& exact_solution)
    : _max_iter(max_iter)
    , _tol(tol)
    , _w(w)
    , _c1(c1)
    , _c2(c2)
    , _num_particles(num_particles)
    , _fun(fun)
    , _D(D)
    , _id(swarm_id)
    , _exact_solution(exact_solution)
{
init(swarm_id, max_iter, tol, w, c1, c2, num_particles, fun, D, exact_solution);
}
template <typename T, typename I, typename Fun, typename Obj>
PSO<T, I, Fun, Obj>::PSO() 
{

}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setParticles() 
{
    for (int p = 0; p < _num_particles; ++p) 
    {
        _particles.emplace_back(Obj(_fun, _D));
    }
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setGlobalBest(const vector<T>& gbp) 
{
    _gbp = gbp;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setExactSolution(const vector<T>& exact_solution) 
{
    _exact_solution = exact_solution;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setFunction(const Fun& fun) 
{
    _fun = fun;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setNParticles(const I& num_particles) 
{
    _num_particles = num_particles;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setMaxIter(const I& max_iter) 
{
    _max_iter = max_iter;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setW(const T& w) 
{
    _w = w;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setC1(const T& c1) 
{
    _c1 = c1;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setC2(const T& c2) 
{
    _c2 = c2;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setD(const I& D) 
{
    _D = D;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setTol(const T& tol) 
{
    _tol = tol;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::setId(const I& swarm_id) 
{
    _id = swarm_id;
}

template <typename T, typename I, typename Fun, typename Obj>
const vector<Obj>& PSO<T, I, Fun, Obj>::getParticles() const 
{
    return _particles;
}

template <typename T, typename I, typename Fun, typename Obj>
vector<T> PSO<T, I, Fun, Obj>::getGlobalBest() const 
{
   size_t best_part_id = 0;
    for (size_t i = 1; i < _particles.size(); ++i) {
        if (_particles[i].getBestValue() < _particles[best_part_id].getBestValue()) {
            best_part_id = i;
        }
    }
//----------------------------------------------------------------------------------------------
// Race condition when writing to best_part_id.
// In order to avoid it, we use first have each thread compute their own best_value 
// Then I a critical section, one thread compares the best_value of each thread and updates best_part_id
// (The overhead of parallelizing this is not worth it)
//----------------------------------------------------------------------------------------------

/*    size_t best_part_id = 0;
    double best_value = _particles[best_part_id].getBestValue();

    #pragma omp parallel for
    for (size_t i = 1; i < _particles.size(); ++i){
        double temp_value = _particles[i].getBestValue();
        #pragma omp critical 
        {
            if (temp_value < best_value) {
                best_value = temp_value;
                best_part_id = i;
            }
        }
    } */

    vector<T> best = _particles[best_part_id].getBestPosition();
    return best;
}

template <typename T, typename I, typename Fun, typename Obj>
const vector<T>& PSO<T, I, Fun, Obj>::getExactSolution() const 
{
    return _exact_solution;
}

template <typename T, typename I, typename Fun, typename Obj>
const Fun& PSO<T, I, Fun, Obj>::getFunction() const 
{
    return _fun;
}

template <typename T, typename I, typename Fun, typename Obj>
const I& PSO<T, I, Fun, Obj>::getNParticles() const 
{
    return _num_particles;
}

template <typename T, typename I, typename Fun, typename Obj>
const I& PSO<T, I, Fun, Obj>::getMaxIter() const 
{
    return _max_iter;
}

template <typename T, typename I, typename Fun, typename Obj>
const T& PSO<T, I, Fun, Obj>::getW() const 
{
    return _w;
}

template <typename T, typename I, typename Fun, typename Obj>
const T& PSO<T, I, Fun, Obj>::getC1() const 
{
    return _c1;
}

template <typename T, typename I, typename Fun, typename Obj>   
const T& PSO<T, I, Fun, Obj>::getC2() const 
{
    return _c2;
}

template <typename T, typename I, typename Fun, typename Obj>
const I& PSO<T, I, Fun, Obj>::getD() const 
{
    return _D;
}

template <typename T, typename I, typename Fun, typename Obj>
const T& PSO<T, I, Fun, Obj>::getTol() const 
{
    return _tol;
}

template <typename T, typename I, typename Fun, typename Obj>
const I& PSO<T, I, Fun, Obj>::getId() const 
{
    return _id;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::init(const I& swarm_id, 
                               const I& max_iter,
                               const T& tol,
                               const T& w,
                               const T& c1,
                               const T& c2,
                               const I& num_particles,
                               const Fun& fun,
                               const I& D, 
                               const vector<T>& exact_solution)
{
    auto start = high_resolution_clock::now();
    setId(swarm_id);
    setMaxIter(max_iter);
    setTol(tol);
    setNParticles(num_particles);
    setFunction(fun);
    setD(D);
    setExactSolution(exact_solution);
    setParticles();
    //info(functionName); // passing the function name to info method
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << " ms for initialization \n" << endl;
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::localBest(Obj& particle) const 
{
    particle.setValue(_fun(particle.getPosition()));

    if (particle.getValue() < particle.getBestValue()) {
        particle.setBestPosition(particle.getPosition());
        particle.setBestValue(particle.getValue());
    }
}

template <typename T, typename I, typename Fun, typename Obj>
const T PSO<T, I, Fun, Obj>::solve() {
    for (I it = 0; it < _max_iter; ++it) {
        _gbp = getGlobalBest();
 
        //omp_set_num_threads(8);
        //int num_threads=omp_get_num_threads(); 
        #pragma omp parallel for
        for (int p = 0; p < _num_particles; ++p) 
        {  
            localBest(_particles[p]);
            vector<T> r1, r2;
            for (int d = 0; d < _D; ++d) 
            {
                r1.emplace_back(_dis(_rng));
                r2.emplace_back(_dis(_rng));
            }
            for (int d = 0; d < _D; ++d) 
            {
                _particles[p].getVelocity()[d] = _w * _particles[p].getVelocity()[d] +
                                                _c1 * r1[d] * (_particles[p].getBestPosition()[d] - _particles[p].getPosition()[d]) +
                                                _c2 * r2[d] * (_gbp[d] - _particles[p].getPosition()[d]);
            }
            for (int d = 0; d < _D; ++d) 
            {
                _particles[p].getPosition()[d] = _particles[p].getPosition()[d] + _particles[p].getVelocity()[d];
            }
            localBest(_particles[p]);
        }
        vector<T> gbp_new = getGlobalBest();

        if (_fun(gbp_new) < _fun(_gbp))
        {
            setGlobalBest(gbp_new);
            _w = min(_w*1.2, 0.9); // correction, if you are doing good, you can go faster
            if (abs(_w - 0.9) < eps) { _w *= 0.95; } //if you are going too fast, slow down a little
        } else {
            _w = max(_w*0.9, 0.1); // correction, if you are doing bad, you should go slower
            if (abs(_w - 0.1) < eps) { _w *= 2; } // if you are going too slow, speed up a little
        }

        if (errorNorm(_gbp) < _tol)
        {
            cout << "\n Swarm "<< _id << " --> Convergence achieved in " << it + 1 << " iterations" << endl;
            return gbp_new.back();
        };

        if (it == _max_iter - 1)
        {
            cout << "\n Maximum number of iterations reached" << endl;
            cout << "\n Tolerance achieved: " << errorNorm(_gbp) << endl;
            return gbp_new.back();
        }
    }
}

template <typename T, typename I, typename Fun, typename Obj>
void PSO<T, I, Fun, Obj>::info(const string& fun_name) const {
    cout << "\n============================================="
    << "\n               PSO algorithm                 " 
    << "\n=============================================" << endl;  
    cout << "\n=============================================" << endl;
    cout << " Function            : " << fun_name << endl;
    cout << " Problem Dimension   : " << _D << endl;
    cout << " Max Iter            : " << _max_iter << endl;
    cout << " Tolerance           : " << _tol << endl;
    cout << " Number of Particles : " << _num_particles << endl;
    cout << " Inertia Weight      : " << _w << endl;
    cout << " Cognitive Parameter : " << _c1 << endl;
    cout << " Social Parameter    : " << _c2 << endl;
    cout << "=============================================" << endl;
}

template <typename T, typename I, typename Fun, typename Obj>
const T PSO<T, I, Fun, Obj>::errorNorm(const vector<T>& vec) const
{
    T norm = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        norm += (vec[i] - _exact_solution[i]) * (vec[i] - _exact_solution[i]);
    }
    return sqrt(norm);
}

template class PSO<double, int, function<double(const vector<double>&)>, Particle<double, function<double(const vector<double>&)>>>;