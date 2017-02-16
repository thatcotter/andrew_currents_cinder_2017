#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageManipulationApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void mouseMove( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    void twirl(Surface8u *surface, Area area, float maxAngle);
    
    Rectf getRectf( glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale = glm::vec2( 1.f, 1.f ) );
    
    ci::Surface8u   mSurfaceTwirl;
    
    gl::TextureRef  mTexture;
    gl::TextureRef  mTexTwirlFromSurface;
    ci::Surface8u   mSurface;

    float mWidth;
    float mHeight;
    
    float angle;
};

Rectf ImageManipulationApp::getRectf(glm::vec2 startingPoint, glm::vec2 size, glm::vec2 scale){
    return Rectf( startingPoint.x, startingPoint.y, (( size.x + startingPoint.x ) * scale.x ), ((size.y + startingPoint.y) * scale.y) );
}

void ImageManipulationApp::setup()
{
    mWidth = .5f * 863.f;
    mHeight = .5f * 853.f;
    
    setWindowSize( mWidth + 20, 480 );
    
    try
    {
        mTexture = gl::Texture::create( loadImage( loadAsset( "it_me.jpg" ) ) );
        mSurface = loadImage( loadAsset( "it_me.jpg" ) );
        mSurfaceTwirl = mSurface.clone();
    } catch (exception& e)
    {
        ci::app::console() << e.what() << std::endl;
    }
    
//    ci::Surface::Iter iter = mSurface.getIter(mSurface.getBounds());
//    while(iter.line())
//    {
//        while(iter.pixel())
//        {
//            iter.r() = 255.f - iter.r();
//            iter.g() = 255.f - iter.g();
//            iter.b() = 255.f - iter.b();
//        }
//    }
    
    twirl( &mSurfaceTwirl, mSurfaceTwirl.getBounds(), 1.f);
}

void ImageManipulationApp::twirl(Surface8u *surface, Area area, float maxAngle)
{
    // clone the surface, or any changes make to *surface will affect directly on the variable
    ci::Surface8u inputSurface = surface->clone();
    
    ci::Surface::Iter inputIter(inputSurface.getIter());
    ci::Surface::Iter outputIter(surface->getIter(area));
    
    // get max radius. usually diagnal distance
    float maxDistance = ci::length((glm::vec2)area.getSize());
    
    glm::vec2 mid = (area.getUL() + area.getLR()) / 2;
    
    
    while( inputIter.line() && outputIter.line() ) {
        while( inputIter.pixel() && outputIter.pixel() ) {
            // getting the current pixel position, and get the distance between it and image center
            glm::vec2 current = (glm::vec2)inputIter.getPos() - mid;
            // get length of a vec2
            float r = length(current);
            
            float twirlAngle = r / maxDistance * maxAngle;
            float angle = atan2(current.x, current.y);
            glm::vec2 outSameple(r * cos( angle + twirlAngle  ), r * sin( angle + twirlAngle ));
            glm::vec2 out = outSameple - current;
            outputIter.r() = inputIter.rClamped( out.x, out.y );
            outputIter.g() = inputIter.gClamped( out.x, out.y );
            outputIter.b() = inputIter.bClamped( out.x, out.y );
            
        }
    }
    
//    cout << "twirl!" << endl;
}

void ImageManipulationApp::mouseDown( MouseEvent event )
{
}

void ImageManipulationApp::mouseMove(cinder::app::MouseEvent event)
{
    angle = event.getX() + 50 / abs(event.getY()) + 50;
}

void ImageManipulationApp::update()
{
    mSurfaceTwirl = mSurface.clone();
    twirl( &mSurfaceTwirl, mSurfaceTwirl.getBounds(), angle );
}

void ImageManipulationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    mTexTwirlFromSurface = gl::Texture::create(mSurfaceTwirl);
    gl::draw(mTexTwirlFromSurface, Rectf(0.f + 10.f, 0.f + 10.f, mWidth + 10.f, mHeight + 10.f));

    gl::drawString( "illustation by Marina Romero", ci::vec2( 10.f, mHeight + 25 ) );
}

CINDER_APP( ImageManipulationApp, RendererGl )
