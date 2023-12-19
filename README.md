# Particle Swarm Optimization (PSO) Project
Implementation of a Particle Swarm Optimization simulation by Hanna Kamil, Hugot Simon and Zhou Fude; for the Advanced Methods for Scientific Computing course by Prof.Formaggia at Politecnico di Milano 

## 1. Introduction

Particle Swarm Optimization (PSO) is a computational method based on a meta-heuristic method that optimizes a problem by iteratively trying to improve a candidate solution with regard to a given measure of quality. It's interesting because it's inspired by the social behavior of bird flocking or fish schooling.

## 2. Particle Swarm Optimization (PSO)

PSO is initialized with a group of random particles (solutions) and then searches for optima by updating generations. In every iteration, each particle is updated by following two "best" values. The first one is the best solution it has achieved so far. This value is the `personal best` of the particle. Another "best" value that is tracked by the particle swarm optimizer is the best value obtained so far by any particle in the population. This best value is a `global best`.

When a particle takes part of the swarm into consideration, it is a local best value. Each particle keeps track of its coordinates in the problem space which are associated with the best solution (fitness) it has achieved so far. When a particle takes all the population as its topological neighbors, the best value is a global one which is obtained so far by any particle in the population.

## 3. Our Implementation

Our project is structured as follows:

- `include/`: Contains the header files for the PSO and Particles classes and for the Functions namespace.
- `src/`: Contains the main file and the implementations of the PSO and Particle classes.
- `visualization/`: Contains a Python script for visualizing the results of the PSO algorithm.

The main classes in our implementation are:

- `PSO`: This class implements the PSO algorithm. It includes methods for initializing the swarm, updating the particle's position and velocity in parallel, according to the following rules. For the particle i and time t, we have: 
        $$ 
        \begin{equation}
        \begin{split}
            v^{t+1}_{i} &= \underbrace{w*v^{t}_{i}}_{inertia component}*\underbrace{c1*r1*(pBest^{t}_{i}-x^{t}_{i})}_{cognitive component}*\underbrace{}_{social component} \\
            x &= x^{t}_{i}+v^{t+1}_{i}
        \end{split}
        \end{equation}
        $$
Where, v is the velocity, x the position, w is the inertia weight that dictates the momentum of the particle, c1 and c2 are the acceleration parameters which are the weights of the cognitive and social componenets in the global update. r1 and r2 are random uniformly distributed variables between 0 and 1. 
- `Particle`: 
- The `Functions` namespace holds the implementation of all the test functions.

## 4. Test Functions and Results

We tested our PSO implementation on several benchmark functions. These functions are commonly used in the field of optimization to evaluate the performance of optimization algorithms.
- Rastrigin (minimum of 0 at $[0,0,...,0,0]^{D}$)
- Rosenbrock (minimum of 0 at $[1,1,...,1,1]^{D}$)
- Ackley (minmum of 0 at $[0,0]^{D}, D_{max}=2$)
- ...

## 5. Compilation and Configuration

To compile the project, you need to have `CMake` and `openMP` installed. You can compile the project by running the following command in the root directory of the project:

```sh
mkdir build && cd build/ 
```
```sh
cmake ..
```
```sh
make
```
```sh
./PSO_EXEC
```