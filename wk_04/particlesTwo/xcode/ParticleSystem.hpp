//
//  ParticleSystem.hpp
//  particlesTwo
//
//  Created by Andrew Cotter on 2/22/17.
//
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "Particle.h"
#include "cinder/Perlin.h"
#include "cinder/app/AppBase.h"
#include "cinder/Rand.h"
//#include "cinder/gl/gl.h"

class ParticleSystem;

typedef std::shared_ptr<ParticleSystem> ParticleSystemRef;

class ParticleSystem
{
public:
    static ParticleSystemRef create(glm::vec2 position, float lifespan, glm::vec2 acceleration);
    ParticleSystem();
    void setup(glm::vec2 position, float lifespan, glm::vec2 acceleration);
    void update();
    void draw();
    
    void explode();
    void applyForce(glm::vec2 _force);
    bool isDead();
    int getArraySize();
    
    float emmittedParticles = 0;
    
private:
    
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 acc;
    
    float lifespan;
    float age;
    
    
    
    //values to be passed into the particles
    const int	NUM_PARTICLES = 25;
    const float  RANDOM_RANGE = 10.f;
    const float  RANDOM_FORCE_RANGE = 2.f;
    const float LIFE_SPAN = 3.f;
    
    std::vector<ParticleRef> mParticles;
    
    ci::Perlin  mPerlin;
    float       mTime;
    float       mFrequency = 1 / 200.0f;
    
};

#endif /* ParticleSystem_hpp */
