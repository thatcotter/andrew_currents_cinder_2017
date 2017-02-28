#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class wavesApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    ci::Anim<vec2> startPos, endPos;
    
    std::vector<vec2> starts;
    std::vector<ci::Anim<vec2>> targets;
    ci::Anim<float> factor;
    
};

void wavesApp::setup()
{
    endPos = ci::app::getWindowCenter() - vec2( -10, 0 );
    startPos = endPos;
    
    for (int i = 0; i < 1000; i += 50)
    {
        ci::Anim<vec2> tempTarg;
        vec2 tempStart;
        
        tempTarg = vec2( i+10, ci::app::getWindowCenter().y+100 );
        tempStart = vec2( i+20, ci::app::getWindowCenter().y+100 );
        
        targets.push_back(tempTarg);
        starts.push_back(tempStart);
    }
}

void wavesApp::mouseDown( MouseEvent event )
{
    timeline().apply( &endPos, ci::app::getWindowCenter() - vec2( 0, 100 ), 1.f, EaseOutExpo() )
    .finishFn( [&]()
    {
        timeline().apply( &endPos, ci::app::getWindowCenter(),  1.f, EaseInExpo() );
    });
    
    for (int i = 0; i < targets.size(); i++)
    {
        cout << i << endl;
        timeline().apply( &targets[i], vec2( i * 50 + 10, ci::app::getWindowCenter().y - 100), 1.f, EaseOutExpo() ).delay( float(i)/32 )
        .finishFn( [&]()
                  {
                      for (int j = 0; j < targets.size(); j++)
                      {
                          cout << "finish: " << j << endl;
                          timeline().apply( &targets[j], vec2( (j*50)+10, ci::app::getWindowCenter().y+100 ),  1.f , EaseInExpo()).delay( float(j)/8 );
                      }
                      
                  });
    }
}

void wavesApp::update()
{
}

void wavesApp::draw()
{
	gl::clear( Color( 0.9f, 0.8f, 0.2f ) );
    
    gl::color( 0.1f, 0.1f, 0.1f );
//    gl::drawSolidRect( Rectf( startPos, endPos  ));
    for (int i = 0; i < targets.size(); i++)
    {
        gl::drawSolidRect( Rectf( starts[i], targets[i] ) );
    }
    
}

CINDER_APP( wavesApp, RendererGl )
