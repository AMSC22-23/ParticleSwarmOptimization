# Particle Swarm Optimization (PSO) Project
Implementation of a Particle Swarm Optimization simulation by Hanna Kamil, Hugot Simon and Zhou Fude; for the Advanced Methods for Scientific Computing course by Prof.Formaggia at Politecnico di Milano 

## 1. Introduction

Particle Swarm Optimization (PSO) is a computational method based on a meta-heuristic method that optimizes a problem by iteratively trying to improve a candidate solution with regard to a given measure of quality. It's interesting because it's inspired by the social behavior of bird flocking or fish schooling.

## 2. Particle Swarm Optimization (PSO)

PSO is initialized with a group of random particles (solutions) and then searches for optima by updating generations. In every iteration, each particle is updated by following two "best" values. The first one is the best solution it has achieved so far. This value is the `personal best` of the particle. Another "best" value that is tracked by the particle swarm optimizer is the best value obtained so far by any particle in the population. This best value is a `global best`.

When a particle takes part of the swarm into consideration, it is a local best value. Each particle keeps track of its coordinates in the problem space which are associated with the best solution (fitness) it has achieved so far. This value is called `pBest`. When a particle takes all the population as its topological neighbors, the best value is a global one which is obtained so far by any particle in the population. This is called `gBest`.

## 3. Our Implementation

Our project is structured as follows:

- `include/`: Contains the header files for the PSO and ObjectiveFunction classes.
- `src/`: Contains the implementation of the PSO and ObjectiveFunction classes.
- `visualization/`: Contains a Python script for visualizing the results of the PSO algorithm.

The main classes in our implementation are:

- `PSO`: This class implements the PSO algorithm. It includes methods for initializing the swarm, updating the particles, and running the algorithm.
- `ObjectiveFunction`: This class represents the objective function that the PSO algorithm is trying to optimize. It includes methods for evaluating the function and its gradient.

## 4. Test Functions and Results

We tested our PSO implementation on several benchmark functions. These functions are commonly used in the field of optimization to evaluate the performance of optimization algorithms.
- Rastrigin (minimum of 0 at $[0,0,...,0,0]^{D}$)
- Rosenbrock (minimum of 0 at $[1,1,...,1,1]^{D}$)
- Ackley (minmum of 0 at $[0,0]^{D}, D_{max}=2$)
- ...

## 5. Compilation and Configuration

To compile the project, you need to have CMake installed. You can compile the project by running the following command in the root directory of the project:

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
./PSO_EXEC <number_of_particles> <dimension_of_the_problem> <number_of_iterations> <objective_function>
```