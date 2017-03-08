#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTimeGl.h"

#include "VideoPlayer.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class videoPlayerApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
    
    void onVideoEnded();
    
    VideoPlayerRef mPlayer;
    int mPlayCount;
};

void videoPlayerApp::setup()
{
    mPlayCount = 0;
    mPlayer = VideoPlayer::create();
//    mPlayer->loadVideo("fingers.mov");
    mPlayer->getVideoEndedSignal().connect(std::bind(&videoPlayerApp::onVideoEnded, this));
}

void videoPlayerApp::mouseDown( MouseEvent event )
{
}

void videoPlayerApp::keyDown(cinder::app::KeyEvent event)
{
    mPlayer->openVideo(event);
}

void videoPlayerApp::onVideoEnded()
{
    ci::app::console() << "video has ended" << std::endl;
    mPlayCount += 1;
}

void videoPlayerApp::update()
{
    mPlayer->update();
}

void videoPlayerApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mPlayer->draw();
//    ci::gl::drawString(std::to_string(mPlayCount), glm::vec2(10.f, 10.f));
    
}

CINDER_APP( videoPlayerApp, RendererGl )
