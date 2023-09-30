// #ifndef PARTICLE_H
// #define UParticleSystemComponent* 

// class Particle {
//     public: 
//         // Constructor
//         Particle();

//         // Update the particle's state
//         void update(float deltaTime);

//         // Getters and Setters
//         float getX() const;
//         float getY() const;
//         void setVelocity(float vx, float vy);

//         bool isAlive() const;
    
//     private: 
//         // Particle properties
//         float x, y;     // Position
//         float vx, vy;   // Velocity
//         float life;     // Lifespan
//         float maxLife;  // MaximumLifeSpan
// };

// #endif

#pragma once

struct Particle {
    float position[3];
    float velocity[3];
    float lifeTime;
    float maxLifeTime;
};

class ParticleSystem {
private:
    static const int MAX_PARTICLES = 1000;
    Particle particles[MAX_PARTICLES];

public:
    ParticleSystem();
    void update(float deltaTime);
    Particle* getParticles() { return particles; } // Expose particles for rendering
};

