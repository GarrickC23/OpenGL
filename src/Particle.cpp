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
#include <stdlib.h>
#include <ctime>
#include <vector>

ParticleSystem::ParticleSystem() 
{
    // rand function from -1 to 1
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize particles
    for (int i = 0; i < MAX_PARTICLES; i++) 
    {
        float xRandValue = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;       // x range from -1 to 1
        float yRandValue = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * 2.0f;       // y range from 1 to 1.5
        float zRandValue = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;       // x range from -1 to 1

        float randWidth = 0.002f + (static_cast<float>(rand()) / RAND_MAX) * 0.004f;       // y range from 0.002 to 0.006
        float randHeight = 0.025f + (static_cast<float>(rand()) / RAND_MAX) * 0.075f;       // y range from 0.025 to 0.1

        particles[i].position[0] = xRandValue; // X
        particles[i].position[1] = yRandValue;  // Y
        particles[i].position[2] = zRandValue;  // Z

        particles[i].velocity[0] = 0.0f;
        particles[i].velocity[1] = 0.1f;
        particles[i].velocity[2] = 0.0f;

        particles[i].lifeTime = 0.0f;
        particles[i].maxLifeTime = 10.0f; // 5 seconds of life

        particles[i].width = randWidth;
        particles[i].height = randHeight;
    }
}

void ParticleSystem::setWind(float windValue)
{
    wind = windValue;
}

void ParticleSystem::update(float deltaTime, double currentTime) 
{
    float gravity = 9.81f;      //gravity constant

    for(int i = 0; i < MAX_PARTICLES; i++) 
    {
        float xRandValue = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;       // x range from -1 to 1
        float yRandValue = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * 0.5f;       // y range from 1 to 1.5

        // Update position
        for (int j = 0; j < 3; j++) 
        {
            particles[i].position[j] -= particles[i].velocity[j] * deltaTime * gravity;
        }

        particles[i].position[0] += wind * deltaTime; 

        // Update lifeTime
        particles[i].lifeTime += deltaTime;

        // Reset if the particle has lived its life
        if ( particles[i].position[1] < -0.8f ) {
            particles[i].position[0] = xRandValue; // Reset X position
            particles[i].position[1] = yRandValue; // Reset Y position

            landings.push_back({particles[i].position[0], currentTime});

            // particles[i].lifeTime = 0.0f; // Reset lifeTime
        }
    }
}

