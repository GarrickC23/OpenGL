// #include "Particle/Particle.h"

// Particle::Particle() : x(0), y(0), vx(0), vy(0), life(1.0f), maxLife(1.0f) {}

// void Particle::update(float deltaTime) 
// {
//     // Update position based on velocity
//     x += vy * deltaTime;
//     y += vy * deltaTime;
 
//     // Decrease life
//     life -= deltaTime;

//     // Ensure life does not go below 0
//     if ( life < 0 )
//     {
//         life = 0;
//     }
// }

// float Particle::getX() const { return x; }

// float Particle::getY() const { return y; }

// void Particle::setVelocity(float vx, float vy)
// {
//     this->vx = vx;
//     this->vy = vy;
// }

// bool Particle::isAlive() const
// {
//     return life > 0; 
// }

#include "Particle/Particle.h"

ParticleSystem::ParticleSystem() {
    // Initialize particles
    for(int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position[0] = 0.0f; // X
        particles[i].position[1] = 0.0f; // Y
        particles[i].position[2] = 0.0f; // Z

        particles[i].velocity[0] = 0.0f;
        particles[i].velocity[1] = 0.1f; // Moving up
        particles[i].velocity[2] = 0.0f;

        particles[i].lifeTime = 0.0f;
        particles[i].maxLifeTime = 5.0f; // 5 seconds of life
    }
}

void ParticleSystem::update(float deltaTime) {
    for(int i = 0; i < MAX_PARTICLES; i++) {
        // Update position
        for (int j = 0; j < 3; j++) {
            particles[i].position[j] += particles[i].velocity[j] * deltaTime;
        }

        // Update lifeTime
        particles[i].lifeTime += deltaTime;

        // Reset if the particle has lived its life
        if (particles[i].lifeTime >= particles[i].maxLifeTime) {
            particles[i].position[1] = 0.0f; // Reset Y position
            particles[i].lifeTime = 0.0f; // Reset lifeTime
        }
    }
}

