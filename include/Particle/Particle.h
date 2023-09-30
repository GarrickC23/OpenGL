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

// Structure for a single particle with properties of position, velocity, and lifetime
struct Particle {
    float position[3];      // array for position with 3 values representing x, y, z
    float velocity[3];      // array for velocity with 3 values representing x, y, z
    float lifeTime;         // how long the particle is alive
    float maxLifeTime;      // max time the particle lives
};

class ParticleSystem {
private:
    static const int MAX_PARTICLES = 1000;
    Particle particles[MAX_PARTICLES];      //created from struct 

public:
    ParticleSystem();
    void update(float deltaTime);
    Particle* getParticles() { return particles; } // Expose particles for rendering
};

