//
//  Particle.cpp
//  particlesOne
//
//  Created by Andrew Cotter on 2/10/17.
//
//

#include "Particle.hpp"

Particle::Particle()
{
    pos = glm::vec2( 0.f, 0.f );
    vel = glm::vec2( 0.f, 0.f );
    acc = glm::vec2( 0.f, 0.f );
    damp = 0.95f;
    fric = 0.95f;
    
    try {
        this->texture = cinder::gl::Texture::create( loadImage( cinder::app::loadAsset( "cloud1.png") ) );
    } catch (ci::Exception& e) {
        ci::app::console() << e.what() << std::endl;
    }
    texSizeX = 10;
    texSizeY = 10;
}

Particle::Particle( glm::vec2 _initPos, glm::vec2 _initVel )
{
    pos = _initPos;
    vel = _initVel;
    
    acc = glm::vec2( 0.f, 0.f );
    damp = 0.95f;
    fric = 0.95f;
    try {
        this->texture = cinder::gl::Texture::create( loadImage( cinder::app::loadAsset( "cloud1.png") ) );
    } catch (ci::Exception& e) {
        ci::app::console() << e.what() << std::endl;
    }
    texSizeX = 900;
    texSizeY = 498;
}

ci::Rectf Particle::getRectf(glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale){
    return ci::Rectf( startingPoint.x, startingPoint.y, (( size.x + startingPoint.x ) * scale.x ), ((size.y + startingPoint.y) * scale.y) );
}

glm::vec2 Particle::getPos()
{
    return this->pos;
}

glm::vec2 Particle::getVel()
{
    return this->vel;
}

void Particle::applyForce(glm::vec2 _force)
{
    this->force += _force;
}

void Particle::update()
{
    acc += force;// * fric;
    vel *= fric;
    vel += acc;
    pos += vel;
    force *= 0.f;
}

void Particle::draw()
{
    ci::gl::color( 1.f, 0.f, 1.f );
    
//    ci::gl::drawSolidCircle( pos, 2.f );
    ci::gl::draw( texture, getRectf( glm::vec2( pos.x , pos.y ) , glm::vec2( texSizeX, texSizeY ), glm::vec2( 0.5f, 0.5f )));
}
