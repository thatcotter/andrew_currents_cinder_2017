//
//  ParticleSystem.cpp
//  particlesTwo
//
//  Created by Andrew Cotter on 2/22/17.
//
//

#include "ParticleSystem.hpp"

ParticleSystemRef ParticleSystem::create(glm::vec2 position, float lifespan, glm::vec2 acceleration)
{
    ParticleSystemRef ref = std::shared_ptr<ParticleSystem>(new ParticleSystem());
    ref->setup(position, lifespan, acceleration);
    return ref;
}

ParticleSystem::ParticleSystem()
{
    
}

void ParticleSystem::setup(glm::vec2 _position, float _lifespan, glm::vec2 _acceleration)
{
    lifespan = _lifespan;
    pos = _position;
    acc  = _acceleration;
    vel += acc;
//    mTime.start();
}

void ParticleSystem::update()
{
    mTime = ci::app::getElapsedSeconds() * 100.f;
    
    this->age++;
    
    this->applyForce( glm::vec2( 0, -0.001f ) );
    pos += vel;
    
    for (auto& p: mParticles){
        p->update();
    }
    
    // remove particle if it has passed its lifespan
    for (auto p = mParticles.begin(); p != mParticles.end();)
    {
        if ( (*p)->getTimerleft() < 0) {
            p = mParticles.erase(p);
        } else {
            ++p;
        }
        
    }
}

void ParticleSystem::draw()
{
    
//    ci::gl::color( 1, 1, 1 );
    ci::gl::drawSolidCircle(pos, (lifespan-age) / 10);
    
    ci::gl::ScopedBlendAdditive blend;
    
    ci::gl::begin(GL_LINES);
    for (auto& p: mParticles){
        ci::gl::color(ci::ColorA(p->getTimerleft()/p->getLifespan() ,0.3f, 1.f - p->getTimerleft()/p->getLifespan(), p->getTimerleft()/p->getLifespan()));
        // get perlin value based on position
        glm::vec3 norm = mPerlin.dfBm( glm::vec3( p->getPosition().x, p->getPosition().y, mTime ) * mFrequency ) * 20.0f;
        glm::vec2 flowForce = normalize( glm::vec2( norm.x, norm.y ) ) * 0.1f;
        p->applyForce(flowForce);
        ci::gl::vertex(p->getPosition());
        ci::gl::vertex(p->getPosition() + glm::vec2(norm.x, norm.y) * 0.3f);
    }
    ci::gl::end();
    
//    if (this->isDead()) {
//        
//    }else{
//        ci::gl::drawSolidCircle(pos, 16);
//    }

}

void ParticleSystem::explode()
{
    for (int i = 0; i < NUM_PARTICLES; i++){
        
            glm::vec2 tempAcc = glm::vec2(ci::randFloat(-RANDOM_FORCE_RANGE, RANDOM_FORCE_RANGE), ci::randFloat(-RANDOM_FORCE_RANGE, RANDOM_FORCE_RANGE));
            
            mParticles.push_back(Particle::create( this->pos, LIFE_SPAN, tempAcc ));
        
    }
    
    emmittedParticles += NUM_PARTICLES;
}

void ParticleSystem::applyForce(glm::vec2 _force)
{
    vel += _force;
}

bool ParticleSystem::isDead()
{
    if ( this->age > this->lifespan) {
        std::cout << "boom!" << std::endl;
        return true;
    }else{
        return false;
    }
}

int ParticleSystem::getArraySize()
{
    return mParticles.size();
}
