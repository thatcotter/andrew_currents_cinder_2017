#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Perlin.h"
#include "cinder/Rand.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/InputNode.h"
#include "Particle.h"
#include "ParticleSystem.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class particlesTwoApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseMove( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    // have all value that is not going to change in here
    const int	NUM_PARTICLES = 25;
    const float  RANDOM_RANGE = 10.f;
    const float  RANDOM_FORCE_RANGE = 2.f;
    const float LIFE_SPAN = 3.f;
    
    // declare your value
    std::vector<ParticleSystemRef> ps;
    
    audio::InputDeviceNodeRef mic = ci::audio::master()->createInputDeviceNode();
};

void particlesTwoApp::setup()
{
    
}

void particlesTwoApp::mouseDown( MouseEvent event )
{
    glm::vec2 tempAcc = glm::vec2(ci::randFloat(-5, 5), ci::randFloat(-5, 1));
    
    auto p = ParticleSystem::create( event.getPos(), 90, tempAcc);
    
    ps.push_back(p);
    cout << ps.size() << endl;
}

void particlesTwoApp::mouseMove(cinder::app::MouseEvent event)
{
    
}

void particlesTwoApp::update()
{
    for (int i = 0; i < ps.size(); i++) {
        ps[i]->update();
        cout << "update: " << ps.size() << endl;
        if (ps[i]->isDead())
        {
            if (ps[i]->emmittedParticles < 50)
            {
                ps[i]->explode();
            }
            if (ps[i]->getArraySize() <= 0) {
                ps.erase( ps.begin() + i );
            }
        }
        
    }
}

void particlesTwoApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    for (int i = 0; i < ps.size(); i++) {
        ps[i]->draw();
    }
}

CINDER_APP( particlesTwoApp, RendererGl )
