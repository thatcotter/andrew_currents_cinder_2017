#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "Particle.hpp"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class particlesOneApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    vector<Particle> ps;
    glm::vec2 gravity;
    int psSize;
};

void particlesOneApp::setup()
{
    psSize = 100;
    gravity = glm::vec2( 0.f, -0.02f );
    
    for (int i = 0; i < psSize; i++) {
        glm::vec2 initPos = glm::vec2( randFloat( -100, ci::app::getWindowWidth() + 100 ), ci::app::getWindowHeight() + 100 );
        glm::vec2 initVel = glm::vec2( randFloat( - 5, 5 ), randFloat( - 5, 5 ) );
        Particle temp( initPos, initVel );
        ps.push_back( temp );
    }
}

void particlesOneApp::mouseDown( MouseEvent event )
{
    
}

void particlesOneApp::update()
{
    if (ps.size() < psSize) {
        glm::vec2 initPos = glm::vec2( randFloat( -100, ci::app::getWindowWidth() + 100 ), ci::app::getWindowHeight() + 100 );
        glm::vec2 initVel = glm::vec2( randFloat( - 5, 5 ), randFloat( - 5, 5 ) );
        Particle temp( initPos, initVel );
        ps.push_back( temp );
    }
    
    for( auto& p: ps )
    {
        p.applyForce( gravity );
        p.update();
    }
    for (int i = 0; i < ps.size(); i++)
    {
        if (ps[i].getPos().y < -100)
        {
            ps.erase( ps.begin() + i );
        }
    }
}

void particlesOneApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color( 0.f, 1.f, 1.f );
    gl::drawSolidRect( Rectf( 0, 0, ci::app::getWindowWidth(), ci::app::getWindowHeight() ) );
    
    for ( auto& p: ps )
    {
        p.draw();
    }
}

CINDER_APP( particlesOneApp, RendererGl )
