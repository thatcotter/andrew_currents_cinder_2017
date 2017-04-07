//
//  Button.hpp
//  poScen_UI
//
//  Created by Andrew Cotter on 4/5/17.
//
//

#ifndef Button_hpp
#define Button_hpp

#include "poNodeContainer.h"
#include "poShape.h"

#include "cinder/Signals.h"

class Button;

typedef std::shared_ptr<Button> ButtonRef;
typedef ci::signals::Signal<void(bool state)> ButtonStateChangeSignal;

class Button : public po::scene::NodeContainer
{
public:
    static ButtonRef create( ci::vec2 position, float radius, ci::Color btnColor );
    ButtonStateChangeSignal& getButtonStateChangeSignal(){ return mButtonStateChangeSignal;}
    ci::Color getColor(){ return mColor; }
    float getAnimationTime(){ return mAnimationTime; }
    bool getIsActivated(){ return mIsActivated; }
    void inActivation(){ mIsActivated = false; }
    
private:
    Button();
    void setup( ci::vec2 position, float radius, ci::Color btnColor);
    void onMouseEvent(po::scene::MouseEvent &event);
    void addButtonCircle();
    
    po::scene::ShapeRef mButtonCircle;
    
    ci::vec2 mPosition;
    float mRadius;
    ci::Color mColor;
    
    float mAnimationTime;
    
    ButtonStateChangeSignal mButtonStateChangeSignal;
    
    bool mIsActivated;
};
#endif /* Button_hpp */
