#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class dialApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseMove( MouseEvent event ) override;
    void updateMouse();
	void update() override;
	void draw() override;
    
    vec2 mouseDelta();
    
    vec2 mousePos;
    vec2 prevMousePos;
    
    float mouseSpeed;
};

void dialApp::setup()
{
}

void dialApp::mouseDown( MouseEvent event )
{
}

void dialApp::mouseMove(cinder::app::MouseEvent event)
{
    mousePos = event.getPos();
}

void dialApp::updateMouse()
{
    prevMousePos = mousePos;
}

vec2 dialApp::mouseDelta()
{
    vec2 temp;
    temp = mousePos - prevMousePos;
    return abs(temp);
}

void dialApp::update()
{
    mouseSpeed = mouseDelta().x;
    updateMouse();
}

void dialApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    gl::drawString( "mouse speed: " + std::to_string(int(mouseSpeed)), ci::vec2(50, 50));
    
    vec2 center = 0.5f * vec2( getWindowSize() );
    
    for( int h = 0; h < 6; ++h ) {
        gl::pushModelView();
        
        gl::translate( center );
        gl::rotate( h * glm::radians( 30.0f ) - 1.3 );
        
        gl::color( 1.f, 1.f, 1.f );
        gl::drawSolidRect( Rectf( -3, -110, 3, -90 ) );
        
        gl::popModelView();
    }
    
    if (mouseSpeed > 25) {
        mouseSpeed = 25;
    }
    gl::pushModelView();
    gl::translate( center );
    gl::rotate( mouseSpeed * glm::radians( 360.0f / 60.0f ) - 1.3 );
    gl::color( 1.f, 0.f, 0.f );
    gl::drawSolidRect( Rectf( -1, -100, 1, 15 ) );
    gl::drawSolidCircle( vec2( 0 ), 6, 24 );
    gl::popModelView();
}

CINDER_APP( dialApp, RendererGl )
