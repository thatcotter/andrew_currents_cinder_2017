#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class clockApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    string hour;
    string minute;
    string sec;
    
    ci::Font myFont;
};

void clockApp::setup()
{
    ci::app::setWindowSize( 250.f, 100.f );
    
//    myFont = Font("manteka.ttf", 24);
}

void clockApp::mouseDown( MouseEvent event )
{
}

void clockApp::update()
{
    //calculate time
    auto t = std::time(nullptr);
    auto d = std::localtime(&t);
    
    cout << d->tm_hour%12 << endl;
    
    hour = std::to_string(d->tm_hour%12);
    
    if (d->tm_min < 10) {
        minute = "0" + std::to_string( + d->tm_min);
    } else{
        minute = std::to_string(d->tm_min);
    }
    if (d->tm_sec < 10) {
        sec = "0" + std::to_string(d->tm_sec);
    } else{
        sec = std::to_string(d->tm_sec);
    }
    

}

void clockApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    //draw hours
    gl::drawString( hour, ci::vec2( 100.f, 50.f ) );
    
    gl::drawSolidCircle(ci::vec2( 115.f, 50.f ), 1);
    gl::drawSolidCircle(ci::vec2( 115.f, 53.f ), 1);
    
    //draw minutes
    gl::drawString( minute, ci::vec2( 120.f, 50.f ) );
    
    gl::drawSolidCircle(ci::vec2( 140.f, 50.f ), 1);
    gl::drawSolidCircle(ci::vec2( 140.f, 53.f ), 1);
    
    //draw seconds
    gl::drawString( sec, ci::vec2( 148.f, 50.f ) );
}


CINDER_APP( clockApp, RendererGl )
