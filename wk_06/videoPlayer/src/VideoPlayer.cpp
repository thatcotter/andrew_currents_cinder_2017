//
//  VideoPlayer.cpp
//  videoPlayer
//
//  Created by Andrew Cotter on 3/7/17.
//
//

#include "VideoPlayer.hpp"

VideoPlayerRef VideoPlayer::create(){
    VideoPlayerRef ref = std::shared_ptr<VideoPlayer>(new VideoPlayer());
    ref->setup();
    return ref;
}

VideoPlayer::VideoPlayer()
{
}

void VideoPlayer::setup()
{
    ci::fs::path moviePath = ci::app::getOpenFilePath();;
    if( ! moviePath.empty() )
        loadMovieFile( moviePath );
    mDuration = mMovie->getNumFrames();
    mProgress = 0;
}

void VideoPlayer::setPath(std::string path)
{
    try
    {
        mMoviePath = ci::app::getAssetPath("fingers.mov");
    } catch (std::exception& e) {
        ci::app::console() << e.what() << std::endl;
    }
}

void VideoPlayer::openVideo(ci::app::KeyEvent event)
{
    if( event.getChar() == 'o' ) {
        ci::fs::path moviePath = ci::app::getOpenFilePath();
        if( ! moviePath.empty() )
            this->loadMovieFile( moviePath );
        mDuration = mMovie->getNumFrames();
        mProgress = 0;
    }
}

void VideoPlayer::loadMovieFile( const ci::fs::path &moviePath )
{
    try {
        // load up the movie, set it to loop, and begin playing
        mMovie = ci::qtime::MovieGl::create( moviePath );
        mMovie->setLoop();
        mMovie->play();
    }
    catch( ci::Exception &exc ) {
        cinder::app::console() << "Exception caught trying to load the movie from path: " << moviePath << ", what: " << exc.what() << std::endl;
        mMovie.reset();
    }
    
    mFrameTexture.reset();
}

void VideoPlayer::loadVideo(std::string videoPath)
{
    setPath(videoPath);
    
    try {
        mMovie = ci::qtime::MovieGl::create( mMoviePath );
        mMovie->setLoop();
        mMovie->play();
        mMovie->getEndedSignal().connect(std::bind(&VideoPlayer::onVideoEnded, this));
    }
    catch( std::exception& e ) {
        ci::app::console() << e.what() << std::endl;
        mMovie.reset();
    }
}

void VideoPlayer::update()
{
    if(mMovie){
        mFrameTexture = mMovie->getTexture();
    }
    
}

void VideoPlayer::play()
{
    if(mMovie){
        mMovie->play();
        this->paused = false;
    }
}

void VideoPlayer::stop()
{
    if(mMovie){
        mMovie->stop();
        this->paused = true;
    }
}

void VideoPlayer::setLoop(bool bIsLoop)
{
    if(mMovie){
        mMovie->setLoop(bIsLoop);
    }
}

void VideoPlayer::onVideoEnded()
{
    mVideoEndedSignal.emit();
}

void VideoPlayer::draw()
{
    if(mFrameTexture){
        ci::Rectf centeredRect = ci::Rectf( mFrameTexture->getBounds() ).getCenteredFit(ci::app::getWindowBounds(), true );
        //Rectf centeredRect = Rectf( mFrameTexture->getBounds() ).getCenteredFill( getWindowBounds(), true );
        
        ci::gl::draw( mFrameTexture, centeredRect );
    }
}
