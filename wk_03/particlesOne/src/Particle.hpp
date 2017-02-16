//
//  Particle.hpp
//  particlesOne
//
//  Created by Andrew Cotter on 2/10/17.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
//#include "cinder/Rand.h"

class Particle
{
public:
    Particle();
    Particle( glm::vec2 _initPos, glm::vec2 _initVel );
    void applyForce( glm::vec2 _force );
    ci::Rectf getRectf( glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale = glm::vec2( 1.f, 1.f ) );
    glm::vec2 getPos();
    glm::vec2 getVel();
    void update();
    void draw();
    
private:
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 acc;
    glm::vec2 force;
    
    float fric;
    float damp;
    
    ci::gl::TextureRef texture;
    int texSizeX;
    int texSizeY;
};

#endif /* Particle_hpp */
