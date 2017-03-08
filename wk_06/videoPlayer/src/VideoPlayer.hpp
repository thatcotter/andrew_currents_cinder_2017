//
//  VideoPlayer.hpp
//  videoPlayer
//
//  Created by Andrew Cotter on 3/7/17.
//
//

#ifndef VideoPlayer_hpp
#define VideoPlayer_hpp

#include "cinder/app/App.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"
#include "cinder/qtime/QuickTimeGl.h"

class VideoPlayer;

typedef std::shared_ptr<VideoPlayer> VideoPlayerRef;
typedef ci::signals::Signal<void()> VideoEndedSignal;

class VideoPlayer{
public:
    static VideoPlayerRef create();
    void loadVideo(std::string videoPath);
    void loadMovieFile(const ci::fs::path &moviePath);
    void openVideo(ci::app::KeyEvent event);
    void update();
    void draw();
    void stop();
    void play();
    void setLoop(bool bIsLoop);
    void onVideoEnded();
    
    VideoEndedSignal& getVideoEndedSignal(){return mVideoEndedSignal;}
private:
    VideoPlayer();
    void setup();
    void setPath(std::string path);
    
    VideoEndedSignal        mVideoEndedSignal;
    
    ci::gl::TextureRef      mFrameTexture;
    ci::qtime::MovieGlRef   mMovie;
    ci::fs::path            mMoviePath;
    
    bool paused;
    float mDuration;
    float mProgress;
    float mProgressPercent;
};

#endif /* VideoPlayer_hpp */
