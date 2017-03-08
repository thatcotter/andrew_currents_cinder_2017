#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "SmartPtr.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class PointerQuizApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    std::vector<SmartPtrRef> pointerArr;
};

void PointerQuizApp::setup()
{
    for (int i = 0; i < 10; i++)
    {
        pointerArr.push_back(SmartPtr::create());
    }
    cout << pointerArr.size()<< endl;
}

void PointerQuizApp::mouseDown( MouseEvent event )
{
}

void PointerQuizApp::update()
{
}

void PointerQuizApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( PointerQuizApp, RendererGl )
