#include <iostream>
#include <vector>
#include <functional>
#include <random>

using elem_t = double;

template <typename T>
T Rosenbrock2D(const std::vector<T>& x, const T& a, const T& b) {
    return (a - x[0]) * (a - x[0]) + b * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
}

struct Particle {
    using elem_t = double;
    using position_t = std::vector<elem_t>; // of two elements
    using velocity_t = std::vector<elem_t>;
    position_t position;
    velocity_t velocity;
    position_t best_position;
    elem_t value;
    elem_t best_value;
};

std::vector<elem_t> global_best(const std::vector<Particle>& particles) {
    // Initialize best position among all particles
    size_t best_particle_index = 0;
    for (size_t i = 1; i < particles.size(); ++i) {
        if (particles[i].value < particles[best_particle_index].value) {
            best_particle_index = i;
        }
    }

    const std::vector<elem_t> initial_best_position = particles[best_particle_index].position;

    // Print the best position
    /*
    std::cout << "Best Position: (" << initial_best_position[0] << ", "
              << initial_best_position[1] << ") | Particle " << best_particle_index + 1 << std::endl;
    */

    return initial_best_position;
}

void local_best(Particle& particle, const double& a, const double& b) {
    // Computing best position for each particle during each iteration
    particle.value = Rosenbrock2D(particle.position, a, b);

    if (particle.value < particle.best_value) {
        particle.best_position = particle.position;
        particle.best_value = particle.value;
    }
}

std::vector<Particle> PSO_init(const size_t& num_particles, const double& a, const double& b) {
    using elem_t = double;

    // Bounds for p_dimensionality = 2
    const std::vector<std::pair<elem_t, elem_t>> position_bounds = {{-5.0, 5.0}, {-5.0, 5.0}};
    const std::vector<std::pair<elem_t, elem_t>> velocity_bounds = {{-1.0, 1.0}, {-1.0, 1.0}};

    // Initialize particles with random positions and velocities
    std::vector<Particle> particles(num_particles); // reserve space for particles

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<elem_t> dis_position_x(position_bounds[0].first, position_bounds[0].second);
    std::uniform_real_distribution<elem_t> dis_position_y(position_bounds[1].first, position_bounds[1].second);
    std::uniform_real_distribution<elem_t> dis_velocity_x(velocity_bounds[0].first, velocity_bounds[0].second);
    std::uniform_real_distribution<elem_t> dis_velocity_y(velocity_bounds[1].first, velocity_bounds[1].second);

    for (size_t i = 0; i < particles.size(); ++i) {
        // Generate random positions
        particles[i].position = {dis_position_x(gen), dis_position_y(gen)};
        particles[i].best_position = particles[i].position;

        // Generate random velocity
        particles[i].velocity = {dis_velocity_x(gen), dis_velocity_y(gen)};

        // Calculate Rosenbrock value for each particle
        particles[i].value = Rosenbrock2D(particles[i].position, a, b);
        particles[i].best_value = particles[i].value;

        // Print the generated positions, velocity, and value (for demonstration purposes)
        std::cout << "Particle " << i + 1 << "\t"
                  << "Position: (" << particles[i].position[0] << ", " << particles[i].position[1] << ") | "
                  << "Velocity: (" << particles[i].velocity[0] << ", " << particles[i].velocity[1] << ") | "
                  << "Value: " << particles[i].value << std::endl;
    }

    return particles;
}

int main() {

    using elem_t = double;

    // Rosenbrock function parameters
    elem_t a = 1.0;
    elem_t b = 100.0;

    // PSO parameters
    // size_t p_dimensionality = 2; // problem dimensionality --> to be addressed later
    size_t num_particles = 10;
    size_t max_iter = 100;
    elem_t w = 0.5;
    elem_t c1 = 0.2;
    elem_t c2 = 0.8;

    std::cout << "===============================================" << std::endl;
    
    // PSO initialization
    std::vector<Particle> particles = PSO_init(num_particles, a, b);

    // PSO iteration
    std::vector<elem_t> gbp = global_best(particles);

    std::cout << "\nBest Initial Position: (" << gbp[0] << ", "
              << gbp[1] << ")" << std::endl;
    std::cout << "\n===============================================" << std::endl;
    
    std::cout << "=================PSO algorithm=================" << std::endl;

    gbp = global_best(particles);
    // PSO iteration
    for (size_t i = 0; i < max_iter; ++i) {

        std::cout << "===============================================" << std::endl;
        std::cout << "It: " << i+1 << "; SBP: (" << gbp[0] << ", "
                      << gbp[1] << "); SBV: " << Rosenbrock2D(gbp, a, b) << std::endl;

        for (size_t p = 0; p < particles.size(); ++p) {
            // Update best position for each particle
            local_best(particles[p], a, b);

            // std::cout << "Particle " << p + 1 << "\t"
            //           << "Initial Position: (" << particles[p].position[0] << ", " << particles[p].position[1] << ") | "
            //           << "Velocity: (" << particles[p].velocity[0] << ", " << particles[p].velocity[1] << ") | "
            //           << "Value: " << particles[p].value << " | "
            //           << "Best Position: (" << particles[p].best_position[0] << ", " << particles[p].best_position[1] << ")" << std::endl;

            // Update velocity
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<elem_t> dis(0.0, 1.0);

            std::vector<elem_t> r1 = {dis(gen), dis(gen)};
            std::vector<elem_t> r2 = {dis(gen), dis(gen)};

            // Element-wise operations for vector addition and subtraction
            particles[p].velocity[0] = w * particles[p].velocity[0] +
                                       r1[0] * c1 * (particles[p].best_position[0] - particles[p].position[0]) +
                                       r2[0] * c2 * (gbp[0] - particles[p].position[0]);

            particles[p].velocity[1] = w * particles[p].velocity[1] +
                                       r1[1] * c1 * (particles[p].best_position[1] - particles[p].position[1]) +
                                       r2[1] * c2 * (gbp[1] - particles[p].position[1]);

            // Update position
            particles[p].position[0] = particles[p].position[0] + particles[p].velocity[0];
            particles[p].position[1] = particles[p].position[1] + particles[p].velocity[1];

            local_best(particles[p], a, b);

            // Print the generated positions, velocity, and value (for demonstration purposes)
            // std::cout << "Particle " << p + 1 << "\t"
            //           << "Final Position: (" << particles[p].position[0] << ", " << particles[p].position[1] << ") | "
            //           << "Velocity: (" << particles[p].velocity[0] << ", " << particles[p].velocity[1] << ") | "
            //           << "Value: " << particles[p].value << " | "
            //           << "Best Position: (" << particles[p].best_position[0] << ", " << particles[p].best_position[1] << ")" << std::endl;
        }

        std::vector<elem_t> gbp_new = global_best(particles);

        if (Rosenbrock2D(gbp_new, a, b) < Rosenbrock2D(gbp, a, b)) {
            gbp = gbp_new;
        } else {
            gbp = gbp;
        }

        std::cout << "It: "<< i+1 << "; EBP: (" << gbp[0] << ", "
                      << gbp[1] << "); EBV: " << Rosenbrock2D(gbp, a, b) << std::endl;
    }
    
    
    return 0;
}

